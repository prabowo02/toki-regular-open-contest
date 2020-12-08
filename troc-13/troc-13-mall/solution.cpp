#include <bits/stdc++.h>
using namespace std;

const long long inf = 2e18;

struct Line {
  long long a, b;
  Line() : a(0), b(inf) {}
  Line(long long a, long long b) : a(a), b(b) {}
  long long get(int x) { return a * x + b; }
};

class LiChao {
 private:
  int sz;
  vector<int> coordinates;
  vector<Line> tree;

  void InsertLineKnowingly(int n, int tl, int tr, Line x) {
    if (tree[n].get(coordinates[tl]) >= x.get(coordinates[tl])) swap(tree[n], x);
    if (tree[n].get(coordinates[tr]) <= x.get(coordinates[tr])) return;
    int mid = (tl + tr) / 2;
    int lc = n + 1;
    int rc = n + 2 * (mid - tl + 1);
    if (tree[n].get(coordinates[mid]) <= x.get(coordinates[mid])) {
      InsertLineKnowingly(rc, mid + 1, tr, x);
    } else {
      swap(tree[n], x);
      InsertLineKnowingly(lc, tl, mid, x);
    }
  }

  void InsertLine(int n, int tl, int tr, int l, int r, Line x) {
    if (tr < l || r < tl || tl > tr || l > r) return;
    if (l <= tl && tr <= r) return InsertLineKnowingly(n, tl, tr, x);
    int mid = (tl + tr) / 2;
    int lc = n + 1;
    int rc = n + 2 * (mid - tl + 1);
    InsertLine(lc, tl, mid, l, r, x);
    InsertLine(rc, mid + 1, tr, l, r, x);
  }

  long long Query(int n, int tl, int tr, int x) {
    if (tl == tr) return tree[n].get(x);
    int mid = (tl + tr) / 2;
    int lc = n + 1;
    int rc = n + 2 * (mid - tl + 1);
    if (x <= coordinates[mid]) {
      return min(tree[n].get(x), Query(lc, tl, mid, x));
    } else {
      return min(tree[n].get(x), Query(rc, mid + 1, tr, x));
    }
  }

 public:
  LiChao() {}
  LiChao(vector<int> q_pos) {
    sort(begin(q_pos), end(q_pos));
    q_pos.resize(unique(begin(q_pos), end(q_pos)) - begin(q_pos));
    sz = q_pos.size();
    tree.resize(2 * sz);
    coordinates = q_pos;
  }

  void InsertLine(int l, int r, Line x) {
    int ll = lower_bound(begin(coordinates), end(coordinates), l) - begin(coordinates);
    int rr = lower_bound(begin(coordinates), end(coordinates), r) - begin(coordinates);
    return InsertLine(1, 0, sz - 1, ll, rr, x);
  }

  long long Query(int x) {
    return min(inf, Query(1, 0, sz - 1, x));
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);

  int H, N;
  cin >> H >> N;

  vector<int> D(N);
  for (int i = 0; i < N; i++) {
    cin >> D[i];
  }

  int S;
  cin >> S;

  vector<int> A(N), B(N), T(N), Q(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i] >> B[i] >> T[i] >> Q[i];
  }

  int X;
  cin >> X;
  X--;

  vector<int> positions = {1, H};
  for (int i = 0; i < N; i++) {
    positions.emplace_back(D[i]);
    positions.emplace_back(A[i]);
    positions.emplace_back(B[i]);
  }

  LiChao li_chao(positions);
  li_chao.InsertLine(D[X], D[X], Line(0, 0));

  vector<long long> dist(N, inf);

  for (int lo = X, hi = X; 0 <= lo || hi < N;) {
    long long l = (lo <  0 ? inf : li_chao.Query(D[lo]));
    long long r = (hi >= N ? inf : li_chao.Query(D[hi]));

    int u = (l <= r ? lo-- : hi++);
    dist[u] = li_chao.Query(D[u]);

    li_chao.InsertLine(1, D[u], Line(- S, dist[u] + 1ll * D[u] * S));
    li_chao.InsertLine(D[u], H, Line(+ S, dist[u] - 1ll * D[u] * S));

    li_chao.InsertLine(A[u], D[u], Line(- T[u], dist[u] + Q[u] + 1ll * D[u] * T[u]));
    li_chao.InsertLine(D[u], B[u], Line(+ T[u], dist[u] + Q[u] - 1ll * D[u] * T[u]));

    li_chao.InsertLine(1, A[u], Line(- S, li_chao.Query(A[u]) + 1ll * A[u] * S));
    li_chao.InsertLine(B[u], H, Line(+ S, li_chao.Query(B[u]) - 1ll * B[u] * S));
  }

  for (int i = 0; i < N; i++) {
    cout << dist[i] << "\n";
  }
  return 0;
}
