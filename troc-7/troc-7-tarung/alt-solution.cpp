#include <bits/stdc++.h>
using namespace std;

int f(int x, int y, int a, int b) {
  if (x >= y) return 1;

  int atk, def;
  
  if (x == b) atk = max(0, f(x*2 - y, y-x, a, b));
  else if (x < b) atk = -1;
  else atk = -f(y-x, x, b, a);

  if (y == a) def = max(0, f(x+a, y+b, a, b));
  else if (y > a) def = -1;
  else def = -f(y, x+y, b, a);

  return max(atk, def);
}

int main() {
  int t;
  scanf("%d %*d %*d", &t);
  while (t--) {
    int x, y, a, b;
    scanf("%d %d %d %d", &x, &y, &a, &b);

    int res = f(x, y, a, b);
    if (res == -1) printf("YOGA\n");
    else if (res == 0) printf("SALMAN\n");
    else printf("AMNU\n");
  }

  return 0;
}