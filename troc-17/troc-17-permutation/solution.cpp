#include <cstdio>

const int MAXN = 2005;
const int MOD = 998244353;

int n, k;

bool fixed[MAXN];

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 0; i < k; ++i) {
    int a;
    scanf("%*d %d", &a);
    fixed[a] = true;
  }

  int ans = 1;
  for (int i = n; i > 0; --i) {
    if (!fixed[i]) ans = 1LL * ans * i % MOD;
  }

  printf("%d\n", ans);
  return 0;
}
