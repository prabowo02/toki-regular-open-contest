#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, m;
vector<int> edges[N];
vector<int> redges[N];

bool vis[N];
void dfs(int u, vector<int> &order, vector<int> edges[]) {
  vis[u] = true;
  for (int v: edges[u]) {
    if (vis[v]) continue;
    dfs(v, order, edges);
  }
  
  order.push_back(u);
}

vector<vector<int>> buildSCC() {
  vector<int> order;
  for (int i = 0; i < n; ++i) if (!vis[i]) dfs(i, order, edges);
  
  reverse(order.begin(), order.end());

  for (int i = 0; i < n; ++i) vis[i] = false;
  
  vector<vector<int>> ret;
  for (int u: order) {
    if (vis[u]) continue;

    ret.push_back({});
    dfs(u, ret.back(), redges);
  }

  return ret;
}

int par[N];
int root(int u) { return u == par[u] ? u : par[u] = root(par[u]); }

int comp[N];
bool sccDagIsGood(const vector<vector<int>> &sccs, vector<int> edges[]) {
  for (int i = 0; i < sccs.size(); ++i) {
    for (int u: sccs[i]) comp[u] = i;
    par[i] = i;
  }

  for (const vector<int> &scc: sccs) {
    for (int u: scc) {
      int otherScc = -1;
      for (int v: edges[u]) {
        if (comp[u] == comp[v]) continue;

        if (otherScc == -1) otherScc = comp[v];
        if (root(comp[v]) != root(otherScc)) {
          return false;
        }
      }
      if (otherScc != -1) par[root(comp[u])] = root(otherScc);
    }
  }

  for (int i = 1; i < n; ++i) {
    if (root(comp[i]) != root(comp[0])) return false;
  }
  return true;
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;

    edges[u].push_back(v);
    redges[v].push_back(u);
  }

  vector<vector<int>> scc = buildSCC();

  if (!sccDagIsGood(scc, redges)) {
    return 0 * printf("TIDAK\n");
  }
  reverse(scc.begin(), scc.end());
  if (!sccDagIsGood(scc, edges)) {
    return 0 * printf("TIDAK\n");
  }

  printf("YA\n");
  return 0;
}
