#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int SN = sqrt(N);
const int MOD = 998244353;

int n;
int a[N];
vector<int> adj[N];
int q;

int par[N];
void dfs(int u, int p=-1) {
  par[u] = p;
  for (int v : adj[u]) {
    if (v == p) continue;
    dfs(v, u);
  }
}

int sums[N];
vector<pair<int, int>> updates;

void update(int x) {
  int val = a[x];
  for (pair<int, int> p : updates) {
    int u = p.first;
    if (par[u] == x) {
      // child of x
      val = (val + p.second) % MOD;
    } else if (par[x] == u) {
      // parent of x
      val = (val + p.second) % MOD;
    }
  }
  updates.emplace_back(x, val);
}

int query(int x) {
  int ret = sums[x];
  for (pair<int, int> p : updates) {
    int u = p.first;
    if (par[u] >= 0 && par[par[u]] == x) {
      // grandchild of x
      ret = (ret + p.second) % MOD;
    } else if (u == x) {
      // x itself
      ret = (ret + 1LL * p.second * adj[x].size()) % MOD;
    } else if (par[u] == par[x]) {
      // sibling of x
      ret = (ret + p.second) % MOD;
    } else if (par[x] >= 0 && par[par[x]] == u) {
      // grandparent of x
      ret = (ret + p.second) % MOD;
    }
  }

  return ret;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(0);

  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    if (i % SN == 0) {
      vector<int> pending(n);
      for (pair<int, int> p : updates) {
        pending[p.first] = (pending[p.first] + p.second) % MOD;
      }
      for (int i = 0; i < n; ++i) {
        for (int j : adj[i]) {
          a[i] = (a[i] + pending[j]) % MOD;
        }
      }
      for (int i = 0; i < n; ++i) {
        sums[i] = 0;
        for (int j : adj[i]) sums[i] = (sums[i] + a[j]) % MOD;
      }
      updates.clear();
    }

    int t, x;
    scanf("%d %d", &t, &x);
    --x;

    if (t == 1) update(x);
    else if (t == 2) printf("%d\n", query(x));
  }

  return 0;
}
