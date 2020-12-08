// Author   : rama_pang
// Problem  : troc-12-toko
// Time     : O(N log N)
// Memory   : O(N)

#include <bits/stdc++.h>
using namespace std;

int N, D;
vector<int> deg;
vector<vector<int>> adj;

void Read() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);

  cin >> N >> D;
  adj.resize(N);
  deg.resize(N);
  for (int i = 0; i < N; i++) {
    int W;
    cin >> W;
    while (W--) {
      int P;
      cin >> P;
      adj[--P].emplace_back(i);
      deg[i]++;
    }
  }
}

void Solve() {
  vector<int> ans;
  set<int> candidates;

  auto GetCandidate = [&candidates](int days) {
    auto it = candidates.lower_bound(((-1ll * days * D) % N + N) % N);
    if (it == end(candidates)) it = begin(candidates);
    int res = *it;
    candidates.erase(it);
    return res;
  };

  for (int i = 0; i < N; i++) {
    if (deg[i] == 0) {
      candidates.emplace(i);
    }
  }

  for (int days = 0; !candidates.empty(); days++) {
    int u = GetCandidate(days);
    ans.emplace_back((u + 1ll * days * D) % N);
    for (auto v : adj[u]) {
      if ((--deg[v]) == 0) {
        candidates.emplace(v);
      }
    }
  }

  for (int i = 0; i < N; i++) {
    cout << ans[i] << " \n"[i == N - 1];
  }
}

int main() {
  Read();
  Solve();
  return 0;
}
