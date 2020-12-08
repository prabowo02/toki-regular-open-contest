#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int P = 67;
const int N = 50005;

int n, q;
char s[N];
int a[N];

int inv[P*3];
int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }

  return ret;
}

int cnt[P*3][3][P*3];
int sum[P*3][3][P*3];
void compute_subsequence_count_sum(int n, char *s, int a[], int p) {
  cnt[1][0][0] = cnt[1][1][0] = cnt[1][2][0] = 1;

  for (int i = 0; i < n; ++i) {
    int idx, pidx;
    if (s[i] == 'b') {
      idx = 0, pidx = 2;
    } else if (s[i] == 'o') {
      idx = 1, pidx = 0;
    } else if (s[i] == 'n') {
      idx = 2, pidx = 1;
    } else {
      continue;
    }

    for (int j = 1; j <= p*3; ++j) {
      (cnt[1][idx][j] += cnt[1][pidx][j-1]) %= MOD;
      sum[1][idx][j] = (1LL * cnt[1][pidx][j-1] * a[i] + sum[1][pidx][j-1] + sum[1][idx][j]) % MOD;
    }
  }

  cnt[1][0][0] = cnt[1][1][0] = cnt[1][2][0] = 0;

  for (int i = 2; i <= p*3; ++i) {
    for (int j = i; j <= p*3; ++j) {
      for (int k = 1; k < j; ++k) {
        for (int l = 0; l < 3; ++l) {
          int idx = (p*3 - k + l) % 3;
          cnt[i][l][j] = (1LL * cnt[i-1][l][k] * cnt[1][idx][j-k] + cnt[i][l][j]) % MOD;
          sum[i][l][j] = (1LL * cnt[i-1][l][k] * sum[1][idx][j-k] + 
                          1LL * sum[i-1][l][k] * cnt[1][idx][j-k] + sum[i][l][j]) % MOD;
        }
      }
    }
  }
}

int main() {
  scanf("%d %d", &n, &q);
  scanf("%s", s);
  for (int i = 0; i < n; ++i) scanf("%d", a + i);

  compute_subsequence_count_sum(n, s, a, P-1);

  for (int i = 1; i < P*3; ++i) inv[i] = power(i, MOD-2);

  while (q--) {
    int p, m;
    scanf("%d %d", &p, &m);

    int ans = 0, cur = 1;

    for (int i = 1; i <= p*3; ++i) {
      cur = 1LL * cur * (m - i + 1) % MOD * inv[i] % MOD;
      ans = (1LL * cur * sum[i][2][p*3] + ans) % MOD;
    }

    printf("%d\n", ans);
  }
  return 0;
}
