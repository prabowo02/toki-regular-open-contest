#include <bits/stdc++.h>
using namespace std;

#define ends LOLOLOL

const int N = 20;
const int MOD = 1000000007;

int n;
int par[N];
int s, t;

vector<int> edges[N];

int dp[N][1 << N];
int dfs(int u, int mask) {
  if (mask + 1 == (1 << n)) return u == t;
  if (~dp[u][mask]) return dp[u][mask];

  int ret = 0;
  for (int v: edges[u]) {
    if (mask >> v & 1) continue;
    ret = (ret + dfs(v, mask | 1 << v)) % MOD;
  }

  return dp[u][mask] = ret;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    scanf("%d", &par[i]);
    --par[i];
  }
  scanf("%d %d", &s, &t); --s; --t;

  for (int u = 1; u < n; ++u) {
    int v = u;
    do {
      v = par[v];
      edges[u].push_back(v);
      edges[v].push_back(u);
    } while (v != 0);
  }

  memset(dp, -1, sizeof dp);
  printf("%d\n", dfs(s, 1 << s));
  return 0;
}
