#include <bits/stdc++.h>
using namespace std;

using lint = long long;
const lint INF = 2e18;

lint Solve(int N, lint C, vector<int> P, vector<int> D) {
  vector<vector<int>> adj(N);
  for (int i = 1; i < N; i++) {
    adj[P[i]].emplace_back(i);
  }
  vector<lint> dp(N);
  const auto Dfs = [&](const auto &self, int u, int sum, lint add) -> lint {
    for (auto v : adj[u]) {
      add += dp[v];
    }
    lint res = C + 1ll * sum * sum + add;
    for (auto v : adj[u]) {
      res = min(res, self(self, v, sum + D[v], add - dp[v]));
    }
    return res;
  };
  for (int u = N - 1; u >= 0; u--) {
    dp[u] = Dfs(Dfs, u, 0, 0);
  }
  return dp[0];
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N;
  lint C;
  cin >> N >> C;

  vector<int> P(N), D(N);
  for (int i = 1; i < N; i++) {
    cin >> P[i] >> D[i];
    P[i]--;
  }

  cout << Solve(N, C, P, D) << '\n';
  return 0;
}
