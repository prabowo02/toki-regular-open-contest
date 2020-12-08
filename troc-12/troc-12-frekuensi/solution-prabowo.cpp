#include <bits/stdc++.h>
using namespace std;

const int N = 252;

int n, l, r;
int a[N][N];

int pre1[N][N][N];
int pre2[N][N][N];

int get1(int k, int x, int y) {
  if (x > n) y -= x - n, x = n;
  if (y > n) x -= y - n, y = n;
  if (x < 0 || y < 0) return 0;

  return pre1[k][x][y];
}

int get2(int k, int x, int y) {
  if (y < 0) x += y, y = 0;
  if (x > n) y += x - n, x = n;
  if (x < 0 || y > n) return 0;

  return pre2[k][x][y];
}

inline int get(int k, int i, int j, int d) {
  return get1(k, i, j+d) - get1(k, i-d, j) + get2(k, i, j-d) - get2(k, i-d-1, j+1)
       + get1(k, i+d, j) - get1(k, i, j-d) + get2(k, i+d-1, j+1) - get2(k, i, j+d);
}

int main() {
  scanf("%d %d %d", &n, &l, &r);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      scanf("%d", &a[i][j]);
      pre1[a[i][j]][i][j] = 1;
      pre2[a[i][j]][i][j] = 1;
    }
  }

  for (int k = 1; k < N-1; ++k) {
    for (int i = 1; i <= n; ++i) {
      pre2[k][i][0] += pre2[k-1][i][0] + pre2[k][i-1][1] - pre2[k-1][i-1][1];
      for (int j = 1; j <= n; ++j) {
        pre1[k][i][j] += pre1[k-1][i][j] + pre1[k][i-1][j-1] - pre1[k-1][i-1][j-1];
        pre2[k][i][j] += pre2[k-1][i][j] + pre2[k][i-1][j+1] - pre2[k-1][i-1][j+1];
      }
    }
  }

  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      for (int d = 1; d <= n*2 - 2; ++d) {
        int k = min(N-2, r*d / a[i][j]);
        int cnt = get(k, i, j, d);

        if (a[i][j] > 0) {
          k = min(N-2, l*d / a[i][j] - (l*d % a[i][j] == 0));
          if (k >= 0) cnt -= get(k, i, j, d);
        }

        ans += cnt * cnt;
      }
    }
  }

  printf("%lld\n", ans);
  return 0;
}
