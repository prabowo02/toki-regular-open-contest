#include <bits/stdc++.h>
using namespace std;

const int N = 303;

int n, m;
int a[N][N];

bool island[N][N];

tuple<int, int, int> depths[N*N];

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

int par[N*N];
int root(int u) {
  if (u == par[u]) return u;
  return par[u] = root(par[u]);
}

bool merge(int u, int v) {
  if (root(u) == root(v)) return false;
  par[par[u]] = par[v];
  return true;
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      scanf("%d", &a[i][j]);
      depths[i*m + j] = make_tuple(a[i][j], i, j);
      par[i*m + j] = i*m + j;
    }
  }

  sort(depths, depths + n*m, greater<tuple<int, int, int>>());

  int cnt = 0, ans = 0;
  for (int i = 0; i < n*m; ++i) {
    int d, x, y;
    tie(d, x, y) = depths[i];

    island[x][y] = true; ++cnt;
    for (int dir = 0; dir < 4; ++dir) {
      int nx = x + dx[dir], ny = y + dy[dir];
      if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
      if (!island[nx][ny]) continue;

      if (merge(x*m + y, nx*m + ny)) --cnt;
    }

    ans = max(ans, cnt);
  }

  printf("%d\n", ans);
  return 0;
}
