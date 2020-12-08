#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <cstdio>

const int MOD = 998244353;
const int N = 5005;

int n, d, a, b;

int p[2][N];
int np[2][N];

int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }
  return ret;
}

int main() {
  scanf("%d %d %d %d", &n, &d, &a, &b);
  p[0][--a] = p[1][--b] = 1;

  int id = power(d, MOD-2);

  int post = 1, ans = 0, it = n - d - 1 - (a < b ? a : b);
  for (it = (it > 0 ? it : 0); it; --it) {
    int pB = 0;
    for (int i = 0; i < n-1; ++i) {
      pB = (pB + p[1][i]) % MOD;
    }

    for (int k = 0; k < 2; ++k) {
      for (int i = 0; i < n; ++i) np[k][i] = 0;
      for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= d; ++j) {
          int nx = (i + j < n ? i + j : (n-1) - (i + j - (n-1)));
          np[k][nx] = (1LL * p[k][i] * id + np[k][nx]) % MOD;
        }
      }
      for (int i = 0; i < n; ++i) p[k][i] = np[k][i];
      // for (int i = 0; i < n; ++i) cerr << p[k][i] << " "; cerr << endl;
    }

    ans = (1LL * pB * p[0][n-1] + ans) % MOD;
    p[0][n-1] = p[1][n-1] = 0;
  }

  int r = 1LL * (d-1) * (d-1) % MOD * id % MOD * id % MOD;
  r = (1 - r) % MOD; if (r < 0) r += MOD;
  r = power(r, MOD - 2);

  int pA = 0, pB = 0;
  for (int i = 0; i < n-1; ++i) {
    pA = (pA + p[0][i]) % MOD;
    pB = (pB + p[1][i]) % MOD;
  }

  ans = (1LL * pA * pB % MOD * id % MOD * r + ans) % MOD;

  printf("%d\n", ans);
  return 0;
}
