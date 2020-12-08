#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const int MAXA = 100005;
const int MOD = 1000000007;

int n, k;
int a[N];

int cnt[MAXA];

int fact[N], ifact[N];
int C(int n, int k) {
  if (k < 0 || k > n) return 0;
  return 1LL * fact[n] * ifact[k] % MOD * ifact[n-k] % MOD;
}

bitset<MAXA> prime;
char mobius[MAXA];

void init() {
  fact[0] = 1;
  for (int i = 1; i < N; ++i) {
    fact[i] = 1LL * fact[i-1] * i % MOD;
  }

  ifact[N-1] = 230247071; // pow((N-1)!, MOD-2, MOD)
  for (int i = N-2; i >= 0; --i) {
    ifact[i] = 1LL * ifact[i+1] * (i+1) % MOD;
  }

  for (int i = 1; i < MAXA; ++i) {
    mobius[i] = 1; prime[i] = true;

    for (int j = i*2; j < MAXA; j += i) {
      cnt[i] += cnt[j];
    }
  }

  for (int i = 2; i < MAXA; ++i) {
    if (!prime[i]) continue;
    for (int j = i; j < MAXA; j += i) {
      prime[j] = false;
      mobius[j] *= -1;
    }

    for (long long j = 1LL*i*i; j < MAXA; j += 1LL*i*i) {
      mobius[j] = 0;
    }
  }
}

int count_subset_gcd(int g, int k) {
  long long ret = 0;
  for (int i = 1; g*i < MAXA; ++i) {
    ret = (ret + C(cnt[g*i], k) * mobius[i]);
  }
  return ret % MOD;
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

  ans %= MOD;
  if (ans < 0) ans += MOD;
  printf("%lld\n", ans % MOD);
  return 0;
}
