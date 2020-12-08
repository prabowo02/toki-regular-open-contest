#include <cstdio>

const int kMaxA = 1005;

int points[kMaxA * kMaxA * 2];

int main() {
  int N;
  scanf("%d", &N);
  for (int i = 0; i <= N; ++i) {
    for (int j = 1; j <= N; ++j) {
      ++points[i*i + j*j];
    }
  }

  for (int i = N; i > 0; --i) {
    if (points[i*i] == 3) return 0 * printf("%d\n", i);
  }

  printf("-1\n");
  return 0;
}
