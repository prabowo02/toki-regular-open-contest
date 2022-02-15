#include <bits/stdc++.h>
using namespace std;

const int N = 2005;

int n, k;
int t[N];

long long dp[N][N];
long long f(int n, int k) {
  if (k < 0) return 1e18;
  if (n == 0) return k == 0 ? 0 : 1e18;
  long long &ret = dp[n][k];
  if (~dp[n][k]) return dp[n][k];

  ret = 1e18;
  int maxi = 0;
  for (int i = n - 1; i >= 0; --i) {
    maxi = max(maxi, t[i]);
    ret = min(ret, 1LL * maxi * (::n - i) + f(i, k - 1));
  }
  return ret;
}

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &t[i]);
  }

  memset(dp, -1, sizeof dp);

  long long ans = 1e18;
  for (int i = 1; i <= k; ++i) {
    ans = min(ans, f(n, i));
  }
  printf("%lld\n", ans);
  return 0;
}
