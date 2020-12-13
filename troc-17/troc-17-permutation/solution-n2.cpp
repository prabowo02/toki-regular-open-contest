#include <cstdio>

const int MAXN = 2005;
const int MOD = 998244353;

int n, k;

bool fixed[MAXN];
int dp[MAXN][MAXN];

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 0; i < k; ++i) {
    int a;
    scanf("%*d %d", &a);
    fixed[a] = true;
  }
  
  for (int delta = 0; delta <= n; ++delta) dp[0][delta] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int delta = i; delta <= n; ++delta) {
      if (fixed[i]) {
        dp[i][delta] = dp[i-1][delta-1];
      } else {
        dp[i][delta] = 1LL * (dp[i-1][delta] - dp[i-1][delta-1]) * (delta - i + 1) % MOD;
        dp[i][delta] = (dp[i][delta] + dp[i-1][delta - 1]) % MOD;
        if (dp[i][delta] < 0) dp[i][delta] += MOD;
      }
      dp[i][delta] = (dp[i][delta] + dp[i][delta-1]) % MOD;
    }
  }

  int ans = dp[n][n] - dp[n][n-1];
  if (ans < 0) ans += MOD;
  printf("%d\n", ans);
  return 0;
}
