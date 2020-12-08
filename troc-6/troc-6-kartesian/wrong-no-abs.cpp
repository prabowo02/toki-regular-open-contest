#include <bits/stdc++.h>
using namespace std;

int main() {
  int x, y, n;
  cin >> n >> x >> y;

  int a = max(y, 0);
  int b = max(x, 0);
  int c = a - y;
  int d = b - x;

  if (x + y > n || n % 2 !=  (x + y) % 2) {
    puts("-1");
  } else {
    int sisa = n - a - b - c - d;
    a += sisa / 2;
    c += sisa / 2;

    printf("%d %d %d %d\n", a, b, c, d);
  }
  
  return 0;
}
