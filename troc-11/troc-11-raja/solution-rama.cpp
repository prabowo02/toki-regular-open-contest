/**
 * Author   : rama_pang
 * Problem  : troc-11-raja
 * Time     : O(1)
 * Memory   : O(1)
**/

#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  cin >> N >> M;

  long long ans = 0;

  ans += 8ll * (N - 2); // corners on side N
  ans += 8ll * (M - 2); // corners on side M

  ans += 2ll * (N - 2) * (N - 3); // side N
  ans += 2ll * (M - 2) * (M - 3); // side M
  
  cout << ans << "\n";
  return 0;
}
