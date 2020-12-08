#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N, M;
  cin >> N >> M;

  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  sort(begin(A), end(A));
  A.emplace_back(A[0] + M);
  for (int i = N; i > 0; i--) {
    A[i] -= A[i - 1];
  }
  
  cout << M - *max_element(begin(A) + 1, end(A)) << '\n';
  return 0;
}
