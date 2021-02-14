#include <cstdio>
#include <cstring>

const int N = 41;
const int MOD = 998244353;

int n, m, a, b, c;

int memoC[N][N];
int C(int n, int k) {
  if (~memoC[n][k]) return memoC[n][k];
  if (k == 0 || k == n) return memoC[n][k] = 1;
  return memoC[n][k] = (C(n - 1, k - 1) + C(n - 1, k)) % MOD;
}

int memoPower[N][N];
int power(int n, int m) {
  int &ret = memoPower[n][m];
  if (~ret) return ret;
  if (m == 0) return ret = 1;
  return ret = 1LL * n * power(n, m - 1) % MOD;
}

int memoCount[N][N];
int count(int n, int m) {
  int &ret = memoCount[n][m];
  if (~ret) return ret;
  if (m == 0) return 1;
  return ret = 1LL * n * (n + 1) / 2 * count(n, m - 1) % MOD;
}

int memoCc[N][N];
int countCc(int n, int m) {
  int &ret = memoCc[n][m];
  if (~ret) return ret;
  ret = count(n, m);
  for (int i = 1; i < n; ++i) for (int j = i - 1; j <= m; ++j) {
    ret = (ret - 1LL * countCc(i, j) * count(n - i, m - j) % MOD * C(n - 1, i - 1) % MOD * C(m, j)) % MOD;
  }
  if (ret < 0) ret += MOD;
  return ret;
}

int memoCcs[N][2][N][N];
int countCcs(int num, int nopar, int n, int m) {
  int &ret = memoCcs[num][nopar][n][m];
  if (~ret) return ret;
  if (num == 0) {
    if (nopar) return ret = count(n, m);
    return ret = (n == 0 && m == 0 ? 1 : 0);
  }
  ret = 0;
  for (int i = 1; i <= n; ++i) for (int j = 0; j <= m; ++j) {
    if (j < m) {
      ret = (ret + 1LL * countCc(i, j) * countCcs(num - 1, nopar, n - i, m - j - 1) % MOD * C(n - 1, i - 1) % MOD * C(m, j) % MOD * (m - j) * i) % MOD;
    }
    if (nopar) {
      ret = (ret + 1LL * count(i, j) * countCcs(num, 0, n - i, m - j) % MOD * C(n - 1, i - 1) % MOD * C(m, j)) % MOD;
    }
  }
  return ret;
}

int memo2Edge[N][N];
int count2Edge(int n, int m) {
  int &ret = memo2Edge[n][m];
  if (~ret) return ret;
  ret = countCc(n, m);
  for (int i = 1; i < n; ++i) for (int j = 0; j <= m; ++j) for (int k = 1; k <= n - i; ++k) {
    ret = (ret - 1LL * count2Edge(i, j) * countCcs(k, 0, n - i, m - j) % MOD * C(n - 1, i - 1) % MOD * C(m, j) % MOD * power(i, k)) % MOD;
  }
  if (ret < 0) ret += MOD;
  return ret;
}

int memo2Cc[N][N];
int count2Cc(int n, int m) {
  int &ret = memo2Cc[n][m];
  if (~ret) return ret;
  ret = 0;
  for (int i = 1; i < n; ++i) for (int j = i - 1; j <= m; ++j) {
    ret = (ret + 1LL * countCc(i, j) * countCc(n - i, m - j) % MOD * C(n - 1, i - 1) % MOD * C(m, j) % MOD * i * (n - i)) % MOD;
  }
  return ret;
}

int solve(int n, int m) {
  int ret = 1LL * count(n, m) * c % MOD * m % MOD;
  for (int edge = 0; edge < m; ++edge) {
    for (int i = 2; i <= n; ++i) for (int j = i - 2; j <= edge; ++j) {
      ret = (ret + 1LL * count2Cc(i, j) * count(n - i, edge - j) % MOD * C(n, i) % MOD * C(edge, j) % MOD * count(n, m - edge - 1) % MOD * (a - c)) % MOD;
    }

    for (int i = 1; i <= n; ++i) for (int j = 0; j <= edge; ++j) for (int k = 0; k <= n - i; ++k) {
      ret = (ret + 1LL * count2Edge(i, j) * countCcs(k, 1, n - i, edge - j) % MOD * C(n, i) % MOD * C(edge, j) % MOD * power(i, k) % MOD * i * (i + 1) / 2 % MOD * count(n, m - edge - 1) % MOD * (b - c)) % MOD;
    }
  }
  if (ret < 0) ret += MOD;
  return ret;
}

int inv(int x) {
  int ret = 1;
  for (int y = MOD - 2; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }
  return ret;
}

int main() {
  scanf("%d %d %d %d %d", &n, &m, &a, &b, &c);
  memset(memoC, -1, sizeof memoC);
  memset(memoPower, -1, sizeof memoPower);
  memset(memoCount, -1, sizeof memoCount);
  memset(memoCc, -1, sizeof memoCc);
  memset(memo2Edge, -1, sizeof memo2Edge);
  memset(memoCcs, -1, sizeof memoCcs);
  memset(memo2Cc, -1, sizeof memo2Cc);

  printf("%lld\n", 1LL * solve(n, m) * inv(count(n, m)) % MOD);
  return 0;
}
