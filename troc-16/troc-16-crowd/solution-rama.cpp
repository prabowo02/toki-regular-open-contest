#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N;
  cin >> N;
  
  vector<tuple<int, int, int>> A;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int a;
      cin >> a;
      if (i < j) {
        A.push_back({a, i, j});
      }
    }
  }

  sort(begin(A), end(A));
  vector<int> parent(2 * N);
  iota(begin(parent), end(parent), 0);
  const auto Find = [&](const auto &self, int u) -> int {
    return parent[u] = (parent[u] == u ? u : self(self, parent[u]));
  };

  int ans = 0;
  for (auto [w, u, v] : A) {
    parent[Find(Find, u)] = Find(Find, v + N);
    parent[Find(Find, u + N)] = Find(Find, v);

    if (Find(Find, u) == Find(Find, u + N)) {
      ans = w;
      break;
    }
  }

  cout << ans << '\n';
  return 0;
}
