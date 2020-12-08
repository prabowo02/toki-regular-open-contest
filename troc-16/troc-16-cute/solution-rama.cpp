#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N, M;
  cin >> N >> M;

  const int MOD = 1e9 + 7;
  const auto Add = [&](int &a, int b) {
    a += b;
    a -= (a >= MOD) * MOD;
  };

  vector<vector<int>> dp(2, vector<int>(2));

  dp[0][0] = 1;
  for (int i = 0; i < N; i++) {
    vector<vector<int>> ndp(2, vector<int>(2));
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        Add(ndp[0][k | 0], int(1ll * dp[j][k] * (M - 1) % MOD));
        Add(ndp[1][k | 1], int((j == 0) * dp[j][k]));
      }
    }
    swap(dp, ndp);
  }

  int ans = 0;
  Add(ans, dp[0][1]);
  Add(ans, dp[1][1]);

  cout << ans << '\n';
  return 0;
}
