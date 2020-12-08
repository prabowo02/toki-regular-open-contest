#include <bits/stdc++.h>
using namespace std;

const int kMaxN = 50005;
const int kMagic = 222;

int n, q;
int a[kMaxN];
vector<int> edges[kMaxN];

// tuple(time, delta, child)
vector<tuple<int, int, int>> updates[kMaxN];
vector<int> asks[kMaxN];
int lazy[kMaxN];

int sz[kMaxN];
long long ans[kMaxN], pairs[kMaxN];

void dfsSz(int u, int p) {
  sz[u] = a[u];
  pairs[u] = 0;
  for (int v: edges[u]) {
    if (v == p) continue;
    dfsSz(v, u);
    pairs[u] += 1LL * sz[u] * sz[v];
    sz[u] += sz[v];
  }
}

void dfs(int u, int p) {
  int hasUpdate = u, cnt = (updates[u].size() > 0);
  lazy[u] = (a[u] == 0 ? 1 : -1);
  for (int v: edges[u]) {
    if (v == p) continue;
    dfs(v, u);

    if (updates[v].size() > 0) {
      ++cnt;
      hasUpdate = v;
    }
  }

  if (cnt > 1) {
    // Merge
    for (int v: edges[u]) {
      if (v == p) continue;
      for (int i = 0; i < updates[v].size(); ++i) {
        updates[u].push_back(updates[v][i]);
        get<1>(updates[u].back()) += (i & 1 ? -lazy[v] : lazy[v]);
        get<2>(updates[u].back()) = v;
      }
      updates[v].clear();
      lazy[v] = 0;
    }

    sort(updates[u].begin(), updates[u].end());
  } else if (hasUpdate != u) {
    swap(updates[hasUpdate], updates[u]);
    lazy[u] += lazy[hasUpdate];
  }

  if (asks[u].size() > 0) {
    if (cnt == 1 && hasUpdate != u) {
      for (int i = 0; i < updates[u].size(); ++i) {
        get<1>(updates[u][i]) += (i & 1 ? -lazy[hasUpdate] : lazy[hasUpdate]);
        get<2>(updates[u][i]) = hasUpdate;
      }
      lazy[u] -= lazy[hasUpdate];
    }
    int tsz = sz[u], color = a[u];

    for (int i = 0, j = 0; i < asks[u].size(); ++i) {
      while (j < updates[u].size() && get<0>(updates[u][j]) < asks[u][i]) {
        int delta = get<1>(updates[u][j]), child = get<2>(updates[u][j]);
        if (child != u) {
          pairs[u] += 1LL * delta * (sz[u] - sz[child]);
          sz[child] += delta;
          sz[u] += delta;
        }

        if (color == 0) pairs[u] += sz[u]++;
        else pairs[u] -= --sz[u];
        color ^= 1;

        ++j;
      }

      ans[asks[u][i]] = pairs[u];
    }

    sz[u] = tsz;
  }

  a[u] ^= (updates[u].size() & 1);
}

int main() {
  scanf("%d %d", &n, &q);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;

    edges[u].push_back(v);
    edges[v].push_back(u);
  }

  dfsSz(0, 0);

  for (int i = 0; i < q; ++i) {
    int t, x;
    scanf("%d %d", &t, &x);
    --x;
    ans[i] = -1;

    if (t == 1) {
      updates[x].emplace_back(i, 0, x);
    } else if (t == 2) {
      asks[x].push_back(i);
    }

    if (i % kMagic + 1 == kMagic) {
      dfs(0, 0);
      for (int i = 0; i < n; ++i) {
        asks[i].clear();
        updates[i].clear();
      }
      dfsSz(0, 0);
    }
  }
  dfs(0, 0);

  for (int i = 0; i < q; ++i) {
    if (ans[i] != -1) printf("%lld\n", ans[i]);
  }

  return 0;
}
