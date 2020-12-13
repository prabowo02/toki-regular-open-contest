#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <cstdio>

const int N = 200005;

int n;
int a[N];

int cnt[3][N];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  int ans = 0;
  for (int i = 0; i < n - 2; ++i) {
    ++cnt[0][a[i]];

    for (int j = i + 1; j < n; ++j) ++cnt[2][a[j]];

    int cur = 0;
    for (int j = i + 1; j < n - 1; ++j) {
      int bef = (cnt[0][a[j]] > 0 && cnt[1][a[j]] > 0 && cnt[2][a[j]] > 0);
      ++cnt[1][a[j]]; --cnt[2][a[j]];
      int aft = (cnt[0][a[j]] > 0 && cnt[1][a[j]] > 0 && cnt[2][a[j]] > 0);

      cur += aft - bef;
      if (cur > ans) ans = cur;
    }
    --cnt[2][a[n-1]];

    for (int j = i + 1; j < n - 1; ++j) --cnt[1][a[j]];
  }

  printf("%d\n", ans);
  return 0;
}
