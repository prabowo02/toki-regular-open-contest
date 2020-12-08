#include <bits/stdc++.h>
using namespace std;

int main() {
  int x, y, z;
  scanf("%d %d %d", &x, &y, &z);

  int discount = x / 100;
  while (y--) x -= discount;

  int tax = x / 100;
  while (z--) x += tax;

  printf("%d\n", x);
  return 0;
}
