#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N, M;
  cin >> N >> M;

  vector<int> A(N * M);
  for (int i = 0; i < N * M; i++) {
    cin >> A[i];
  }

  cout << (accumulate(begin(A), end(A), 0) == 0 ? "NO" : "YES") << '\n';
  return 0;
}
