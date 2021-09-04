#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const long long INFLL = 2e18;

int n;
long long c;
int p[N], d[N];

long long dist[N];
vector<int> adj[N];
int sz[N], head[N], heavy[N];

long long dp[N];

struct Line {
  mutable long long k, m, p;
  bool operator<(const Line& o) const { return k < o.k; }
  bool operator<(long long x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  static const long long INF = LLONG_MAX;
  long long lazy_constant;
  long long div(long long a, long long b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(iterator x, iterator y) {
    if (y == end()) return x->p = INF, 0;
    if (x->k == y->k) x->p = x->m > y->m ? INF : -INF;
    else x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  void add_line(long long k, long long m) {
    m -= lazy_constant;
    k = -k; m = -m;
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  void add_constant(long long c) {
    lazy_constant += c;
  }
  long long query(long long x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return -l.k * x - l.m + lazy_constant;
  }
} tree[N];

void init() {
  for (int u = n - 1; u >= 0; --u) {
    sz[u] = 1;
    heavy[u] = -1;
    for (int v : adj[u]) {
      sz[u] += sz[v];
      if (heavy[u] == -1 || sz[v] > sz[heavy[u]]) {
        heavy[u] = v;
      }
    }
    head[u] = u;
  }

  for (int u = 0; u < n; ++u) {
    if (heavy[u] != -1) {
      head[heavy[u]] = head[u];
    }
  }
}

int main() {
  scanf("%d %lld", &n, &c);
  for (int i = 1; i < n; ++i) {
    scanf("%d %d", &p[i], &d[i]);
    adj[--p[i]].push_back(i);
    dist[i] = dist[p[i]] + d[i];
  }

  init();

  for (int u = n - 1; u >= 0; --u) {
    long long sum = 0;
    for (int v : adj[u]) {
      sum += dp[v] + c;
    }
    dp[u] = sum;

    for (int v : adj[u]) {
      dp[u] = min(dp[u], sum - dp[v] - c + tree[head[v]].query(dist[u]) + 1LL * dist[u] * dist[u]);
      tree[head[v]].add_constant(sum - dp[v] - c);
    }
    for (int v : adj[u]) {
      if (heavy[u] != v) for (Line line : tree[head[v]]) {
        tree[head[u]].add_line(-line.k, -line.m + tree[head[v]].lazy_constant);
      }
    }
    tree[head[u]].add_line(-2 * dist[u], sum + 1LL * dist[u] * dist[u]);
  }

  printf("%lld\n", dp[0] + c);
  return 0;
}
