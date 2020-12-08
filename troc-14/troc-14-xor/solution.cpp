#include <cstdio>
#define LOG2(n) ((n) == 0 ? 0 : 63 - __builtin_clzll(n))
using namespace std;

int N;
long long A[100005];
long long sum, ans;

int main() {
  scanf("%d", &N);
  for(int i = 1; i <= N; i++) {
    scanf("%lld\n", &A[i]);
    sum ^= A[i];
  }
  long long tmp;
  for(int i = 1; i <= N; i++) {
    tmp = A[i] | (sum ^ A[i]) | ((1LL << (LOG2(A[i] & (sum ^ A[i])))) - 1);
    if(ans < tmp) ans = tmp;
  }
  printf("%lld\n", ans);
}
