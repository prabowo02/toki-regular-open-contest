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

  vector<int> dp(4);
  vector<vector<int>> mul(4, vector<int>(4));

  for (int j = 0; j < 2; j++) {
    for (int k = 0; k < 2; k++) {
      mul[j * 2 + k][0 + (k | 0)] = M - 1;
      mul[j * 2 + k][2 + (k | 1)] = (j == 0);
    }
  }

  dp[0] = 1;
  for (int n = N; n > 0; n /= 2) {
    if (n & 1) {
      vector<int> ndp(4);
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          Add(ndp[j], int(1ll * dp[i] * mul[i][j] % MOD));
        }
      }
      swap(dp, ndp);
    }
    vector<vector<int>> nmul(4, vector<int>(4));
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 4; k++) {
          Add(nmul[i][j], int(1ll * mul[i][k] * mul[k][j] % MOD));
        }
      }
    }
    swap(mul, nmul);
  }

  int ans = 0;
  Add(ans, dp[1]);
  Add(ans, dp[3]);

  cout << ans << '\n';
  return 0;
}
