#include <cstdio>

int main() {
  int q;
  scanf("%d", &q);
  while (q--) {
    int x, y;
    scanf("%d %d", &x, &y);
    if (x - y & 3) printf("%d\n", x + y);
    else if (x == y) printf("%d\n", x + y + (x>0)*2);
    else {
      int ctz = 2 << __builtin_ctz(x - y >> 2);
      int m = y & ((ctz << 1) - 1);
      printf("%d\n", x + y + !(m == 0 || (m & ctz)) * 2);
    }
  }  
  return 0;
}
