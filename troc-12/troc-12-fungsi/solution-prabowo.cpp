#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int LG = 30;

int a, b, ka, kb, la, lb;

int par[LG][N];
long long sum[LG][N];

void init() {
  for (int i = 0; i < a; ++i) {
    for (int j = 0; j < b; ++j) {
      int ni = (i == ka ? (i-la)%a : j == kb ? (i-lb)%a : i-1);
      int nj = (i == ka ? (j-la)%b : j == kb ? (j-lb)%b : j-1);
      if (ni < 0) ni += a;
      if (nj < 0) nj += b;

      par[0][i*b + j] = ni*b + nj;
      sum[0][i*b + j] = (i == ka ? la : j == kb ? lb : 1);
    }
  }

  for (int i = 1; i < LG; ++i) {
    for (int j = a*b; j--; ) {
      par[i][j] = par[i-1][par[i-1][j]];
      sum[i][j] = sum[i-1][j] + sum[i-1][par[i-1][j]];
    }
  }
}

int getDepth(int x) {
  int cur = (x%a)*b + (x%b);
  int depth = 0;
  for (int i = LG; i--; ) {
    if (sum[i][cur] >= x) continue;
    depth |= 1 << i;
    x -= sum[i][cur];
    cur = par[i][cur];
  }

  return depth;
}

int lca(int x, int y) {
  int dx = getDepth(x), dy = getDepth(y);
  if (dx < dy) {
    swap(x, y);
    swap(dx, dy);
  }
  int cx = (x%a)*b + x%b, cy = (y%a)*b + y%b;

  while (dx != dy) {
    int up = __builtin_ctz(dx - dy);
    x -= sum[up][cx];
    dx -= 1 << up;
    cx = par[up][cx];
  }

  if (x == y) return x;

  for (int i = LG; i--; ) {
    if ((1 << i) > dx) continue;
    if (par[i][cx] == par[i][cy]) continue;
    x -= sum[i][cx], y -= sum[i][cy];
    dx -= 1 << i, dy -= 1 << i;
    cx = par[i][cx], cy = par[i][cy];
  }

  if (dx > 0 && x - sum[0][cx] == y - sum[0][cy]) return x - sum[0][cx];
  return -1;
}

int main() {
  scanf("%d %d %d %d %d %d", &a, &b, &ka, &kb, &la, &lb);
  init();
  int q;
  scanf("%d", &q);
  while (q--) {
    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d\n", lca(x, y));
  }
  return 0;
}
