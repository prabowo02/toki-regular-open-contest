#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  A.resize(unique(begin(A), end(A)) - begin(A));

  cout << (A.size() > 3 && N > 4 ? "NO" : "YES") << '\n';
  return 0;
}
