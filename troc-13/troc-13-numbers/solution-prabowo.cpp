#include <cstdio>
#include <algorithm>

const int N = 100005;

int n;
int a[N];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  std::sort(a, a + n);
  int _n = std::unique(a, a + n) - a;
  printf("%d\n", (_n == 1 || _n == n ? _n : n-1));
  return 0;
}
