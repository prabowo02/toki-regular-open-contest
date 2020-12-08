#include <bits/stdc++.h>
using namespace std;

const int N = 300003;
const int MOD = 1000000007;

int n, k;
int a[N];

int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

  int ans = 0;
  for (int mask = 1; mask < 1<<n; ++mask) {
    int g = 0, cnt = 0;
    for (int i = 0; i < n; ++i) {
      if (mask >> i & 1) {
        g = gcd(g, a[i]);
        ++cnt;
      }
    }

    if (g * cnt == k) ++ans;
  }

  printf("%d\n", ans);
  return 0;
}
