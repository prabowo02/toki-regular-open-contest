#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int Q = 100005;

int n, m, q;
int a[N][N];

tuple<int, int, int> benteng[N*N];
tuple<int, int, int, int> queries[Q];

pair<int, int> par[N][N];

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

pair<int, int> root(pair<int, int> p) {
  int x, y; tie(x, y) = p;
  if (par[x][y] == p) return par[x][y];
  return par[x][y] = root(par[x][y]);
}

void merge(pair<int, int> p, pair<int, int> q) {
  pair<int, int> rp = root(p);
  pair<int, int> rq = root(q);
  
  if (rp == rq) return;
  if (rp.first + rp.second < rq.first + rq.second) {
    par[rq.first][rq.second] = rp;
  } else {
    par[rp.first][rp.second] = rq;
  }
}

int ans[Q];

void init() {
  sort(queries, queries + q);
  sort(benteng, benteng + n*m);

  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    par[i][j] = {i, j};
  }
}

int main() {
  scanf("%d %d %d", &n, &m, &q);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      scanf("%d", &a[i][j]);
      benteng[i*m + j] = make_tuple(a[i][j], i, j);
    }
  }

  for (int i = 0; i < q; ++i) {
    int x, y, l;
    scanf("%d %d %d", &x, &y, &l);
    --x, --y;
    queries[i] = make_tuple(l, x, y, i);
  }

  init();

  int idx = 0;
  for (int i = 0; i < q; ++i) {
    int x, y, l, qi;
    tie(l, x, y, qi) = queries[i];
    while (idx < n*m) {
      int z, x, y;
      tie(z, x, y) = benteng[idx];
      if (z > l) break;

      for (int k = 0; k < 4; ++k) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

        if (a[nx][ny] <= a[x][y]) merge({x, y}, {nx, ny});
      }

      ++idx;
    }

    pair<int, int> nearest = root({x, y});
    ans[qi] = nearest.first + nearest.second;
  }

  for (int i = 0; i < q; ++i) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
