#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  for (int i = 0; i + 1 < N; i++) {
    int u, v;
    cin >> u >> v;
  }

  if (accumulate(begin(A), end(A), 0) == 0 || (N == 2 && A[0] + A[1] == 2)) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
  }
  return 0;
}
