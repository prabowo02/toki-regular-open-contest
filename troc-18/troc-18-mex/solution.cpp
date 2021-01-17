#include <cstdio>
#include <algorithm>
using namespace std;

int N;
int A[1005];

int main() {
  scanf("%d", &N);
  for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
  sort(A + 1, A + N + 1);
  if(N > 1) swap(A[2], A[N]);
  printf("%d", A[1]);
  for (int i = 2; i <= N; i++) printf(" %d", A[i]);
  putchar('\n');
}