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
  long long constant;
  int slope;

  Line(long long _constant=0, int _slope=0): constant(_constant), slope(_slope) {}

  long long eval(int x) {
    return 1LL * slope * x + constant;
  }
};

// Min LiChao
class LiChao {
  vector<int> coordinates;
  vector<Line> lines;
  long long lazy_constant;

  void update(int node, int l, int r, Line line) {
    bool ll = line.eval(coordinates[l]) <= lines[node].eval(coordinates[l]);
    bool rr = line.eval(coordinates[r]) <= lines[node].eval(coordinates[r]);

    if (ll == rr) {
      if (ll) swap(lines[node], line);
      return;
    }

    int mid = (l + r) >> 1;
    update(node*2 + 1, l, mid+0, line);
    update(node*2 + 2, mid+1, r, line);
  }

  long long query(int node, int l, int r, int x) {
    if (l == x && r == x) return lines[node].eval(coordinates[x]);

    int mid = (l + r) >> 1;
    return min(lines[node].eval(coordinates[x]),
      x <= mid ? query(node*2 + 1, l, mid, x) : query(node*2 + 2, mid+1, r, x));
  }

  inline int getIdx(int coor) {
    return lower_bound(coordinates.begin(), coordinates.end(), coor) - coordinates.begin();
  }

 public:
  void init(vector<int> _coordinates) {
    lazy_constant = 0;
    coordinates = _coordinates;
    lines = vector<Line>(coordinates.size() * 4, Line(INFLL));
  }

  void add_line(Line line) {
    line.constant -= lazy_constant;
    lines.push_back(line);
    update(0, 0, (int) coordinates.size() - 1, line);
  }

  void add_constant(long long c) {
    lazy_constant += c;
  }

  long long query(int x) {
    return query(0, 0, (int) coordinates.size() - 1, getIdx(x)) + lazy_constant;
  }

  vector<Line> get_lines() {
    vector<Line> ret;
    for (Line line : lines) {
      if (line.constant == INFLL) continue;
      line.constant += lazy_constant;
      ret.push_back(line);
    }
    return ret;
  }
} tree[N];

void init() {
  vector<vector<int>> coordinates(n);
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
    for (int v : adj[u]) coordinates[head[v]].push_back(dist[u]);
  }

  for (int u = 0; u < n; ++u) {
    sort(coordinates[u].begin(), coordinates[u].end());
    coordinates[u].resize(unique(coordinates[u].begin(), coordinates[u].end()) - coordinates[u].begin());
    tree[u].init(coordinates[u]);
  }
}

int main() {
  scanf("%d %lld", &n, &c);
  if (n == 1) {
    printf("%lld\n", c);
    return 0;
  }
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
      if (heavy[u] != v) for (Line line : tree[v].get_lines()) {
        tree[head[u]].add_line(line);
      }
    }
    tree[head[u]].add_line(Line(sum + 1LL * dist[u] * dist[u], -2 * dist[u]));
  }

  printf("%lld\n", dp[0] + c);
  return 0;
}
