#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, d;
char s[N];

struct SegTree {
  int n;
  int maxi[N << 2];
  int lazy[N << 2];

  void build(int idx, int l, int r, int a[]) {
    if (l == r - 1) {
      maxi[idx] = a[l];
      return;
    }

    int mid = (l + r) >> 1;
    build(idx*2 + 1, l, mid, a);
    build(idx*2 + 2, mid, r, a);
    maxi[idx] = max(maxi[idx*2 + 1], maxi[idx*2 + 2]);
  }

  void propagate(int idx) {
    for (int i = 0; i < 2; ++i) {
      maxi[idx*2 + i + 1] += lazy[idx];
      lazy[idx*2 + i + 1] += lazy[idx];
    }
    lazy[idx] = 0;
  }

  void update(int idx, int l, int r, int ll, int rr, int val) {
    if (l >= rr || r <= ll) return;
    if (l >= ll && r <= rr) {
      maxi[idx] += val;
      lazy[idx] += val;
      return;
    }

    int mid = (l + r) >> 1;
    propagate(idx);

    update(idx*2 + 1, l, mid, ll, rr, val);    
    update(idx*2 + 2, mid, r, ll, rr, val);
    maxi[idx] = max(maxi[idx*2 + 1], maxi[idx*2 + 2]);
  }

  int query(int idx, int l, int r, int x) {
    if (l == r - 1) return l;

    int mid = (l + r) >> 1;
    propagate(idx);

    if (maxi[idx*2 + 1] > x) return query(idx*2 + 1, l, mid, x);
    return query(idx*2 + 2, mid, r, x);
  }

  void build(int _n, int a[]) {
    n = _n;
    build(0, 0, n, a);
  }

  void update(int l, int r, int val) {
    update(0, 0, n, l, r, val);
  }

  int query(int x) {
    if (maxi[0] <= x) return -2;
    return query(0, 0, n, x);
  }
} tree;

int a[N];

int main() {
  scanf("%d %d", &n, &d);
  scanf("%s", s);

  int cur = 0;
  for (int i = 0; i < n; ++i) {
    cur += (s[i] == '1');
    if (i >= d) cur -= (s[i - d] == '1');
    a[i] = cur;
  }

  tree.build(n, a);

  int q;
  scanf("%d", &q);
  while (q--) {
    int t, x;
    scanf("%d %d", &t, &x);

    if (t == 1) {
      --x;
      int delta;

      if (s[x] == '1') delta = -1, s[x] = '0';
      else if (s[x] == '0') delta = 1, s[x] = '1';

      tree.update(x, min(n, x + d), delta);
    } else if (t == 2) {
      printf("%d\n", tree.query(x) + 1);
    }
  }
  return 0;
}
