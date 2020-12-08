#include <cstdio>
using namespace std;

int N, ans, A, B;
int cnt[15];

int main() {
  scanf("%d", &N);
  for(int i = 1; i <= N; i++) {
    scanf("%d %d", &A, &B);
    cnt[A]++, cnt[B]++;
  }
  for(int i = 10; i > 0; i--) {
    if(cnt[i] > N) {
      ans += N * i, N = 0;
    }else {
      ans += cnt[i] * i, N -= cnt[i];
    }
  }
  printf("%d\n", ans);
}