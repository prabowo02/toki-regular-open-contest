#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int MOD = 998244353;

class SegTree {
  int n;
  int sum[N << 2];
  int lazy[N << 2];

  void updateNode(int idx, int l, int r, int val) {
    sum[idx] = (sum[idx] + 1LL * val * (r - l)) % MOD;
    lazy[idx] = (lazy[idx] + val) % MOD;
  }

  void push(int idx, int l, int r) {
    if (lazy[idx] == 0) return;
    int mid = (l + r) / 2;
    updateNode(idx + 1, l, mid, lazy[idx]);
    updateNode(idx + (mid - l) * 2, mid, r, lazy[idx]);
    lazy[idx] = 0;
  }

  void build(int idx, int l, int r, const std::vector<int> &vals) {
    if (l + 1 == r) {
      sum[idx] = vals[l];
      lazy[idx] = 0;
      return;
    }

    int mid = (l + r) / 2;
    build(idx + 1, l, mid, vals);
    build(idx + (mid - l) * 2, mid, r, vals);
    sum[idx] = (sum[idx + 1] + sum[idx + (mid - l) * 2]) % MOD;
  }

  void update(int idx, int l, int r, int ll, int rr, int val) {
    if (l >= rr || r <= ll) return;
    if (l >= ll && r <= rr) return updateNode(idx, l, r, val);

    push(idx, l, r);

    int mid = (l + r) / 2;
    update(idx + 1, l, mid, ll, rr, val);
    update(idx + (mid - l) * 2, mid, r, ll, rr, val);
    sum[idx] = (sum[idx + 1] + sum[idx + (mid - l) * 2]) % MOD;
  }

  int query(int idx, int l, int r, int ll, int rr) {
    if (l >= rr || r <= ll) return 0;
    if (l >= ll && r <= rr) return sum[idx];

    push(idx, l, r);

    int mid = (l + r) / 2;
    return (query(idx + 1, l, mid, ll, rr) +
            query(idx + (mid - l) * 2, mid, r, ll, rr)) % MOD;
  }

 public:
  void build(const std::vector<int> &vals) {
    n = (int) vals.size();
    build(0, 0, n, vals);
  }

  void update(int l, int r, int val) {
    update(0, 0, n, l, r, val);
  }

  void update(int x, int val) {
    update(x, x + 1, val);
  }

  int query(int l, int r) {
    return query(0, 0, n, l, r);
  }

  int query(int x) {
    return query(x, x + 1);
  }
} tree;

int n;
int a[N];
vector<int> adj[N];

int order[N];
int lft[N], rgt[N], par[N];
void bfs(int u=0) {
  vector<bool> vis(n);
  queue<int> q;

  q.push(u);
  vis[u] = true;
  order[u] = 0;

  int id = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();

    lft[u] = id;
    for (int v : adj[u]) {
      if (vis[v]) continue;
      vis[v] = true;
      q.push(v);
      par[v] = order[u];
      order[v] = id++;
    }
    rgt[u] = id;
  }
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

  bfs();

  vector<int> vals(n);
  for (int i = 0; i < n; ++i) {
    vals[order[i]] = a[i];
  }
  tree.build(vals);

  int q;
  scanf("%d", &q);
  for (int j = 0; j < q; ++j) {
    int t, x;
    scanf("%d %d", &t, &x);
    --x;

    if (t == 1) {
      int v = tree.query(order[x]);
      tree.update(lft[x], rgt[x], v);
      if (x > 0) {
        tree.update(par[x], v);
      }
    } else {
      int ans = tree.query(lft[x], rgt[x]);
      if (x > 0) {
        ans = (ans + tree.query(par[x])) % MOD;
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}
