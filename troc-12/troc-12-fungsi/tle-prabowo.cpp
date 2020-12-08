#include <cstdio>
using namespace std;

int a, b, ka, kb, la, lb;

void next(int &x) {
  if (x % a == ka) x -= la;
  else if (x % b == kb) x -= lb;
  else x -= 1;
}

int query(int x, int y) {
  while (x > 0 && y > 0) {
    if (x == y) return x;
    if (x > y) next(x);
    else next(y);
  }

  return -1;
}

int main() {
  scanf("%d %d %d %d %d %d", &a, &b, &ka, &kb, &la, &lb);
  int q;
  scanf("%d", &q);
  while (q--) {
    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d\n", query(x, y));
  }
  return 0;
}
