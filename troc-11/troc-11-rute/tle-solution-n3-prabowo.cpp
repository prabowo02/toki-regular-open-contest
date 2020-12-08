#include <bits/stdc++.h>
using namespace std;

#define ends LOLOLOL

const int N = 2005;
const int MOD = 1000000007;

int n;
int par[N];
vector<int> edges[N];
int s, t;

int ends[N];

int combinations[N][N];
int C(int n, int k) {
  if (k < 0 || k > n) return 0;
  if (k == 0 || k == n) return 1;
  if (combinations[n][k]) return combinations[n][k];
  return combinations[n][k] = (C(n-1, k) + C(n-1, k-1)) % MOD;
}

int dp[N][N];
int tmp[N];
void dfs(int u) {
  dp[u][0] = 1;
  for (int v: edges[u]) {
    if (v == par[u]) continue;

    dfs(v);
    for (int i = 0; i <= n; ++i) tmp[i] = 0;

    for (int i = 0; i <= n; ++i) {
      for (int j = 1; i+j <= n; ++j) {
        tmp[i+j] = (1LL * dp[u][i] * dp[v][j] % MOD * C(i+j - ends[u] - ends[v], i - ends[u]) + tmp[i+j]) % MOD;
      }
    }

    ends[u] += ends[v];
    for (int i = 0; i <= n; ++i) {
      dp[u][i] = tmp[i];
    }
  }

  for (int i = 0; i <= n; ++i) tmp[i] = 0;

  if (u == s || u == t) {
    ++ends[u];
    for (int i = 0; i <= n; ++i) {
      tmp[i+1] = (dp[u][i] + tmp[i+1]) % MOD; // New component
      tmp[i] = (dp[u][i] + tmp[i]) % MOD; // Existing
    }
  } else {
    for (int i = 0; i <= n; ++i) {
      // New component
      tmp[i+1] = (1LL * dp[u][i] * (i+1 - ends[u]) + tmp[i+1]) % MOD;

      // Merge
      tmp[i] = (1LL * dp[u][i+1] * i + tmp[i]) % MOD;

      // Existing
      tmp[i] = (1LL * dp[u][i] * (i*2 - ends[u]) + tmp[i]) % MOD;
    }
  }

  for (int i = 0; i <= n; ++i) dp[u][i] = tmp[i];
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    scanf("%d", &par[i]);
    edges[--par[i]].push_back(i);
  }
  scanf("%d %d", &s, &t); --s; --t;

  dfs(0);
  printf("%d\n", dp[0][1]);
  return 0;
}
