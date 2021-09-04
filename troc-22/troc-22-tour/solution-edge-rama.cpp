// Alternate problem version: each edge is used exactly once
#include <bits/stdc++.h>
using namespace std;

using lint = long long;
const lint INF = 2e18;

class Line {
 public:
  lint a = 0;
  lint b = -INF;
  Line() {}
  Line(lint a, lint b) : a(a), b(b) {}
  lint get(lint x) {
    return a * x + b;
  }
};

class Compress {
 public:
  int n;
  vector<int> coords;
  const int& operator[](int i) const {
    assert(0 <= i && i < n);
    return coords[i];
  }
  Compress() {}
  Compress(vector<int> coords_) : coords(coords_) {
    sort(begin(coords), end(coords));
    coords.resize(unique(begin(coords), end(coords)) - begin(coords));
    n = coords.size();
  }
};

class LiChao {
 public:
  LiChao(int n_, vector<int> coords) : T(n_) {
    C = Compress(coords);
    n = C.n;
  }

  int Merge(int u, int v) {
    return Merge(u, v, 0, n - 1);
  }

  lint Get(int u, lint x) {
    return -Get(u, x, 0, n - 1);
  }

  void Add(int u, lint x) {
    return Apply(u, -x);
  }

  void ModifyLine(int u, Line line) {
    line.a *= -1;
    line.b *= -1;
    T[u].line = line;
  }

 private:
  struct Node {
    int l = -1;
    int r = -1;
    lint lazy = 0;
    Line line = Line();
  };

  int n;
  Compress C;
  vector<Node> T;

  void Apply(int u, lint x) {
    if (u != -1) {
      T[u].line.b += x;
      T[u].lazy += x;
    }
  }

  void Push(int u) {
    if (u != -1) {
      Apply(T[u].l, T[u].lazy);
      Apply(T[u].r, T[u].lazy);
      T[u].lazy = 0;
    }
  }

  int Merge(int u, int v, int l, int r) {
    Push(u), Push(v);
    if (u == -1) return v;
    if (v == -1) return u;

    int m = (l + r) / 2;
    T[u].l = Merge(T[u].l, T[v].l, l, m);
    T[u].r = Merge(T[u].r, T[v].r, m + 1, r);
    T[v].l = T[v].r = -1;

    if (T[u].line.get(C[l]) < T[v].line.get(C[l])) {
      swap(T[u].line, T[v].line);
    }
    if (T[u].line.get(C[r]) < T[v].line.get(C[r])) {
      // Each nontrivial call to Merge() will increase the inserted node's depth by 1
      // Maximum depth of a node is O(log N) -> total time complexity is O(N log N)
      if (T[u].line.get(C[m]) > T[v].line.get(C[m])) {
        T[u].r = Merge(T[u].r, v, m + 1, r);
      } else {
        swap(T[u].line, T[v].line);
        T[u].l = Merge(T[u].l, v, l, m);
      }
    }
    return u;
  }

  lint Get(int u, lint x, int l, int r) {
    Push(u);
    if (u == -1) return -INF;
    int m = (l + r) / 2;
    return max(T[u].line.get(x), x <= C[m] ? Get(T[u].l, x, l, m) : Get(T[u].r, x, m + 1, r));
  }
};

lint Solve(int N, lint C, vector<int> P, vector<int> D) {
  vector<int> S(N);
  vector<vector<int>> adj(N);
  for (int i = 1; i < N; i++) {
    S[i] = D[i] + S[P[i]];
    adj[P[i]].emplace_back(i);
  }
  LiChao T(N, S);
  vector<int> tree(N);
  vector<lint> dp0(N);  // excluding parent edge
  vector<lint> dp1(N);  // including parent edge
  for (int u = N - 1; u >= 0; u--) {
    tree[u] = u;
    for (auto v : adj[u]) {
      dp1[v] = C + 1ll * S[u] * S[u] + T.Get(tree[v], S[u]);
      dp0[u] += dp1[v];
    }
    T.ModifyLine(tree[u], Line(-2 * S[u], 1ll * S[u] * S[u] + dp0[u]));
    for (auto v : adj[u]) {
      T.Add(tree[v], dp0[u] - dp1[v]);
      tree[u] = T.Merge(tree[u], tree[v]);
    }
  }
  return dp0[0];
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N;
  lint C;
  cin >> N >> C;

  vector<int> P(N), D(N);
  for (int i = 1; i < N; i++) {
    cin >> P[i] >> D[i];
    P[i]--;
  }

  cout << Solve(N, C, P, D) << '\n';
  return 0;
}
