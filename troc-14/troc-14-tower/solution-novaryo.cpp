#include <cstdio>
using namespace std;

int N, M;

int main() {
  scanf("%d %d", &N, &M);
  for(int i = 1; i <= N; i++) {
    for(int j = 1; j <= M; j++) {
      if(j & 1) putchar('W');
      else putchar('B');
    }
    putchar('\n');
  }
}