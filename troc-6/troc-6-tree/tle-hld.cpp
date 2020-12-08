// O(QK log^2 N), too slow
// but memory is lower...
// for testing
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int LOG = 17;

int k;

struct Node {
  int len;
  long long ans;
  vector<pair<int, int>> pref, suf;

  Node() {
    len = 0;
    ans = 0;
    pref = suf = {{0, 0}};
  }

  void init(int v) {
    len = 1;
    ans = (k == 1);
    pref = suf = {{1 << v, 1}};
  }

  Node operator +(Node other) const {
    Node ret;
    ret.len = len + other.len;
    ret.ans = ans + other.ans;

    for (int i = (int)suf.size()-1, j = 0, otherLen = other.len ; i >= 0 ; i--) {
      while (j < other.pref.size() && __builtin_popcount(suf[i].first | other.pref[j].first) != k) {
        otherLen -= other.pref[j].second;
        j++;
      }

      ret.ans += 1ll * suf[i].second * otherLen;
    }

    {
      ret.pref = pref;
      for (pair<int, int> it : other.pref) {
        int lst = ret.pref.back().first;
        int cur = lst | it.first;
        if (cur == lst) {
          ret.pref[ret.pref.size()-1].second += it.second;
        } else {
          ret.pref.push_back({cur, it.second});
        }
      }
    }

    {
      ret.suf = other.suf;
      for (pair<int, int> it : suf) {
        int lst = ret.suf.back().first;
        int cur = lst | it.first;
        if (cur == lst) {
          ret.suf[ret.suf.size() - 1].second += it.second;
        } else {
          ret.suf.push_back({cur, it.second});
        }
      }
    }

    return ret;
  }
};

int n, q;
Node stree[4 * N];

vector<pair<int, int>> adj[N];
int depth[N];
int in[N];
int heavy[N];
int sz[N];
int chainHead[N];
pair<int, int> parent[N];
int inve[N];

void dfs(int now, int prv) {
  sz[now] = 1;
  heavy[now] = -1;

  for (int i = 0 ; i < adj[now].size() ; i++) {
    pair<int, int> nxt = adj[now][i];
    int nex = nxt.first;
    int color = nxt.second;
    if (nex == prv) continue;

    parent[nex] = {now, color};
    depth[nex] = depth[now] + 1;
    dfs(nex, now);

    sz[now] += sz[nex];
    if (heavy[now] == -1 || sz[nex] > sz[heavy[now]]) {
      heavy[now] = nex;
      swap(adj[now][0], adj[now][i]);
    }
  }
}

void dfsHld(int now, int prv, int head) {
  static int dfsCnt = 0;

  in[now] = ++dfsCnt;
  inve[dfsCnt] = now;
  chainHead[now] = head;
  for (int i = 0 ; i < adj[now].size() ; i++) {
    pair<int, int> nxt = adj[now][i];
    int nex = nxt.first;
    if (nex == prv) continue;

    dfsHld(nex, now, i == 0 ? head : nex);
  }
}

void build(int id, int l, int r) {
  if (l == r) {
    int idx = inve[l];
    stree[id].init(parent[idx].second);
  } else {
    int m = (l + r) / 2;
    int chld = id << 1;

    build(chld, l, m);
    build(chld+1, m+1, r);

    stree[id] = stree[chld] + stree[chld+1];
  }
}

Node query(int id, int l, int r, int x, int y) {
  if (x <= l && r <= y) {
    return stree[id];
  } else {
    int m = (l + r) / 2;
    int chld = id << 1;

    Node ret;
    if (x <= m) ret = ret + query(chld, l, m, x, y);
    if (y > m) ret = ret + query(chld+1, m+1, r, x, y);
    return ret;
  }
}

long long solve(int u, int v) {
  Node pathU, pathV;

  while (chainHead[u] != chainHead[v]) {
    if (depth[chainHead[u]] > depth[chainHead[v]]) {
      int uu = chainHead[u];
      Node cur = query(1, 1, n, in[uu], in[u]);
      pathU = cur + pathU;
      u = parent[uu].first;
    } else {
      int vv = chainHead[v];
      Node cur = query(1, 1, n, in[vv], in[v]);
      pathV = cur + pathV;
      v = parent[vv].first;
    }
  }

  if (depth[u] > depth[v]) {
    Node cur = query(1, 1, n, in[v]+1, in[u]);
    pathU = cur + pathU;
  } else if (depth[u] < depth[v]) {
    Node cur = query(1, 1, n, in[u]+1, in[v]);
    pathV = cur + pathV;
  }

  swap(pathU.pref, pathU.suf);
  Node ret = pathU + pathV;

  return ret.ans;
}

void read() {
  scanf("%d %d", &n, &k);
  for (int i = 1 ; i < n ; i++) {
    int u, v;
    char s[5];
    
    scanf("%d %d %s", &u, &v, s);
    int ch = s[0] - 'a';

    adj[u].push_back({v, ch});
    adj[v].push_back({u, ch});
  }
}

void prepare() {
  dfs(1, -1);
  dfsHld(1, -1, 1);
  build(1, 1, n);
}

void work() {
  scanf("%d", &q);
  for (int i = 0 ; i < q ; i++) {
    int u, v;
    scanf("%d %d", &u, &v);

    printf("%lld\n", solve(u, v));
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}
