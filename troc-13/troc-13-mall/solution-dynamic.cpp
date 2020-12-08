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
  struct Node {
    Line line = Line();

    Node *lc = nullptr;
    Node *rc = nullptr;
  };

  int sz;
  Node *root = nullptr;

  void InsertLineKnowingly(Node* &n, int tl, int tr, Line x) {
    if (n == nullptr) n = new Node();
    if (n->line.get(tl) >= x.get(tl)) swap(n->line, x);
    if (n->line.get(tr) <= x.get(tr)) return;
    int mid = (tl + tr) / 2;
    if (n->line.get(mid) <= x.get(mid)) {
      InsertLineKnowingly(n->rc, mid + 1, tr, x);
    } else {
      swap(n->line, x);
      InsertLineKnowingly(n->lc, tl, mid, x);
    }
  }

  void InsertLine(Node* &n, int tl, int tr, int l, int r, Line x) {
    if (tr < l || r < tl || tl > tr || l > r) return;
    if (n == nullptr) n = new Node();
    if (l <= tl && tr <= r) return InsertLineKnowingly(n, tl, tr, x);
    int mid = (tl + tr) / 2;
    InsertLine(n->lc, tl, mid, l, r, x);
    InsertLine(n->rc, mid + 1, tr, l, r, x);
  }

  long long Query(Node* &n, int tl, int tr, int x) {
    if (n == nullptr) return inf;
    if (tl == tr) return n->line.get(x);
    int mid = (tl + tr) / 2;
    if (x <= mid) {
      return min(n->line.get(x), Query(n->lc, tl, mid, x));
    } else {
      return min(n->line.get(x), Query(n->rc, mid + 1, tr, x));
    }
  }

 public:
  LiChao() {}
  LiChao(long long sz) : sz(sz) {}
  
  void InsertLine(int l, int r, Line x) {
    return InsertLine(root, 1, sz, l, r, x);
  }

  long long Query(int x) {
    return max(-inf, Query(root, 1, sz, x));
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

  LiChao li_chao(H);
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
