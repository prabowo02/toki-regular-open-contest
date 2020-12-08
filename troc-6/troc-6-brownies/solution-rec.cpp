#include <bits/stdc++.h>
using namespace std;

const int L = 30005;
const int N = 105;
const int MOD = 1e9 + 7;

int n, l;
int c[N];
int sumC[N];
int dp[N][L][2];

void read() {
  scanf("%d %d", &n, &l);
  for (int i = 1 ; i <= n ; i++) {
    scanf("%d", &c[i]);
    sumC[i] = sumC[i-1] + c[i];
  }
}

int solve(int posN, int posA, bool start) {
  if (posA >= l) return 0;

  int &ret = dp[posN][posA][start];
  if (ret != -1) return ret;

  if (start) {
    int posB = 2 * sumC[posN-1] - posA;
    if (posB < 0 || posB >= l) return 0;
    if (posN == n) return 1;

    ret = solve(posN, posA+1, 0) - solve(posN, posA + 2 * c[posN], 0);
    ret = (ret + MOD) % MOD;
  } else {
    ret = solve(posN+1, posA, 1) + solve(posN, posA+1, 0);
    ret = ret % MOD;
  }

  return ret;
}

int work() {
  memset(dp, -1, sizeof dp);
  return solve(1, 0, 1);
}

int main() {
  read();
  printf("%d\n", work());
  return 0;
}
