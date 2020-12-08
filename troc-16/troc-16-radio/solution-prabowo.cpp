#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int M = 20;

int n, m, r;
int x[N], y[N];
int a[M], b[M], c[M];

int cnt[1 << M];
int ans[N];

int main() {
  scanf("%d %d %d", &n, &m, &r);
  for (int i = 0; i < n; ++i) {
    scanf("%d %d", &x[i], &y[i]);
  }
  for (int j = 0; j < m; ++j) {
    scanf("%d %d %d", &a[j], &b[j], &c[j]);
  }

  for (int i = 0; i < n; ++i) {
    int mask = 0;
    for (int j = 0; j < m; ++j) {
      if (1LL * (x[i]-a[j]) * (x[i]-a[j]) + 1LL * (y[i]-b[j]) * (y[i]-b[j]) <= 1LL * r * r) {
        mask |= 1 << j;
      }
    }
    ++cnt[mask];
  }

  for (int i = 0; i < m; ++i) for (int mask = 0; mask < 1 << m; ++mask) {
    if (mask >> i & 1) cnt[mask] += cnt[mask ^ (1 << i)];
  }

  for (int i = 1; i <= n; ++i) ans[i] = -1;
  for (int mask = 0; mask < 1 << m; ++mask) {
    int cover = n - cnt[~mask & ((1 << m) - 1)];
    int cost = 0;
    for (int j = 0; j < m; ++j) if (mask >> j & 1) cost += c[j];

    if (ans[cover] == -1 || cost < ans[cover]) {
      ans[cover] = cost;
    }
  }

  for (int i = n - 1; i > 0; --i) {
    if (ans[i] == -1 || ans[i + 1] != -1 && ans[i + 1] < ans[i]) ans[i] = ans[i + 1];
  }

  for (int i = 1; i <= n; ++i) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
