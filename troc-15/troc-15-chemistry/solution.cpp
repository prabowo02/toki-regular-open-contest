#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n, m, t;
vector<pair<int, int>> reactions[MAXN];
int k;
int s[MAXN];
bool base[MAXN];

int dp[MAXN];
int f(int x) {
  if (base[x]) return 1;
  if (~dp[x]) return dp[x];

  int ret = MAXN;
  for (int i = 0; i < reactions[x].size(); ++i) {
    int a, b;
    tie(a, b) = reactions[x][i];
    ret = min(ret, min(max(f(a), f(b) + 1), max(f(a) + 1, f(b))));
  }

  return dp[x] = ret;
}

int main() {
  scanf("%d %d %d", &n, &m, &t);
  --t;
  for (int i = 0; i < m; ++i) {
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);

    reactions[--z].emplace_back(--x, --y);
  }

  scanf("%d", &k);
  for (int i = 0; i < k; ++i) {
    scanf("%d", &s[i]);
    base[--s[i]] = true;
  }

  memset(dp, -1, sizeof dp);
  int ans = f(t);
  if (ans >= MAXN) ans = -1;
  printf("%d\n", ans);
  return 0;
}
