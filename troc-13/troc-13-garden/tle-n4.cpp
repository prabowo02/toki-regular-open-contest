#include <bits/stdc++.h>
using namespace std;

const int N = 303;

int n, m;
int a[N][N];

int depths[N*N];

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

bool vis[N][N];
void bfs(int x, int y, int lim) {
  queue<pair<int, int>> q;
  q.push({x, y});
  vis[x][y] = true;

  while (q.size()) {
    int x, y;
    tie(x, y) = q.front();
    q.pop();

    for (int k = 0; k < 4; ++k) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
      if (a[nx][ny] < lim) continue;
      if (vis[nx][ny]) continue;
      vis[nx][ny] = true;
      q.push({nx, ny});
    }
  }
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      scanf("%d", &a[i][j]);
      depths[i*m + j] = a[i][j];
    }
  }

  sort(depths, depths + n*m);
  int size_depths = unique(depths, depths + n*m) - depths;

  int ans = 0;
  for (int k = 0; k < size_depths; ++k) {
    int cnt = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) vis[i][j] = false;

    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
      if (vis[i][j]) continue;
      if (a[i][j] < depths[k]) continue;

      bfs(i, j, depths[k]);
      ++cnt;
    }

    ans = max(ans, cnt);
  }

  printf("%d\n", ans);
  return 0;
}