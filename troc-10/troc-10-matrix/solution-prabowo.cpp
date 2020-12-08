#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int n, m, p;
int a[N][N];

int pre[N][N];
int getPre(int x, int y) { return x < 0 || y < 0 ? 0 : pre[x][y]; }

int main() {
  scanf("%d %d %d", &n, &m, &p);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      scanf("%d", &a[i][j]);
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      pre[i][j] = getPre(i-1, j) + getPre(i, j-1) - getPre(i-1, j-1);
      a[i][j] -= pre[i][j] - getPre(i-p, j) - getPre(i, j-p) + getPre(i-p, j-p);

      if (a[i][j] < 0) return 0 * printf("TIDAK\n");
      if ((i > n-p || j > m-p) && a[i][j] != 0) return 0 * printf("TIDAK\n");

      pre[i][j] += a[i][j];
    }
  }

  printf("YA\n"); 
  return 0;
}
