#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int N = 5005;

int n, d, a, b;

int p[2][N];
int pre[2][N];

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

  int post = 1, ans = 0;
  for (int it = max(0, n - d - 1 - min(a, b)); it; --it) {
    int pB = 0;
    for (int i = 0; i < n-1; ++i) {
      pB = (pB + p[1][i]) % MOD;
    }

    for (int k = 0; k < 2; ++k) {
      pre[k][0] = p[k][0];
      for (int i = 1; i < n; ++i) pre[k][i] = (pre[k][i-1] + p[k][i]) % MOD;
      for (int i = 0; i < n; ++i) {
        p[k][i] = ((i >= 1 ? pre[k][i-1] : 0) - (i >= d-1 ? pre[k][i-d-1] : 0)) % MOD;
        if (i < n-1 && i + d >= n) {
          p[k][i] = (p[k][i] + pre[k][n-2] - pre[k][n-1 - (i+d-(n-1)) - 1]) % MOD;
        }
        if (p[k][i] < 0) p[k][i] += MOD;
        p[k][i] = 1LL * p[k][i] * id % MOD;
      }

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
