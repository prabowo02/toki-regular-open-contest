#include <cstdio>
#include <vector>
#include <tuple>
#include <utility>
#define pii pair<int, int>
#define piii tuple<int, int, int>//urutan update, ngubah berapa, dari posisi mana
using namespace std;

//solution O(N sqrt Q) - pending update + pending query
//while renew the answer
//small to large -> O(sqrt(Q) * sqrt(Q) + N) N times vector swap and sqrt(Q) times processing in O(sqrt(Q))

int N, Q;
int A[50005], par[50005];
long long dp[50005], sz[50005];
vector<int> adj[50005];
vector<pii> upd[50005];
int lazy[50005];
vector<int> ask[50005];
long long ans[50005];

void DFS(int u, int p) {
  for(int v : adj[u]) {
    if(v == p) continue;
    DFS(v, u);
    dp[u] += sz[u] * sz[v];
    sz[u] += sz[v];
  }
  sz[u] += A[u];
}

long long init_sz[50005];
//dp[u] nyimpen semua pasangan lca(u, v) = x, yang u != x dan v != x

void refresh(int u, int p) {
  long long init_dp = dp[u], tmp_sz = sz[u] - A[u];
  bool init_state = A[u];
  init_sz[u] = sz[u];
  dp[u] = sz[u] = 0;
  int id = 0, cnt_upd = upd[u].size(), ada = !upd[u].empty();//ada simpen banyak child + node ini yang ada update
  for(int v : adj[u]) {
    if(v == p) continue;
    refresh(v, u);
    if(upd[v].empty() == 0) cnt_upd += upd[v].size(), id = v, ada++;
    dp[u] += sz[u] * sz[v];
    sz[u] += sz[v];
  }
  if(cnt_upd & 1) A[u] = !A[u];
  if(A[u]) sz[u]++;
  //we can skip the process and lazy the update
  if(ada < 2 && ask[u].empty()) {
    if(id) {
//      assert(upd[u].empty());
      swap(upd[id], upd[u]);
      if(init_state) {
        lazy[u] = lazy[id] - 1;
      }else {
        lazy[u] = lazy[id] + 1;
      }
    }else {
      if(init_state) {
        lazy[u] = -1;
      }else {
        lazy[u] = 1;
      }
    }
    return;
  }
  
  //merge and unlazy the query O(size)
  vector<piii> upd_list(upd[u].size());
  //move upd[u] to upd_list
  for(int i = 0; i < upd[u].size(); i++) {
    upd_list[i] = make_tuple(upd[u][i].first, 0, u);
  }
  //merge all upd
  int v;
  for(int aa = 0; aa < adj[u].size(); aa++) {
    v = adj[u][aa];
    if(v == p || upd[v].empty()) continue;
    
    //unlazy O(size[v])
    for(int i = 1; i < upd[v].size(); i += 2) {
      upd[v][i - 1].second += lazy[v];
      upd[v][i].second -= lazy[v];//negate first lazy
    }
    if(upd[v].size() & 1) {
      upd[v].back().second += lazy[v];
    }
    
    //merge O(size[u] + size[v])
    int p_v = 0, p_res = 0;
    vector<piii> res(upd_list.size() + upd[v].size());
    for(int idx = 0; idx < upd_list.size(); idx++) {
      while(p_v < upd[v].size() && upd[v][p_v].first < get<0>(upd_list[idx])) {
        res[p_res++] = make_tuple(upd[v][p_v].first, upd[v][p_v].second, v);
        p_v++;
      }
      res[p_res++] = upd_list[idx];
    }
    
    while(p_v < upd[v].size()) {
      res[p_res++] = make_tuple(upd[v][p_v].first, upd[v][p_v].second, v);
      p_v++;
    }
    swap(res, upd_list);
    upd[v].clear();
  }
  //copying upd_list to upd[u]
  upd[u].resize(upd_list.size());
  for(int i = 0; i < upd_list.size(); i++) {
    upd[u][i] = make_pair(get<0>(upd_list[i]), get<1>(upd_list[i]));
  }
  //update lazy
  if(init_state) {
    lazy[u] = -1;
  }else {
    lazy[u] = 1;
  }
  //process answer
  //init_dp: all valid (u, v) after some update
  //tmp_sz: sz[u] after some update

  if(!ask[u].empty()) {
    int idx = 0, order, val, child;
    for(int i = 0; i < upd_list.size(); i++) {
      tie(order, val, child) = upd_list[i];
      while(idx < ask[u].size() && ask[u][idx] < order) {
        if(init_state ^ (i & 1)) {
          ans[ask[u][idx]] = init_dp + tmp_sz;
        }else {
          ans[ask[u][idx]] = init_dp;
        }
        idx++;
      }
      //update init_dp and tmp_sz
      init_dp += val * (tmp_sz - init_sz[child]);//(yang berubah) * (selain yang di subtree itu)
      tmp_sz += val;
      init_sz[child] += val;
    }

    while(idx < ask[u].size()) {
      if(A[u]) {
        ans[ask[u][idx]] = init_dp + tmp_sz;
      }else {
        ans[ask[u][idx]] = init_dp;
      }
      idx++;
    }
    ask[u].clear();
  }
}

int main() {
  scanf("%d %d", &N, &Q);
  for(int i = 1; i <= N; i++) {
    scanf("%d", &A[i]);
  }
  int u, v;
  for(int i = 1; i < N; i++) {
    scanf("%d %d", &u, &v);
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  DFS(1, 0);
  int ty, pending = 0;
  for(int i = 1; i <= Q; i++) {
    ans[i] = -1LL;//empty ans
    scanf("%d %d", &ty, &u);
    if(ty == 1) {
      upd[u].emplace_back(i, 0);
    }else {
      ask[u].emplace_back(i);
    }
    pending++;
    if(pending > 223) {
      refresh(1, 0), pending = 0;
      upd[1].clear();
    }
  }
  if(pending) refresh(1, 0);
  for(int i = 1; i <= Q; i++) {
    if(ans[i] != -1LL) printf("%lld\n", ans[i]);
  }
}