/**
 * Author   : rama_pang
 * Problem  : troc-11-wifi
 * Time     : O(N log N)
 * Memory   : O(N)
**/

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);

  int N, M;
  cin >> N >> M;

  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  sort(begin(A), end(A));

  int ans = INT_MAX;

  for (int i = 0; i + M - 1 < N; i++) {
    ans = min(ans, A[i + M - 1] - A[i]);
  }

  cout << ans << "\n";
  return 0;
}
