#include <bits/stdc++.h>
using namespace std;

int N, tmp, cnt;
bool A[200005];

int main() {
  scanf("%d", &N);
  for(int i = 1; i <= N; i++) {
    scanf("%d", &tmp);
    cnt += (A[tmp] == 0);
    A[tmp] = 1;
  }
  if(cnt == 1) {
    puts("1");
  }else if(cnt == N) {
    printf("%d\n", N); 
  }else {
    printf("%d\n", N - 1);
  }
}