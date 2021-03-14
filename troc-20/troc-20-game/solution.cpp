#include <cstdio>

int main() {
  int N, last = -1, A, cnt = 0;
  scanf("%d", &N);
  for (int i = 1; i <= N; i++) {
    scanf("%d", &A);
    if (last != A) cnt++, last = A;
  }
  if (N >= 5 && cnt > 3) puts("NO");
  else puts("YES");
}