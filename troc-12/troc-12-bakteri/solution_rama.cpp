// Author   : rama_pang
// Problem  : troc-12-bakteri
// Time     : O(N M)
// Memory   : O(N M)

#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M, K;
  cin >> N >> M >> K;

  vector<string> A(N, string(M, '.'));

  for (int i = N - 1; i >= 0; i -= 2) {
    A[i][0] = 'X';
  }
  for (int i = M - 1; i >= 0; i -= 2) {
    A[0][i] = 'X';
  }

  for (int i = 0; i < N; i++) {
    K -= count(begin(A[i]), end(A[i]), 'X');
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (A[i][j] == '.' && K > 0) {
        A[i][j] = 'X';
        K--;
      }
    }
  }

  if (K < 0) {
    cout << "TIDAK\n";
    return 0;
  }

  cout << "YA\n";
  for (int i = 0; i < N; i++) {
    cout << A[i] << "\n";
  }
  return 0;
}
