#include <bits/stdc++.h>
#define LOG2(n) (31 - __builtin_clz(n))
#define l first
#define r second
#define pii pair<int, int>
using namespace std;

int N, Q;
int depth[300005], par[300005];
pii euler[300005];
int LCA_T[600005][20];
vector<int> adj[300005];
int waktu;//untuk 

void DFS(int u, int p) {
  par[u] = p;
  depth[u] = depth[p] + 1;
  LCA_T[++waktu][0] = u;
  euler[u].l = waktu;
  for(int v : adj[u]) {
    if(v == p) continue;
    DFS(v, u);
  }
  LCA_T[++waktu][0] = u;
  euler[u].r = waktu;
}

int nearest[300005];
int far[300005];

//lets find nearest
void BFS() {
  queue<int> q;
  memset(far, 0x3f3f3f3f, sizeof(far));
  for(int i = 1; i <= N; i++) {
    if(adj[i].size() <= 2) continue;
    q.push(i);
    far[i] = 0;
    nearest[i] = i;
  }
  while(!q.empty()) {
    int u = q.front();
    q.pop();
    for(int v : adj[u]) {
      if(far[v] > far[u] + 1) {
        far[v] = far[u] + 1;
        nearest[v] = nearest[u];
        q.push(v);
      }
    }
  }
}

//LCA part start i don't know if it will works or not
void prepare_LCA() {
  for(int k = 1; (1 << k) <= N * 2; k++) {
    int b = N * 2 - (1 << k) + 1;
    for(int i = 1; i <= b; i++) {
      int le = LCA_T[i][k - 1], ri = LCA_T[i + (1 << (k - 1))][k - 1];
      if(depth[le] > depth[ri]) {
        LCA_T[i][k] = ri;
      }else LCA_T[i][k] = le;
    }
  }
}

int rmq(int l, int r) {
  int lg = LOG2(r - l + 1);
  int le = LCA_T[l][lg], ri = LCA_T[r - (1 << lg) + 1][lg];
  return depth[le] < depth[ri] ? le : ri;
}

int LCA(int u, int v) {
  if(depth[u] > depth[v]) swap(u, v);
  if(euler[u].l <= euler[v].l && euler[v].r <= euler[u].r) {
    return u;
  }
  return par[rmq(min(euler[u].l, euler[v].l), max(euler[u].r, euler[v].r))];
}

int dist(int u, int v) {
  return depth[u] + depth[v] - (depth[LCA(u, v)] << 1);
}

int ans, distU_V, distR_U, distR_V;

//just to find lca between u and v if r are root
int find_LCA(int u, int v, int r) {
  int U_V = LCA(u, v), R_U = LCA(u, r), R_V = LCA(v, r);
  int lca = U_V, distnow = dist(r, U_V);
  if(distnow > dist(r, R_U) && dist(R_U, v) + dist(R_U, u) == dist(u, v)) lca = R_U, distnow = dist(r, R_U);
  if(distnow > dist(r, R_V) && dist(R_V, v) + dist(R_V, u) == dist(u, v)) lca = R_V, distnow = dist(r, R_V);
  return lca;
}

void go() {
  while(Q--) {
    int u, v, r;
    scanf("%d %d %d", &u, &v, &r);
    int lca = find_LCA(u, v, r);
    ans = dist(u, v);
    if(adj[r].size() > 1) {
      if(r != u && r != v) ans = 0;
      else if(u != v) ans = 1;
    }
    //okay i need to find nearest node with degree > 2 now
    int med = nearest[r];
    if(lca != u && lca != v) {
      //u bisa langsung teleport ke v
      ans = min(ans, dist(lca, r));
    }
    if(med != 0) {
      //u teleport ke nearest dan v teleport ke nearest 
      int a = find_LCA(u, med, r), b = find_LCA(v, med, r);
      if(a != u) a = 1;
      else a = 0;
      if(b != v) b = 1;
      else b = 0;
      if(a & b) ans = min(ans, dist(r, med) * 2);
      //v teleport ke nearest kemudian ke u manual and vice versa
      if(b) {
        ans = min(ans, dist(u, med) + dist(med, r) + 1);
      }
      if(a) {
        ans = min(ans, dist(v, med) + dist(med, r) + 1);
      }
    }
    printf("%d\n", ans);
  }
}

int main() {
  scanf("%d %d", &N, &Q);
  int u, v;
  for(int i = 1; i < N; i++) {
    scanf("%d %d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  BFS();
  DFS(1, 0);
  prepare_LCA();
  go();
}