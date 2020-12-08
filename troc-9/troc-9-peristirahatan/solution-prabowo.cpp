#pragma GCC diagnostic ignored "-Wshift-op-parentheses"

#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int INF = 2000000005;

int n, q;
int t[N];

struct SegTree {
  struct Node {
    int mini, maxi, lazy;

    Node() {
      mini = INF; maxi = -INF;
      lazy = 0;
    }

    Node operator + (const Node &other) {
      Node ret;
      ret.mini = min(mini, other.mini);
      ret.maxi = max(maxi, other.maxi);
      ret.lazy = 0;
      return ret;
    }

    Node operator += (int val) {
      mini += val;
      maxi += val;
      lazy += val;

      return *this;
    }
  };

  Node nodes[N << 2];

  void build(int node, int l, int r) {
    if (l == r) {
      nodes[node].mini = nodes[node].maxi = t[l];
      nodes[node].lazy = 0;
      return;
    }

    int mid = l + r >> 1;

    build(node*2 + 1, l, mid+0);
    build(node*2 + 2, mid+1, r);
    nodes[node] = nodes[node*2 + 1] + nodes[node*2 + 2];
  }

  void propagate(int node) {
    nodes[node*2 + 1] += nodes[node].lazy;
    nodes[node*2 + 2] += nodes[node].lazy;
    nodes[node].lazy = 0;
  }

  void update(int node, int l, int r, int a, int b, int val) {
    if (l > b || r < a) return;
    if (l >= a && r <= b) {
      nodes[node] += val;
      return;
    }

    propagate(node);

    int mid = l + r >> 1;

    update(node*2 + 1, l, mid+0, a, b, val);
    update(node*2 + 2, mid+1, r, a, b, val);
    nodes[node] = nodes[node*2 + 1] + nodes[node*2 + 2];
  }

  Node query(int node, int l, int r, int a, int b) {
    if (l > b || r < a) return Node();
    if (l >= a && r <= b) return nodes[node];

    propagate(node);

    int mid = l + r >> 1;

    return query(node*2 + 1, l, mid+0, a, b) + query(node*2 + 2, mid+1, r, a, b);
  }

  void build() {
    build(0, 0, n-1);
  }

  void update(int l, int r, int val) {
    update(0, 0, n-1, l, r, val);
  }

  pair<int, int> query(int l, int r) {
    Node res = query(0, 0, n-1, l, r);
    return {res.mini, res.maxi};
  }
} tree1, tree2;

int main() {
  scanf("%d %d", &n ,&q);
  for (int i = 0; i < n; ++i) scanf("%d", &t[i]);

  for (int i = 0; i < n; ++i) {
    t[i] += i;
  }
  tree1.build();

  for (int i = 0; i < n; ++i) {
    t[i] -= i*2;
  }
  tree2.build();

  while (q--) {
    int op;
    scanf("%d", &op);

    if (op == 1) {
      int x, y, c;
      scanf("%d %d %d", &x, &y, &c);
      --x, --y;

      tree1.update(x, y, c);
      tree2.update(x, y, c);
    } else if (op == 2) {
      int x, y, z;
      scanf("%d %d %d", &x, &y, &z);
      --x, --y, --z;

      pair<int, int> q1 = tree1.query(max(x, z), y), q2 = tree2.query(x, min(y, z));
      int mini = min(q1.first - z, q2.first + z);
      int maxi = max(q1.second - z, q2.second + z);

      printf("%d\n", maxi - mini);
    }
  }
  return 0;
}
