#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int n;
int a[N][N];

int col[N];
vector<int> members[N];
int par[N];
int root(int u) {
  if (u == par[u]) return u;
  return par[u] = root(par[u]);
}

int main() {
  scanf("%d", &n);
  vector<tuple<int, int, int>> edges;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int a;
      scanf("%d", &a);
      if (j < i) {
        edges.emplace_back(a, i, j);
      }
    }
  }

  sort(edges.begin(), edges.end());

  for (int i = 0; i < n; ++i) {
    par[i] = i;
    members[i] = {i};
  }

  for (const tuple<int, int, int> &edge: edges) {
    int w, u, v;
    tie(w, u, v) = edge;

    if (root(u) == root(v)) {
      if (col[u] == col[v]) return 0 * printf("%d\n", w);
    } else {
      if (col[u] == col[v]) {
        for (int member: members[par[v]]) col[member] ^= 1;
      }
      for (int member: members[par[v]]) members[par[u]].push_back(member);
      par[par[v]] = par[u];
    }
  }

  printf("0\n");
  return 0;
}