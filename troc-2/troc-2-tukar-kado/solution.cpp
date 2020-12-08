#include <bits/stdc++.h>

using namespace std;

const int N = 2048, mod = 1e9 + 7;

int C[N][N], fac[N];
int n, x[N];

inline int multiply(int a, int b) {
  return 1LL * a * b % mod;
}

inline int add(int a, int b) {
  a += b;
  if (a >= mod)
    a -= mod;
  return a;
}

int main() {
  for (int i = 0; i < N; ++i) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; ++j)
      C[i][j] = add(C[i-1][j-1], C[i-1][j]);
  }
  fac[0] = 1;
  for (int i = 1; i < N; ++i) {
    fac[i] = multiply(fac[i-1], i);
  }
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d", x+i);
  if (n == 2) {
    printf("%d\n", x[0] == x[1] ? fac[x[0]] : 0);
    return 0;
  }
  int ans = 0;
  for (int awal = 0; awal <= x[n-1]; ++awal) {
    int cur = multiply(C[x[n-1]][awal], fac[awal]);
    int sisa = x[0] - awal;
    for (int i = 0; i + 1 < n; ++i) {
      if (sisa < 0 || sisa > x[i]) {
        cur = 0;
        break;
      }
      cur = multiply(cur, C[x[i]][sisa]);
      cur = multiply(cur, fac[sisa]);
      sisa = x[i+1] - sisa;
    }
    if (sisa != awal)
      cur = 0;
    ans = add(ans, cur);
  }
  printf("%d\n", ans);
  return 0;
}