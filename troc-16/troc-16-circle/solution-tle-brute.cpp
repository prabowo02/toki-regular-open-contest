#include <bits/stdc++.h>
using namespace std;

int Solve(int N, int M, vector<int> X, vector<int> Y, vector<long long> Z) {
  const long long INF = 1e15;
  const int MOD = 1e9 + 7;

  const auto Add = [&](int &a, int b) {
    a += b;
    a -= (a >= MOD) * MOD;
  };

  const auto Dijkstra = [&](int s) {
    vector<vector<pair<int, long long>>> adj(N);
    for (int i = 0; i < M; i++) {
      adj[X[i]].emplace_back(Y[i], Z[i]);
      adj[Y[i]].emplace_back(X[i], Z[i]);
    }

    vector<long long> dist(N, INF);
    priority_queue<pair<long long, int>, 
        vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    
    dist[s] = 0;
    pq.emplace(dist[s], s);
    
    while (!pq.empty()) {
      auto [d, u] = pq.top(); pq.pop();
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

    int sum = 0;
    for (int i = s + 1; i < N; i++) {
      Add(sum, int(dist[i] % MOD));
    }
    return sum;
  };

  int ans = 0;
  for (int i = 0; i < N; i++) {
    Add(ans, Dijkstra(i));
  }
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
