#include <bits/stdc++.h>
using namespace std;

const int N = 10005;

int n;
int d[N*2];

int dp[N*2];

int check(long long len) {
  int j = 0;
  long long sum = 0, pre = 0;
  int ret = -1;
  dp[-1] = 0;
  for (int i = 0; i < n*2; ++i) {
    sum += d[i]; pre += d[i];
    if (pre < len) dp[i] = 0;
    else dp[i] = -1;

    while (sum > len) sum -= d[j++];
    if (j >= n) break;

    if (sum == len) dp[i] = (dp[j-1] == -1 ? -1 : dp[j-1] + i-j);

    if (i >= n-1 && dp[i] != -1) {
      if (ret == -1 || dp[i] < ret) {
        ret = dp[i];
      }
    }
  }

  return ret;
}

int main() {
  scanf("%d", &n);

  long long peri = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &d[i]);
    d[i+n] = d[i];
    peri += d[i];
  }

  int ans = -1;
  for (int side = 3; side <= n; ++side) {
    int nails = check(peri / side);
    if (nails != -1) {
      if (ans == -1 || ans > nails) {
        ans = nails;
      }
    }
  }

  printf("%d\n", ans);
  return 0;
}
