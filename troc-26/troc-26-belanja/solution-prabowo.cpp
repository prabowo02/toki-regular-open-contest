#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXM = 16;

int N, M;
int A[MAXN][MAXM];
int B[MAXM];

long long dp[MAXM][1 << MAXM];

int main() {
  scanf("%d %d", &N, &M);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      scanf("%d", &A[i][j]);
    }
  }
  for (int j = 0; j < M; ++j) scanf("%d", &B[j]);

  for (int i = 0; i < N; ++i) {
    vector<pair<int, int>> prices(M);
    for (int j = 0; j < M; ++j) {
      prices[j] = {A[i][j], j};
    }
    sort(prices.begin(), prices.end());

    int mask = (1 << M) - 1;
    for (int j = 0; j < M; ++j) {
      int bit = prices[j].second;
      mask ^= 1 << bit;
      dp[bit][mask] += prices[j].first;
    }
  }

  // DP sum over supersets
  for (int i = 0; i < M; ++i) {
    for (int len = 1; len < 1 << M; len <<= 1) {
      for (int j = 0; j < 1 << M; j += len << 1) {
        for (int k = j; k < j + len; ++k) {
          dp[i][k] += dp[i][k | len];
        }
      }
    }
  }

  long long sum = -1;
  int ansmask = 0;
  for (int mask = 1; mask < 1 << M; ++mask) {
    long long cur = 0;
    for (int nmask = mask; nmask > 0; ) {
      int bit = __builtin_ctz(nmask & -nmask);
      cur += dp[bit][mask ^ (1 << bit)] + B[bit];
      nmask ^= 1 << bit;
    }

    if (sum == -1 || cur < sum) {
      sum = cur;
      ansmask = mask;
    }
  }
  printf("%lld\n", sum);

  // For backtracking purpose
  // vector<int> ans;
  // for (int i = 0; i < N; ++i) {
  //   int buy = -1;
  //   for (int mask = ansmask; mask > 0; ) {
  //     int bit = __builtin_ctz(mask & -mask);
  //     if (buy == -1 || A[i][bit] < A[i][buy]) {
  //       buy = bit;
  //     }
  //     mask ^= 1 << bit;
  //   }
  //   ans.push_back(buy);
  // }
  // for (int c : ans) printf("%d ", c + 1);
  // printf("\n");
  return 0;
}
