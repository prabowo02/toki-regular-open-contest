#include <bits/stdc++.h>
using namespace std;

int main() {
  int a[3];
  scanf("%d %d %d", &a[0], &a[1], &a[2]);

  sort(a, a + 3);

  if (a[0] == a[1] && a[2] == a[1] + 1 && a[0] > 1) printf("Ya\n");
  else printf("Tidak\n");
  return 0;
}
