#include <cstdio>

int N, M;
int sum, A;

int main() {
  scanf("%d %d", &N, &M);
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      scanf("%d", &A);
      sum += A;
    }
  }
  if (sum) puts("YES");
  else puts("NO");
}