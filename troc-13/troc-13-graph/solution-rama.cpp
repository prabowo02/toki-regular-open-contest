#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;
const int BITS = 20;

int N, Q;
int ans[MAXN];
vector<int> adj[MAXN];

int depth[MAXN]; // rooted at 1
int par[MAXN][BITS]; // rooted at 1

void DfsInit(int u, int p) {
  depth[u] = depth[p] + 1;
  par[u][0] = p;
  for (int i = 1; i < BITS; i++) {
    par[u][i] = par[par[u][i - 1]][i - 1];
  }

  for (auto v : adj[u]) if (v != p) DfsInit(v, u);
}

int GetAncestor(int u, int x) { // rooted at 1
  for (int i = 0; i < BITS; i++) {
    if (x & (1 << i)) {
      u = par[u][i];
    }
  }
  return u;
}

int Lca(int u, int v) { // rooted at 1
  if (depth[u] > depth[v]) swap(u, v);
  v = GetAncestor(v, depth[v] - depth[u]);
  for (int i = BITS - 1; i >= 0; i--) {
    if (par[u][i] != par[v][i]) {
      u = par[u][i];
      v = par[v][i];
    }
  }
  return u == v ? u : par[u][0];
}

int Lca(int r, int u, int v) { // rooted at r
  vector<int> lcas = {Lca(u, v), Lca(u, r), Lca(v, r)};
  sort(begin(lcas), end(lcas), [&](int x, int y) { return depth[x] < depth[y]; });
  return lcas[2]; 
}

int Distance(int u, int v) {
  return depth[u] + depth[v] - 2 * depth[Lca(u, v)];
}

bool IsLineGraph() {
  static int res = -1;
  if (res != -1) return res;
  res = 1;
  for (int i = 1; i <= N; i++) {
    if (adj[i].size() > 2) res = 0;
  }
  return res;
}

vector<pair<pair<int, int>, int>> pending[MAXN];

// Cases for pending:
// 1 If r to u or v before nearest: dist(r, nearest) + dist(other(u, v), nearest) + 1
// 2 If u and v same nearest subtree: 2 * dist(r, nearest)
//                                    dist(r, nearest) + dist(nearest, v) + 1
//                                    dist(r, nearest) + dist(nearest, u) + 1
// 3 If u and v different nearest subtree:
//   3.1 deg[nearest] == 3: 2 * dist(r, nearest) + min(2, dist(r, nearest))
//                          dist(r, nearest) + dist(nearest, v) - 1
//                          dist(r, nearest) + dist(nearest, u) - 1
//   3.2 deg[nearest] >= 4: 2 * dist(r, nearest)
//                          dist(r, nearest) + dist(nearest, v) - 1
//                          dist(r, nearest) + dist(nearest, u) - 1

int GetNearest(int u, int p = 0) {
  if (adj[u].size() >= 3) return u;
  for (auto v : adj[u]) if (v != p) {
    return GetNearest(v, u);
  }
  return -1;
}

void SolvePending(int r) {
  int nearest = GetNearest(r);
  for (auto pending_ : pending[r]) {
    int u, v, qid;
    tie(u, v) = pending_.first;
    qid = pending_.second;
    if (max(Distance(r, u), Distance(r, v)) <= Distance(r, nearest)) continue;
    if (Distance(r, v) <= Distance(r, nearest)) {
      ans[qid] = min(ans[qid], Distance(r, nearest) + Distance(v, nearest) + 1);
    } else if (Distance(r, u) <= Distance(r, nearest)) {
      ans[qid] = min(ans[qid], Distance(r, nearest) + Distance(u, nearest) + 1);
    } else if (Lca(u, v) != nearest) { // u and v are in same subtree of nearest
      ans[qid] = min(ans[qid], 2 * Distance(r, nearest));
      ans[qid] = min(ans[qid], Distance(r, nearest) + Distance(nearest, v) + 1);
      ans[qid] = min(ans[qid], Distance(r, nearest) + Distance(nearest, u) + 1);
    } else if (adj[nearest].size() == 3) { // u and v are in different subtree of nearest
      ans[qid] = min(ans[qid], 2 * Distance(r, nearest) + min(2, Distance(r, nearest)));
      ans[qid] = min(ans[qid], Distance(r, nearest) + Distance(nearest, v) - 1);
      ans[qid] = min(ans[qid], Distance(r, nearest) + Distance(nearest, u) - 1);
    } else {
      ans[qid] = min(ans[qid], 2 * Distance(r, nearest));
      ans[qid] = min(ans[qid], Distance(r, nearest) + Distance(nearest, v) - 1);
      ans[qid] = min(ans[qid], Distance(r, nearest) + Distance(nearest, u) - 1);
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  
  cin >> N >> Q;

  for (int i = 1; i < N; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }

  DfsInit(1, 0);

  for (int i = 0; i < Q; i++) {
    int u, v, r;
    cin >> u >> v >> r;
    ans[i] = Distance(u, v);
    if (adj[r].size() > 1) {
      ans[i] = min(ans[i], ((u == r || v == r) ? 1 : 0));
    } else {
      int lca = Lca(r, u, v);
      if (lca != u && lca != v) {
        ans[i] = min(ans[i], Distance(lca, r));
      }
      if (!IsLineGraph()) {
        pending[r].push_back({{u, v}, i});
      }
    }
  }

  if (!IsLineGraph()) {
    for (int i = 1; i <= N; i++) {
      if (adj[i].size() == 1) {
        SolvePending(i);
      }
    }
  }

  for (int i = 0; i < Q; i++) {
    cout << ans[i] << "\n";
  }
  return 0;
}
