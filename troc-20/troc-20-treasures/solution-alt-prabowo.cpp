#include <bits/stdc++.h>
using namespace std;

const int M = 200005;
const int INF = 1e9 + 5;

int n, m;
int t[M], x[M], y[M], z[M];

// a[first] <= second
vector<pair<int, int>> nodes;

namespace TwoSat {

int n;
vector<vector<int>> adj, radj;
vector<bool> vis;

// Init number of unknowns
void init(int _n) {
  n = _n;
  adj.assign(n * 2, vector<int>());
  radj.assign(n * 2, vector<int>());
  vis.assign(n * 2, false);
}

// Add a clause (x/2 or y/2), if odd means negation
void addClause(int x, int y) {
  adj[x ^ 1].push_back(y);
  adj[y ^ 1].push_back(x);
  radj[y].push_back(x ^ 1);
  radj[x].push_back(y ^ 1);
}

void dfs(int u, vector<int> &order, const vector<vector<int>> &adj) {
  vis[u] = true;
  for (int v : adj[u]) {
    if (vis[v]) continue;
    dfs(v, order, adj);
  }
  order.push_back(u);
}

bool satisfiable() {
  vector<int> order;
  for (int u = 0; u < n * 2; ++u) if (!vis[u]) dfs(u, order, adj);
  reverse(order.begin(), order.end());

  for (int u = 0; u < n * 2; ++u) vis[u] = false;

  vector<bool> found(n, false);
  for (int u : order) {
    if (vis[u]) continue;

    vector<int> comp;
    dfs(u, comp, radj);
    for (int u : comp) {
      if (found[u / 2]) return false;
      found[u / 2] = true;
    }
    for (int u : comp) found[u / 2] = false;
  }

  return true;
}

} // namespace TwoSat

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d %d %d %d", &t[i], &x[i], &y[i], &z[i]);
    --x[i], --y[i];
    nodes.emplace_back(x[i], z[i]);
    nodes.emplace_back(x[i], z[i] - 1);
    nodes.emplace_back(y[i], z[i]);
    nodes.emplace_back(y[i], z[i] - 1);
  }
  sort(nodes.begin(), nodes.end());
  nodes.resize(unique(nodes.begin(), nodes.end()) - nodes.begin());

  TwoSat::init(nodes.size());

  for (int i = 1; i < nodes.size(); ++i) {
    if (nodes[i - 1].first == nodes[i].first) {
      TwoSat::addClause(i*2, (i-1)*2 + 1);
    }
  }

  for (int i = 0; i < m; ++i) {
    int xz = lower_bound(nodes.begin(), nodes.end(), make_pair(x[i], z[i])) - nodes.begin();
    int xz1 = lower_bound(nodes.begin(), nodes.end(), make_pair(x[i], z[i] - 1)) - nodes.begin();
    int yz = lower_bound(nodes.begin(), nodes.end(), make_pair(y[i], z[i])) - nodes.begin();
    int yz1 = lower_bound(nodes.begin(), nodes.end(), make_pair(y[i], z[i] - 1)) - nodes.begin();

    if (t[i] == 1) {
      TwoSat::addClause(xz*2, xz*2);
      TwoSat::addClause(yz*2, yz*2);
      TwoSat::addClause(xz1*2 + 1, yz1*2 + 1);
    } else if (t[i] == 2) {
      TwoSat::addClause(xz1*2 + 1, xz1*2 + 1);
      TwoSat::addClause(yz1*2 + 1, yz1*2 + 1);
      TwoSat::addClause(xz*2, yz*2);
    }
  }

  printf(TwoSat::satisfiable() ? "YES\n" : "NO\n");
  return 0;
}
