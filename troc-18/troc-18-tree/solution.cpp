#include <bits/stdc++.h>
using namespace std;

int N, Q;

vector<int> adj[200005];
int depth[200005];
int L[200005], R[200005], euler_pointer;

int BIT[5][200005];

void dfs(int u, int p) {
  depth[u] = depth[p] + 1;
  L[u] = ++euler_pointer;
  for (int v : adj[u]) {
    if (v != p) {
      dfs(v, u);
    }
  }
  R[u] = euler_pointer;
}

void update(int id, int idx, int value) {
  for(; idx <= 200000; idx += idx & -idx) {
    BIT[id][idx] ^= value;
  }
}

int getsum(int id, int idx) {
  int res = 0;
  for(; idx > 0; idx -= idx & -idx) {
    res ^= BIT[id][idx];
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin >> N;

  int u, v;
  for (int i = 1; i < N; i++) {
    cin >> u >> v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }

  dfs(1, 0);

  cin >> Q;
  int ty, z;
  while (Q--) {
    cin >> ty;
    if (ty == 1) {
      cin >> u >> z;
      update(depth[u] & 1, L[u], z);
      update(depth[u] & 1, R[u] + 1, z);
    }else {
      cin >> u;
      cout << getsum(depth[u] & 1, L[u]) << "\n";
    }
  }
}