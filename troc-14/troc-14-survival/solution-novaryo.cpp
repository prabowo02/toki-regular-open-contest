#include <cstdio>
using namespace std;

int N, D;
int T[200005], R[200005], C[200005];

int main() {
  scanf("%d %d", &N, &D);
  D++;
  for(int i = 1; i <= N; i++) {
    scanf("%d %d %d", &T[i], &R[i], &C[i]);
  }
  for(int i = N; i > 0; i--) {
    if(D - T[i] > R[i] + C[i]) continue;
    if(D - T[i] <= C[i]) D = T[i];
    else D = T[i] + (D - T[i] - C[i]);
  }
  printf("%d\n", D - 1);
}