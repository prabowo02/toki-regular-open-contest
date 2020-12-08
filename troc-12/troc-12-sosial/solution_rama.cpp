// Author   : rama_pang
// Problem  : troc-12-sosial
// Time     : O(N)
// Memory   : O(1)

#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  long long sum = 0;
  for (int i = 0; i <= N; i++) {
    int A;
    cin >> A;
    sum += (1ll << i) * A;
  }
  
  cout << (sum % (1 << N) == 0 ? sum / (1 << N) : -1) << "\n";
  return 0;
}
