#include <bits/stdc++.h>
using namespace std;

int main() {
  int x, y, n;
  cin >> n >> x >> y;

  for (int a = 0 ; a <= n ; a++)
    for (int c = 0 ; c <= n ; c++)
      for (int b = 0 ; b <= n ; b++)
        for (int d = 0 ; d <= n ; d++) {
          if (a + b + c + d == n && a - c == y && b - d == x) {
            printf("%d %d %d %d\n", a, b, c, d);
            return 0;
          }
        }
  
  puts("-1");
  return 0;
}
