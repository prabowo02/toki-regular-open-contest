#include <bits/stdc++.h>
using namespace std;

bool work(int n, int k) {
  n *= 2; k *= 2;
  int distance = __gcd(n / 2 + k, n);
  
  return k >= distance;
}

int main() {
  int t; cin >> t;

  for (int tc = 1 ; tc <= t ; tc++) {
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%s\n", work(n, k) ? "YES" : "NO");
  }
  return 0;
}