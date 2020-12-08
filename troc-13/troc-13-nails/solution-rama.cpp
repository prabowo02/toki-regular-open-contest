#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);

  int N;
  cin >> N;

  vector<int> A(N);
  long long S = 0;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    S += A[i];
  }

  for (int i = 0; i < N; i++) {
    A.emplace_back(A[i]);
  }

  auto Solve = [&](int side) {
    long long len = S / side;
    vector<int> match(2 * N, -1);
    long long s = 0;
    for (int i = 0, j = 0; i < 2 * N; i++) {
      while (j < 2 * N && s < len) {
        s += A[j++];
      }
      if (s == len) {
        match[i] = j;
      }
      s -= A[i];
    }

    vector<int> dp(2 * N + 1, 0);
    for (int i = 2 * N - 1; i >= 0; i--) {
      if (match[i] == -1) continue;
      dp[i] = 1;
      if (match[i] < 2 * N) {
        dp[i] += dp[match[i]];
      }
    }
    if (*max_element(begin(dp), end(dp)) >= side) {
      return side;
    } else {
      return 0;
    }
  };

  int ans = 0;
  for (int f = 3; f <= N; f++) {
    if (S % f == 0) {
      ans = max(ans, Solve(f));
    }
  }  

  if (ans <= 2) {
    cout << -1 << "\n";
  } else {
    cout << N - min(ans, N) << "\n";
  }
  return 0;
}
