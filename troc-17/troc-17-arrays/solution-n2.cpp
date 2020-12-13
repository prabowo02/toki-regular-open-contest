#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <cstdio>

const int MAXN = 100005;
const int MOD = 998244353;

int n;
int a[MAXN];

int main() {
  scanf("%d", &n);

  int ans = 1;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);

    int cur = 0;
    for (int j = i; j >= 0; --j) {
      cur |= a[j];
      ans = 1LL * ans * cur % MOD;
    }
  }

  printf("%d\n", ans);
  return 0;
}
