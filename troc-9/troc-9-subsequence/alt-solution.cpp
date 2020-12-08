#pragma GCC diagnostic ignored "-Wshift-op-parentheses"

#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, k;
int a[N];

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; ++i) scanf("%d", a + i);

  sort(a, a + n);

  long long ans = 0;
  long long smallSum = 0, largeSum = 0;
  for (int i = 0; i < k; ++i) {
    long long take;
    if (i & 1) {
      take = a[n - (i>>1) - 1];
      largeSum += take;
    } else {
      take = a[i>>1];
      smallSum += take;
    }

    ans += 1LL*take*(i+2>>1) - smallSum + largeSum - 1LL*take*(i+1>>1);
  }

  printf("%lld\n", ans);
  return 0;
}
