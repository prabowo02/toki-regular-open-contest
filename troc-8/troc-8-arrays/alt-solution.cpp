#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
int n, k;
int a[4][N];

int sum[N*N];

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 0; i < 4; ++i) for (int j = 0; j < n; ++j) {
    scanf("%d", &a[i][j]);
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      sum[i*n + j] = a[0][i] + a[1][j];
    }
  }
  sort(sum, sum + n*n);

  long long ans = 0;
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
    ans += upper_bound(sum, sum + n*n, k - a[2][i] - a[3][j]) - sum;
  }
  printf("%lld\n", ans);

  return 0;
}
