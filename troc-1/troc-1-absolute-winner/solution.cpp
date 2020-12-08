#include <bits/stdc++.h>
using namespace std;

int main() {
  int a, b, c;
  cin >> a >> b >> c;

  int mx = max(a, max(b, c));
  int sum = a + b + c;

  printf("%s\n", sum / 7 * 4 == mx ? "YA" : "TIDAK");
  return 0;
}
