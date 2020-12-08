#include <cstdio>
using namespace std;

int N, K;
long long H[200005], suf[200005];
long long sum, ans = 1e18;

int main() {
  scanf("%d %d", &N, &K);
  for(int i = 1; i <= N; i++) {
    scanf("%lld", &H[i]);
  }
  for(int i = N; i > 0; i--) {
    suf[i] = H[i] + suf[i + 1];
  }
  for(int i = 1; i <= N; i++) {
    sum += (H[i] - H[i - 1]) * (K > i - 1 ? i - 1 : K);
    if(sum + suf[i] - (N - i + 1) * H[i] < ans) ans = sum + suf[i] - (N - i + 1) * H[i];
  }
  printf("%lld\n", ans);
}