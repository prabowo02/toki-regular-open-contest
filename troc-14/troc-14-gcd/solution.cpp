#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  scanf("%d", &n);

  printf("%d\n", n/2*2 + 1);
  for (int i = 0; i < n/2; ++i) {
    printf("GL");
  }
  printf("G\n");
  return 0;
}
