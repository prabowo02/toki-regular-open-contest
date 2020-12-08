#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, q;
int par[N];

long long a[N];

vector<int> edges[N];

int depth[N];
int cnt[N];

long long sub[N];
long long lazy_sub[N];

void dfs(int u) {
  cnt[u] = 1; sub[u] = a[u];
  for (int v: edges[u]) {
    depth[v] = depth[u] + 1;
    dfs(v);
    sub[u] += sub[v];
    cnt[u] += cnt[v];
  }
}

void update_subtree(int u, int x) {
  lazy_sub[u] += x;
  for (int v = par[u]; v != -1; v = par[v]) {
    sub[v] += 1LL * cnt[u] * x;
  }
}

void update_path(int u, int v, int x) {
  if (depth[u] < depth[v]) swap(u, v);
  int depth_u = depth[u], depth_v = depth[v];
  
  while (depth[u] != depth[v]) {
    a[u] += x;
    sub[u] += x * (depth_u - depth[u] + 1);
    u = par[u];
  }

  while (u != v) {
    a[u] += x; a[v] += x;
    sub[u] += x * (depth_u - depth[u] + 1);
    sub[v] += x * (depth_v - depth[v] + 1);
    u = par[u]; v = par[v];
  }

  a[u] += x; int len = depth_u + depth_v - depth[u]*2 + 1;
  while (u != -1) {
    sub[u] += x * len;
    u = par[u];
  }
}

long long query_subtree(int u) {
  long long ret = sub[u];

  for (int v = u; v != -1; v = par[v]) {
    ret += lazy_sub[v] * cnt[u];
  }

  return ret;
}

long long query_path(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  int depth_u = depth[u], depth_v = depth[v];

  long long ret = 0;
  while (depth[u] != depth[v]) {
    ret += a[u];
    ret += lazy_sub[u] * (depth_u - depth[u] + 1);
    u = par[u];
  }

  while (u != v) {
    ret += a[u] + a[v];
    ret += lazy_sub[u] * (depth_u - depth[u] + 1) + lazy_sub[v] * (depth_v - depth[v] + 1);
    u = par[u]; v = par[v];
  }

  ret += a[u];
  int len = depth_u + depth_v - depth[u]*2 + 1;
  while (u != -1) {
    ret += lazy_sub[u] * len;
    u = par[u];
  }

  return ret;
}

int main() {
  scanf("%d %d", &n, &q);
  par[0] = -1;
  for (int i = 1; i < n; ++i) {
    scanf("%d", par + i);
    edges[--par[i]].push_back(i);
  }

  for (int i = 0; i < n; ++i) {
    scanf("%lld", a + i);
  }

  dfs(0);

  while (q--) {
    int t;
    scanf("%d", &t);

    if (t == 1) {
      int u, v, x;
      scanf("%d %d %d", &u, &v, &x);
      --u, --v;

      update_path(u, v, x);
    } else if (t == 2) {
      int u, x;
      scanf("%d %d", &u, &x);

      update_subtree(--u, x);
    } else if (t == 3) {
      int u, v;
      scanf("%d %d", &u, &v);
      printf("%lld\n", query_path(--u, --v));
    } else if (t == 4) {
      int u;
      scanf("%d", &u);
      printf("%lld\n", query_subtree(--u));
    }
  }

  return 0;
}
