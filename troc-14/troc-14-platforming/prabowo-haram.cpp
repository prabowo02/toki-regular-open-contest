#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

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
  vector<int> idxs;
  for (int i = 1; i <= min(100, n); ++i) idxs.push_back(i);
  for (int i = n; i > max(0, n-100); --i) idxs.push_back(i);
  for (int i = max(1, n/2-100); i <= min(n, n/2 + 100); ++i) idxs.push_back(i);
  for (int i: idxs) {
    long long sum = pre[n] - pre[i] - 1LL * h[i] * (n - i);

    int round = (k < i ? k : i);
    sum += 1LL * round * h[i] - pre[round];

    ans = (sum < ans ? sum : ans);
  }

  printf("%lld\n", ans);
  return 0;
}
