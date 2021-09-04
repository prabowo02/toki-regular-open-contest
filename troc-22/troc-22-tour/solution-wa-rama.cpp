#include <bits/stdc++.h>
using namespace std;

using lint = long long;
const lint INF = 2e18;

lint Solve(int N, lint C, vector<int> P, vector<int> D) {
  vector<vector<int>> adj(N);
  for (int i = 1; i < N; i++) {
    adj[P[i]].emplace_back(i);
  }
  const int L = 1300;
  vector<lint> dp(N);
  vector<tuple<int, int, lint>> que;
  vector<int> biggest(N);
  iota(begin(biggest), end(biggest), 0);
  sort(begin(biggest), end(biggest), [&](int u, int v) {
    return adj[u].size() > adj[v].size();
  });
  vector<int> big(N);
  for (int i = 0; i < N && i < L; i++) {
    big[biggest[i]] = 1;
  }
  for (int node = N - 1; node >= 0; node--) {
    lint res = INF;
    que.clear();
    que.emplace_back(tuple(node, 0, 0));
    for (int i = 0; i < int(que.size()); i++) {
      auto [u, sum, add] = que[i];
      for (auto v : adj[u]) {
        add += dp[v];
      }
      res = min(res, C + 1ll * sum * sum + add);
      for (auto v : adj[u]) {
        if (big[node] == 1 || que.size() < L) {
          que.emplace_back(tuple(v, sum + D[v], add - dp[v]));
        } else {
          break;
        }
      }
    }
    dp[node] = res;
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
