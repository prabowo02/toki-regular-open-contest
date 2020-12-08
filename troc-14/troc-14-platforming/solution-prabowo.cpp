#include <cstdio>

const int N = 200005;

int n, k;
int h[N];
long long pre[N];

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &h[i]);
    pre[i] = pre[i-1] + h[i];
  }

  long long ans = 1e18;
  for (int i = 1; i <= n; ++i) {
    long long sum = pre[n] - pre[i] - 1LL * h[i] * (n - i);

    int round = (k < i ? k : i);
    sum += 1LL * round * h[i] - pre[round];

    ans = (sum < ans ? sum : ans);
  }

  printf("%lld\n", ans);
  return 0;
}
