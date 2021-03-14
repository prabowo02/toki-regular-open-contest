#include <cstdio>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

const int N = 3005;
const int MOD = 998244353;
const int I2 = (MOD + 1) / 2;

int n;
char s[N];

int balance[N][N];

int twos[N];
int cnt[N];

int dp[N];

int main() {
  scanf("%d", &n);
  scanf("%s", s + 1);

  for (int i = 1; i <= n + 1; ++i) balance[i][i - 1] = 1;
  for (int len = 2; len <= n; ++len) for (int l = 1; l <= n; ++l) {
    int r = l + len - 1;
    if (r > n) break;
    if (s[l] == '0' || s[r] == '1') continue;
    for (int k = l + 1; k <= r; k += 2) {
      if (s[k] == '1') continue;
      balance[l][r] = (balance[l][r] + 1LL * balance[l + 1][k - 1] * balance[k + 1][r]) % MOD;
    }
  }

  cnt[0] = 1;
  for (int i = 1; i <= n; ++i) {
    if (s[i] == '1') continue;
    for (int j = 1; j <= i; j += 2) {
      cnt[i] = (cnt[i] + 1LL * balance[i - j + 1][i - 1] * cnt[i - j]) % MOD;
    }
  }

  for (int i = 1; i <= n; ++i) {
    if (s[i] == '1') continue;
    for (int j = 1; j <= i; j += 2) {
      dp[i] = (dp[i] + 1LL * dp[i - j] * balance[i - j + 1][i - 1] + 1LL * balance[i - j + 1][i - 1] * (j/2 + 1) % MOD * cnt[i - j]) % MOD;
    }
  }

  twos[0] = 1;
  for (int i = 1; i <= n; ++i) twos[i] = (s[i] == '?' ? 2LL : 1LL) * twos[i - 1] % MOD;

  for (int i = 1; i <= n; ++i) {
    if (s[i] != '0') dp[i] = (1LL * dp[i] + dp[i - 1] + twos[i - 1]) % MOD;

    if (s[i] != '1') for (int j = 2; j <= i; j += 2) {
      if (s[i - j + 1] == '0') continue;
      dp[i] = (dp[i] + 1LL * dp[i - j] * balance[i - j + 2][i - 1] + 1LL * balance[i - j + 2][i - 1] * (j/2) % MOD * twos[i - j]) % MOD;
    }
  }

  int ans = dp[n];
  for (int i = 1; i <= n; ++i) if (s[i] == '?') ans = 1LL * ans * I2 % MOD;
  ans = (n + MOD - ans) % MOD;
  
  printf("%d\n", ans);
  return 0;
}
