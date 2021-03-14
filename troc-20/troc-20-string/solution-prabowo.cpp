#include <bits/stdc++.h>
using namespace std;

const int N = 3005;
const int MOD = 998244353;
const int I2 = (MOD + 1) / 2;

int n;
char s[N];

int dp[N][N][2];
int f(int n, int bal, int st) {
  if (n == 0) return st == 1 || bal == 0;
  if (~dp[n][bal][st]) return dp[n][bal][st];

  int ret = 0;

  if (st == 0) {
    if (s[n] != '1') {
      if (bal == 0) ret = (ret + f(n - 1, 0, 1)) % MOD;
      ret = (ret + f(n - 1, bal + 1, 0)) % MOD;
    }
    if (s[n] != '0') ret = (ret + f(n - 1, max(bal - 1, 0), 0)) % MOD;
  } else if (st == 1) {
    if (s[n] != '1') ret = (ret + f(n - 1, bal + 1, 1)) % MOD;
    if (s[n] != '0' && bal > 0) ret = (ret + f(n - 1, bal - 1, 1)) % MOD;
  }
  return dp[n][bal][st] = ret;
}

int dp2[N][N][2];
int g(int n, int bal, int st) {
  if (n == 0) return 0;
  if (~dp2[n][bal][st]) return dp2[n][bal][st];

  int ret = 0;

  if (st == 0) {
    if (s[n] != '1') {
      if (bal == 0) ret = (ret + g(n - 1, 0, 1) + f(n - 1, 0, 1)) % MOD;
      ret = (ret + g(n - 1, bal + 1, 0));
    }
    if (s[n] != '0') ret = (1LL * ret + g(n - 1, max(bal - 1, 0), 0) + f(n - 1, max(bal - 1, 0), 0)) % MOD;
  } else if (st == 1) {
    if (s[n] != '1') ret = (ret + g(n - 1, bal + 1, 1) + f(n - 1, bal + 1, 1)) % MOD;
    if (s[n] != '0' && bal > 0) ret = (ret + g(n - 1, bal - 1, 1)) % MOD;
  }

  return dp2[n][bal][st] = ret;
}

int main() {
  scanf("%d", &n);
  scanf("%s", s + 1);

  memset(dp, -1, sizeof dp);
  memset(dp2, -1, sizeof dp2);
  
  int ans = g(n, 0, 0);
  for (int i = 1; i <= n; ++i) if (s[i] == '?') ans = 1LL * ans * I2 % MOD;

  ans = (n + MOD - ans) % MOD;

  printf("%d\n", ans);
  return 0;
}
