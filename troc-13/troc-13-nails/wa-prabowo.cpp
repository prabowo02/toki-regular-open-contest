#include <bits/stdc++.h>
using namespace std;

const int N = 10005;

int n;
int d[N*2];

int dp[N*2];

vector<int> factorize(int n) {
  vector<int> ret;
  for (int i = 1; i*i <= n; ++i) {
    ret.push_back(i);
    if (i*i != n) ret.push_back(n/i);
  }
  return ret;
}

int check(int len) {
  int j = 0, sum = 0;
  int ret = -1;
  dp[-1] = 0;
  for (int i = 0; i < n*2; ++i) {
    sum += d[i];
    if (sum < len) dp[i] = 0;

    while (sum > len) sum -= d[j++];
    if (j >= n) break;

    if (sum == len) dp[i] = (dp[j-1] == -1 ? -1 : dp[j-1] + i-j);
    else dp[i] = -1;

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

  int peri = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &d[i]);
    d[i+n] = d[i];
    peri += d[i];
  }

  int ans = -1;
  for (int len: factorize(peri)) {
    if (peri / len < 3) continue;
    int nails = check(len);
    if (nails != -1) {
      if (ans == -1 || ans > nails) {
        ans = nails;
      }
    }
  }

  printf("%d\n", ans);
  return 0;
}
