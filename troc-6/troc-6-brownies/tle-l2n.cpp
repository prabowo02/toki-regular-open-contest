#include <bits/stdc++.h>
using namespace std;

const int L = 30005;
const int N = 105;
const int MOD = 1e9 + 7;

int n, l;
int c[N];
int sumC[N];
int dp[N][L];

void read() {
  scanf("%d %d", &n, &l);
  for (int i = 1 ; i <= n ; i++) {
    scanf("%d", &c[i]);
    sumC[i] = sumC[i-1] + c[i];
  }
}

int solve(int posN, int posA) {
  int posB = 2 * sumC[posN-1] - posA;
  if (posB >= l || posA >= l) return 0;
  if (posN == n) {
    assert(2 * c[n] == l - posA + l - posB);
    return 1;
  }

  int &ret = dp[posN][posA];
  if (ret != -1) return ret;

  ret = 0;
  // for (int i = 1 ; i < 2 * c[posN] && posA + i < l ; i++) {
  //   ret = (ret + solve(posN+1, posA+i)) % MOD;
  // }
  for (int i = min(l - posA, 2 * c[posN]) - 1 ; i >= 1 ; i--) {
    int sisaB = l - posB - (2 * c[posN] - i);
    if (sisaB < n - posN) break;
    ret = (ret + solve(posN+1, posA+i)) % MOD;
  }

  return ret;
}

int work() {
  memset(dp, -1, sizeof dp);
  return solve(1, 0);
}

int main() {
  read();
  printf("%d\n", work());
  return 0;
}
