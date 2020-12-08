#include <bits/stdc++.h>
using namespace std;

int Solve(int N, int M, vector<int> X, vector<int> Y, vector<long long> Z) {
  const long long INF = 1e15;
  const int MOD = 1e9 + 7;

  // Modular addition
  const auto Add = [&](int &a, int b) {
    a += b;
    a -= (a >= MOD) * MOD;
  };

  // Global variables for DivideConquer()  
  vector<int> position(N);
  vector<long long> distX(N);
  vector<long long> distY(N);
  vector<vector<pair<int, long long>>> adj(N);
  priority_queue<pair<long long, int>, 
      vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

  // Add extra edges with weight INF to split the circle into triangles    
  const auto BuildTriangles = [&]() {
    vector<vector<int>> ints(N);
    for (int i = 0; i < M; i++) {
      ints[X[i]].emplace_back(Y[i]);
    }

    set<int> s;
    vector<int> bound(N);
    for (int i = 0; i < N; i++) {
      while (!s.empty() && *begin(s) <= i) {
        s.erase(begin(s));
      }
      bound[i] = (s.empty() ? (N - 1) : *begin(s));
      for (auto j : ints[i]) {
        s.emplace(j);
      }
    }

    s.clear();
    for (int i = N - 1; i >= 0; i--) {
      while (!s.empty() && *begin(s) <= bound[i]) {
        X.emplace_back(i);
        Y.emplace_back(*begin(s));
        Z.emplace_back(INF);
        if (next(begin(s)) != end(s) && *next(begin(s)) <= bound[i]) {
          s.erase(begin(s));
        } else {
          break;
        }
      }
      for (auto j : ints[i]) {
        while (!s.empty() && *begin(s) < j) {
          s.erase(begin(s));
        }
      }
      s.emplace(i);
    }

    M = (int) X.size();
  };

  // Delete duplicate edges
  const auto MakeUnique = [&]() {
    map<pair<int, int>, long long> edges;
    for (int i = 0; i < M; i++) {
      if (edges.count({X[i], Y[i]}) == 0 || edges[{X[i], Y[i]}] > Z[i]) {
        edges[{X[i], Y[i]}] = Z[i];
      }
    }

    X.clear();
    Y.clear();
    Z.clear();

    for (auto [e, w] : edges) {
      auto [u, v] = e;
      X.emplace_back(u);
      Y.emplace_back(v);
      Z.emplace_back(w);
    }

    M = (int) X.size();
  };

  // Divide and Conquer to count sum of all-pairs shortest paths
  const auto DivideConquer = [&](const auto &self, vector<int> &nodes, vector<int> &edges) {
    if (nodes.size() == 3) {
      assert(edges.size() == 3);
      return int((min(Z[edges[0]], Z[edges[1]] + Z[edges[2]]) + 
                  min(Z[edges[1]], Z[edges[0]] + Z[edges[2]]) + 
                  min(Z[edges[2]], Z[edges[0]] + Z[edges[1]])) % MOD);
    }

    // Dijkstra on induced graph
    const auto Dijkstra = [&](int s, vector<long long> &dist) {
      for (auto i : nodes) {
        dist[i] = INF;
      }
      
      for (auto i : edges) {
        adj[X[i]].emplace_back(Y[i], Z[i]);
        adj[Y[i]].emplace_back(X[i], Z[i]);
      }

      dist[s] = 0;
      pq.emplace(0, s);

      while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (dist[u] != d) {
          continue;
        }
        for (auto [v, w] : adj[u]) {
          if (dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            pq.emplace(dist[v], v);
          }
        }
      }

      for (auto i : nodes) {
        assert(dist[i] != INF);
        adj[i].clear();
      }
    };

    // Count sum of shortest paths between different parts
    const auto Merge = [&](vector<int> first, vector<int> second, int split) {
      first.erase(find(begin(first), end(first), X[split]));
      first.erase(find(begin(first), end(first), Y[split]));

      second.erase(find(begin(second), end(second), X[split]));
      second.erase(find(begin(second), end(second), Y[split]));

      int res = 0;
      for (auto i : first) {
        for (auto j : second) {
          Add(res, int(min(distX[i] + distX[j], distY[i] + distY[j]) % MOD));
        }
      }

      return res;
    };
    
    int n = (int) nodes.size();
    for (int i = 0; i < n; i++) {
      position[nodes[i]] = i;
    }

    int split = -1;
    for (auto i : edges) {
      int split_cost = (split == -1 ? -1 : abs(position[X[split]] - position[Y[split]]));
      int current_cost = abs(position[X[i]] - position[Y[i]]);
      if (split == -1 || max(split_cost, n - split_cost) > max(current_cost, n - current_cost)) {
        split = i;
      }
    }

    assert(split != -1);
    Dijkstra(X[split], distX);
    Dijkstra(Y[split], distY);
    Z[split] = distX[Y[split]];

    vector<int> first_node;
    vector<int> first_edge;
    vector<int> second_node;
    vector<int> second_edge;

    for (auto i : nodes) {
      if (i == X[split] || i == Y[split]) {
        first_node.emplace_back(i);
        second_node.emplace_back(i);
      } else if (position[X[split]] < position[i] && position[i] < position[Y[split]]) {
        first_node.emplace_back(i);
      } else {
        second_node.emplace_back(i);
      }
    }

    for (auto i : edges) {
      if (i == split) {
        first_edge.emplace_back(i);
        second_edge.emplace_back(i);
      } else if (position[X[split]] <= position[X[i]] && position[Y[i]] <= position[Y[split]]) {
        first_edge.emplace_back(i);
      } else {
        second_edge.emplace_back(i);
      }
    }

    nodes.clear();
    edges.clear();
    nodes.shrink_to_fit();
    edges.shrink_to_fit();

    int res = 0;

    Add(res, Merge(first_node, second_node, split));
    Add(res, self(self, first_node, first_edge));
    Add(res, self(self, second_node, second_edge));
    Add(res, MOD - int(Z[split] % MOD));

    return res;
  };

  BuildTriangles();
  MakeUnique();

  vector<int> nodes(N), edges(M);
  iota(begin(nodes), end(nodes), 0);
  iota(begin(edges), end(edges), 0);

  int ans = DivideConquer(DivideConquer, nodes, edges);

  return ans;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N, M;
  cin >> N >> M;

  vector<int> X, Y;
  vector<long long> Z;
  for (int i = 0; i < N; i++) {
    int w;
    cin >> w;
    if (i + 1 == N) {
      X.emplace_back(0);
      Y.emplace_back(N - 1);
      Z.emplace_back(w);
    } else {
      X.emplace_back(i);
      Y.emplace_back(i + 1);
      Z.emplace_back(w);
    }
  }

  for (int i = 0; i < M; i++) {
    int x, y, z;
    cin >> x >> y >> z;
    x--, y--;
    X.emplace_back(x);
    Y.emplace_back(y);
    Z.emplace_back(z);
  }

  cout << Solve(N, N + M, X, Y, Z) << '\n';
  return 0;
}
