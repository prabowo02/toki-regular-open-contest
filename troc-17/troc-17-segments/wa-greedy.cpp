#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <cstdio>

const int N = 200005;

int n;
int a[N];

int cnt[3][N];

int cum;
void add(int x, int i) {
  ++cnt[x][i];
  if (cnt[x][i] == 1 && cnt[0][i] > 0 && cnt[1][i] > 0 && cnt[2][i] > 0) ++cum;
}

void rem(int x, int i) {
  if (cnt[x][i] == 1 && cnt[0][i] > 0 && cnt[1][i] > 0 && cnt[2][i] > 0) --cum;
  --cnt[x][i];
}

int main() {
  scanf("%d", &n);
  // for (int i = n - 1; i >= 0; --i) {
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  for (int i = 0; i < n; ++i) add(1, a[i]);

  int ans = 0, j = n - 1;
  for (int i = 0; i < n - 2; ++i) {
    add(0, a[i]); rem(1, a[i]);
    while (j > i && cnt[2][a[i]] == 0) {
      add(2, a[j]); rem(1, a[j]);
      --j;
    }

    if (j > i && cum > ans) ans = cum;
  }

  printf("%d\n", ans);
  return 0;
}
