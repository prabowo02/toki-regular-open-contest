#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N, M, R;
  cin >> N >> M >> R;

  vector<int> X(N), Y(N);
  for (int i = 0; i < N; i++) {
    cin >> X[i] >> Y[i];
  }

  vector<int> A(M), B(M), C(M);
  for (int i = 0; i < M; i++) {
    cin >> A[i] >> B[i] >> C[i];
  }

  vector<int> dp(1 << M, 0);
  vector<int> occ(1 << M, 0);
  for (int i = 0; i < N; i++) {
    int mask = 0;
    for (int j = 0; j < M; j++) {
      int dx = X[i] - A[j];
      int dy = Y[i] - B[j];
      if (1ll * dx * dx + 1ll * dy * dy <= 1ll * R * R) {
        mask |= 1 << j;
      }
    }
    occ[mask] += 1;
  }

  for (int mask = 0; mask < (1 << M); mask++) if (occ[mask] > 0) {
    // No counter testcases found, conjecture: impossible to trigger worst case
    for (int m = mask; m > 0; m = (m - 1) & mask) {
      dp[m] += (__builtin_popcount(m) & 1) ? occ[mask] : -occ[mask];
    }
  }

  dp[0] = 0;
  for (int i = 0; i < M; i++) {
    for (int mask = 0; mask < (1 << M); mask++) {
      if (((mask >> i) & 1) == 1) {
        dp[mask] += dp[mask ^ (1 << i)];
      }
    }
  }

  vector<int> ans(N + 1, -1);
  for (int mask = 0; mask < (1 << M); mask++) {
    int cost = 0;
    for (int i = 0; i < M; i++) {
      if ((mask >> i) & 1) {
        cost += C[i];
      }
    }
    if (ans[dp[mask]] == -1 || ans[dp[mask]] > cost) {
      ans[dp[mask]] = cost;
    }
  }

  for (int i = N - 1; i >= 1; i--) {
    if (ans[i + 1] != -1 && (ans[i] == -1 || ans[i] > ans[i + 1])) {
      ans[i] = ans[i + 1];
    }
  }

  for (int i = 1; i <= N; i++) {
    cout << ans[i] << '\n';
  }
  return 0; 
}
