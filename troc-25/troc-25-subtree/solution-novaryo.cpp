#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <cstdio>
#include <vector>

int readInt() {
  int ret = 0;
  char c = getchar_unlocked();
  while ('0' <= c && c <= '9') {
    ret = ret * 10 + c - '0';
    c = getchar_unlocked();
  }
  return ret;
}

const int N = 100000;
const int MOD = 998244353;

int n;
int a[N];
std::vector<int> adj[N];

int order[N];
int lft[N], rgt[N], par[N];
int q[N];
bool vis[N];
void bfs(int u=0) {
  int st = 0, en = 0;

  q[en++] = u;
  vis[u] = true;
  order[u] = 0;

  int id = 1;
  while (st != en) {
    int u = q[st++];

    lft[u] = id;
    for (int v : adj[u]) {
      if (vis[v]) continue;
      vis[v] = true;
      q[en++] = v;
      par[v] = order[u];
      order[v] = id++;
    }
    rgt[u] = id;
  }
}

long long vals[N];

long long total, sumAll;

int main() {
  n = readInt();
  for (int i = 0; i < n; ++i) {
    a[i] = readInt();
    total += a[i];
  }

  int u, v;
  for (int i = 1; i < n; ++i) {
    u = readInt() - 1; v = readInt() - 1;

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  bfs();

  for (int i = 0; i < n; ++i) {
    vals[order[i]] = a[i];
  }

  int q = readInt(), t, x;
  int l, r;
  for (int j = 0; j < q; ++j) {
    t = readInt(), x = readInt() - 1;

    l = lft[x], r = rgt[x];
    if (t == 1) {
      int v = vals[order[x]] % MOD;
      total = (total + (r - l) * v) % MOD;

      if (x > 0) {
        vals[par[x]] += v;
      }
      if (r - l > 50000) {
        sumAll += v;
        if (sumAll > MOD) sumAll -= MOD;
        v = MOD - v;
        for (int i = 0; i < l; ++i) {
          vals[i] += v;
        }

        for (int i = r; i < n; ++i) {
          vals[i] += v;
        }
      } else {
        for (int i = l; i < r; ++i) {
          vals[i] += v;
        }
      }
    } else {
      long long ans = sumAll * (r - l + (x > 0));
      for (int i = l; i < r; ++i) {
        ans += vals[i];
      }
      if (x > 0) {
        ans += vals[par[x]];
      }
      printf("%lld\n", ans % MOD);
    }
  }
  return 0;
}