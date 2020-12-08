#include <cstdio>
using namespace std;

int N;

int main() {
  scanf("%d", &N);
  if(N == 1) {
    putchar('0');
    return 0;
  }
  printf("%d\n", (N / 2) * 2 + 1);
  for(int i = 2; i <= N; i += 2) {
    putchar('G'), putchar('L');
  }
  putchar('G');
}