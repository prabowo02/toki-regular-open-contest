#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int n, m, k;

int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }
  return ret;
}

int main() {
  scanf("%d %d %d", &n, &m, &k);
  printf("%d\n", power(k + 1, n + m - 1));
  return 0;
}
