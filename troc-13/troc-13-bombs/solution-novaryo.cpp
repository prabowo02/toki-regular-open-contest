#include <cstdio>
#define MIN(a, b) (a < b ? a : b)
using namespace std;

int N, M, R;

int main() {
  scanf("%d %d %d", &N, &M, &R);
  printf("%d\n", (MIN(N, M) + (R << 1)) / (R << 1 | 1));
}