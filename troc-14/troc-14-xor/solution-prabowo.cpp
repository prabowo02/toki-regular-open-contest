#include <cstdio>

const int N = 100005;

int n;
long long a[N];

int main() {
  scanf("%d", &n);
  long long sum = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &a[i]);
    sum ^= a[i];
  }

  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    long long t = 0;
    for (int j = 60; j >= 0; --j) {
      if ((a[i] >> j & 1) && ((sum ^ a[i]) >> j & 1)) {
        t |= (1LL << j+1) - 1;
        break;
      } else if ((a[i] >> j & 1) || ((sum ^ a[i]) >> j & 1)) {
        t |= 1LL << j;
      }
    }
    ans = (t > ans ? t : ans);
  }

  printf("%lld\n", ans);
  return 0;
}
