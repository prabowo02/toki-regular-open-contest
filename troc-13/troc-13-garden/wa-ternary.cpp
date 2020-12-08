#include <bits/stdc++.h>
using namespace std;

const int N = 303;

int n, m;
int a[N][N];

bool island[N][N];

vector<int> depths;

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

int check(int d) {
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) par[i*m + j] = i*m + j;

  int ret = 0, cnt = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (a[i][j] <= d) continue;
      ++cnt;

      if (i > 0 && a[i-1][j] > d) cnt -= merge(i*m + j, (i-1)*m + j);
      if (j > 0 && a[i][j-1] > d) cnt -= merge(i*m + j, i*m + j-1);
    }
  }

  return cnt;
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      scanf("%d", &a[i][j]);
      depths.push_back(a[i][j]);
    }
  }

  depths.push_back(-1);
  sort(depths.begin(), depths.end());
  depths.resize(unique(depths.begin(), depths.end()) - depths.begin());

  int l = 0, r = (int) depths.size() - 1, ans = -1;
  while (l <= r) {
    int mid1 = (l*2 + r) / 3;
    int mid2 = (l + r*2) / 3;

    int c1 = check(mid1), c2 = check(mid2);
    if (c1 < c2) {
      ans = mid2;
      l = mid1 + 1;
    } else {
      ans = mid1;
      r = mid2 - 1;
    }
  }

  printf("%d\n", check(ans));
  return 0;
}
