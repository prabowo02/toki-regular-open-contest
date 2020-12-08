/**
 * Author   : rama_pang
 * Problem  : troc-11-graf
 * Time     : O(N + M)
 * Memory   : O(N + M)
**/

#include <bits/stdc++.h>
using namespace std;

struct SCC {
  int N;
  vector<vector<int>> adj, rev;

  vector<int> todo;
  vector<int> comp, allComp;
  vector<int> vis;
  
  SCC(int n) : N(n) {
    adj.resize(N);
    rev.resize(N);
    vis.assign(N, 0);
    comp.assign(N, -1);
  }

  void dfs(int n) {
    vis[n] = 1;
    for (auto &i : adj[n]) if (!vis[i]) dfs(i);
    todo.emplace_back(n);
  }

  void dfs2(int n, int id) {
    comp[n] = id;
    for (auto &i : rev[n]) if (comp[i] == -1) dfs2(i, id);
    
  }

  void build() {
    for (int i = 0; i < N; i++) if (!vis[i]) dfs(i);
    reverse(begin(todo), end(todo));
    for (auto &i : todo) if (comp[i] == -1) dfs2(i, i), allComp.emplace_back(i);
  }

  void addEdge(int u, int v) {
    adj[u].emplace_back(v);
    rev[v].emplace_back(u);
  }

};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);

  int N, M;
  cin >> N >> M;

  SCC SCC(N);
  vector<pair<int, int>> edge;

  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    SCC.addEdge(u, v);
    edge.emplace_back(u, v);
  }

  SCC.build();
  vector<int> compPos(N, -1);
  for (int i = 0; i < (int) SCC.allComp.size(); i++) {
    compPos[SCC.allComp[i]] = i;
  }
  N = (int) SCC.allComp.size();
  
  vector<vector<int>> adj(N);
  vector<int> indeg(N);
  for (int i = 0; i < M; i++) {
    int u, v;
    tie(u, v) = edge[i];
    u = compPos[SCC.comp[u]];
    v = compPos[SCC.comp[v]];
    if (u != v) {
      adj[u].emplace_back(v);
      indeg[v]++;
    }
  }

  vector<int> candidates;
  for (int i = 0; i < N; i++) {
    if (indeg[i] == 0) { 
      candidates.emplace_back(i);
    }
  }

  while (!candidates.empty()) { // SCC with indegree of 0 cannot be reached by any other, thus it must be able to reach every other
    if (candidates.size() > 1) { // Thus if there are more than 1, then the two components cannot reach the other, thus the graph is not valid
      cout << "TIDAK\n";
      return 0;
    }

    int n = candidates[0];
    candidates.pop_back();

    for (auto &i : adj[n]) {
      indeg[i]--;
      if (indeg[i] == 0) {
        candidates.emplace_back(i);
      }
    }
  }

  cout << "YA\n";
  return 0;
}
