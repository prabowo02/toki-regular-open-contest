#include <bits/stdc++.h>
using namespace std;

const int L = 30005;
const int N = 105;
const int MOD = 1e9 + 7;

int n, l;
int c[N];
int sumC[N];
int dp[N][L];
int prefixDP[N][L];

void read() {
  scanf("%d %d", &n, &l);
  for (int i = 1 ; i <= n ; i++) {
    scanf("%d", &c[i]);
    sumC[i] = sumC[i-1] + c[i];
  }
}

int work() {
  // fill base case
  for (int posA = 0 ; posA < l ; posA++) {
    int posB = 2 * sumC[n-1] - posA;
    if (posB >= l) {
      dp[n][posA] = 0;
    }
    else {
      assert(2 * c[n] == l - posA + l - posB);
      dp[n][posA] = 1;
    }

    prefixDP[n][posA] = (posA ? prefixDP[n][posA-1] : 0) + dp[n][posA];
    prefixDP[n][posA] %= MOD;
  }

  // recurrence
  for (int posN = n-1 ; posN >= 1 ; posN--) {
    for (int posA = 0 ; posA < l ; posA++) {
      int posB = 2 * sumC[posN-1] - posA;
      if (posB >= l) {
        dp[posN][posA] = 0;
      }
      else {
        int lim = min(l-1, posA + 2 * c[posN] - 1);
        dp[posN][posA] = prefixDP[posN+1][lim] - prefixDP[posN+1][posA];
        dp[posN][posA] = (dp[posN][posA] + MOD) % MOD;
      }

      prefixDP[posN][posA] = (posA ? prefixDP[posN][posA - 1] : 0) + dp[posN][posA];
      prefixDP[posN][posA] %= MOD;
    }
  }

  return dp[1][0];
}

int main() {
  read();
  printf("%d\n", work());
  return 0;
}
