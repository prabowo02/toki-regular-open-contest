#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N, M;
  cin >> N >> M;

  vector<vector<pair<int, int>>> adj(N);
  while (M--) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  int K;
  cin >> K;

  vector<int> P(K), A(K);
  for (int i = 0; i < K; i++) {
    cin >> P[i] >> A[i];
    P[i]--;
  }

  const auto Solve = [&](int L) {
    vector<int> dist(N, 1e9 + 100);
    priority_queue<pair<int, int>> pq;
    for (int i = 0; i < L; i++) {
      dist[i] = 0;
      pq.emplace(0, i);
    }
    while (!pq.empty()) {
      auto [d, u] = pq.top();
      pq.pop();
      if (dist[u] != -d) {
        continue;
      }
      for (auto [v, w] : adj[u]) {
        if (dist[v] > dist[u] + w) {
          dist[v] = dist[u] + w;
          pq.emplace(-dist[v], v);
        }
      }
    }
    int res = -1;
    for (int i = 0; i < K; i++) {
      if (dist[P[i]] > A[i]) {
        res = max(res, i);
      }
    }
    return res;
  };

  int lo = 0, hi = N - 1;
  while (lo < hi) {
    int md = (lo + hi + 1) / 2;
    if (Solve(md) != -1) {
      lo = md;
    } else {
      hi = md - 1;
    }
  }

  cout << Solve(lo) + 1 << '\n';
  return 0;
}
