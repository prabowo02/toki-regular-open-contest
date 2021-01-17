#include <bits/stdc++.h>
using namespace std;

const int N = 305;
const int MOD = 998244353;

int n;
int a[N];
int pos[N];

int C[N][N];

bool lft[N], rgt[N];

int dp[N][N];
int f(int l, int r) {
  if (l == r) return 1;
  if (~dp[l][r]) return dp[l][r];

  int ret = ((!rgt[l] ? f(l + 1, r) : 0) + (!lft[r] ? f(l, r - 1) : 0)) % MOD;
  for (int i = l + 1; i < r; ++i) {
    if (lft[i] || rgt[i]) continue;
    ret = (1LL * f(l, i - 1) * f(i + 1, r) % MOD * C[r - l][i - l] + ret) % MOD;
  }
  return dp[l][r] = ret;
}

bool hasSolution() {
  vector<bool> swapped(n + 1, false);
  vector<int> p(n);
  iota(p.begin(), p.end(), 0);
  for (int it = 0; it < n; ++it) {
    for (int i = 1; i < n; ++i) {
      if (swapped[i]) continue;
      if (lft[i] == swapped[i - 1] && rgt[i] == swapped[i + 1]) {
        swap(p[i - 1], p[i]);
        swapped[i] = true;
      }
    }
  }

  for (int i = 0; i < n; ++i) if (a[i] != p[i]) return false;
  return true;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    pos[--a[i]] = i;
  }

  for (int i = 1; i < n; ++i) {
    if (pos[i - 1] < i - 1) lft[i] = true;
    if (pos[i] > i) rgt[i] = true;
  }
  if (!hasSolution()) return 0 * printf("0\n");

  for (int i = 0; i < n; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
  }

  memset(dp, -1, sizeof dp);
  printf("%d\n", f(1, n - 1));
  return 0;
}
