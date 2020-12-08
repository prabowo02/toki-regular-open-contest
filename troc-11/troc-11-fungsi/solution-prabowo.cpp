#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const int MAXA = 100005;
const int MOD = 1000000007;

int n, k;
int a[N];

int cnt[MAXA];

int comb[N][N];
int C(int n, int k) {
  if (k < 0 || k > n) return 0;
  return comb[n][k];
}

void init() {
  for (int i = 0; i < N; ++i) {
    comb[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      comb[i][j] = (comb[i-1][j] + comb[i-1][j-1]) % MOD;
    }
  }

  for (int i = 1; i < MAXA; ++i) {
    for (int j = i*2; j < MAXA; j += i) {
      cnt[i] += cnt[j];
    }
  }
}

int dp[MAXA];
int count_subset_gcd(int g, int k) {
  int len = (MAXA + g - 1) / g;
  for (int i = 1; i < len; ++i) {
    dp[i] = C(cnt[g*i], k);
  }

  for (int i = len-1; i > 0; --i) {
    for (int j = i*2; j < len; j += i) {
      dp[i] = (dp[i] + MOD - dp[j]) % MOD;
    }
  }

  return dp[1];
}

int main() {  
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    ++cnt[a[i]];
  }

  init();

  long long ans = 0;
  for (int i = 1; i <= k; ++i) {
    if (k % i == 0) ans += count_subset_gcd(i, k/i);
  }

  printf("%lld\n", ans % MOD);
  return 0;
}
