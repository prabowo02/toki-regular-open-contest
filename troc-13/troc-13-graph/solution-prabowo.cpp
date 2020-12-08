#include <bits/stdc++.h>
using namespace std;

const int LN = 19;
const int N = 300005;

int n, q;
vector<int> edges[N];

int depth[N], legs[N], branch[N];
int par[LN][N];

void dfs(int u, int p) {
  par[0][u] = p;
  for (int v: edges[u]) {
    if (v == p) continue;
    depth[v] = depth[u] + 1;
    dfs(v, u);
  }
}

void init_lca(int root) {
  dfs(root, root);

  for (int i = 1; i < LN; ++i) {
    for (int j = 0; j < n; ++j) {
      par[i][j] = par[i-1][par[i-1][j]];
    }
  }
}

int lca(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  while (depth[u] != depth[v]) {
    u = par[__builtin_ctz(depth[u] - depth[v])][u];
  }

  if (u == v) return u;
  for (int i = LN-1; i >= 0; --i) {
    if (par[i][u] == par[i][v]) continue;
    u = par[i][u];
    v = par[i][v];
  }

  return par[0][u];
}

int dist(int u, int v) {
  return depth[u] + depth[v] - depth[lca(u, v)]*2;
}

int main() {
  scanf("%d %d", &n, &q);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;

    edges[u].push_back(v);
    edges[v].push_back(u);
  }

  vector<int> leaf;
  for (int i = 0; i < n; ++i) {
    legs[i] = -1;
    if (edges[i].size() == 1) {
      leaf.push_back(i);
    }
  }

  init_lca(0);

  if (leaf.size() > 2) for (int u: leaf) {
    int prv = u, r = u;
    while (edges[u].size() < 3) {
      legs[u] = r;
      int v = edges[u][0];
      if (v == prv) v = edges[u][1];
      prv = u; u = v;
    }
    branch[r] = u;
  }

  while (q--) {
    int a, b, r;
    scanf("%d %d %d", &a, &b, &r);
    --a, --b, --r;

    if (edges[r].size() > 1) {
      printf("%d\n", a == r || b == r ? 1 : 0);
    } else {
      if (leaf.size() <= 2) printf("%d\n", dist(a, b));
      else {
        bool onLegA = legs[a] == r || a == branch[r];
        bool onLegB = legs[b] == r || b == branch[r];

        if (onLegA && onLegB) printf("%d\n", dist(a, b));
        else if (onLegA) printf("%d\n", min(dist(a, b), dist(a, branch[r]) + dist(r, branch[r]) + 1));
        else if (onLegB) printf("%d\n", min(dist(a, b), dist(b, branch[r]) + dist(r, branch[r]) + 1));
        else {
          int ans = min(dist(a, b), dist(r, branch[r]) * 2);

          int median = lca(a, b), l;
          if (depth[l = lca(branch[r], a)] > depth[median]) median = l;
          if (depth[l = lca(branch[r], b)] > depth[median]) median = l;
          if (median != a && median != b) ans = min(ans, dist(median, r));
          else ans = min(ans, dist(median, r) + 1);

          printf("%d\n", ans);
        }
      }
    }
  }
  return 0;
}
