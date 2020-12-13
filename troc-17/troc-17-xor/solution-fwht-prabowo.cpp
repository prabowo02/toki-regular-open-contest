// O(N + A log A)

#include <cstdio>

const int MAXA = 2048;
const int MOD = 998244353;

long long cnt[MAXA];

int power(int x, long long y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }
  return ret;
}

void fwht(int n, long long a[]) {
  for (int len = 1; len < n; len <<= 1) {
    for (int i = 0; i < n; i += len << 1) {
      for (int j = 0; j < len; ++j) {
        long long u = a[i + j], v = a[i + j + len];
        a[i + j] = u + v;
        a[i + j + len] = u - v;
      }
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int a; scanf("%d", &a);
    ++cnt[a];
  }

  fwht(MAXA, cnt);
  for (int i = 0; i < MAXA; ++i) cnt[i] *= cnt[i];
  fwht(MAXA, cnt);
  for (int i = 0; i < MAXA; ++i) cnt[i] /= MAXA;

  int ans = power(0, (cnt[0] - n) / 2);
  for (int i = 1; i < MAXA; ++i) {
    ans = 1LL * ans * power(i, cnt[i] / 2) % MOD;
  }
  printf("%d\n", ans);
  return 0;
}
