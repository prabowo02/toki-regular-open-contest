#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n;
int a[N];

int lst[N], prv[N];

struct SegTree {
  int mini[N << 2];
  int lazy[N << 2];

  void propagate(int idx) {
    for (int i = 0; i < 2; ++i) {
      mini[idx*2 + i + 1] += lazy[idx];
      lazy[idx*2 + i + 1] += lazy[idx];
    }
    lazy[idx] = 0;
  }

  void update(int idx, int l, int r, int ll, int rr, int val) {
    if (l > rr || r < ll) return;
    if (l >= ll && r <= rr) {
      mini[idx] += val;
      lazy[idx] += val;
      return;
    }

    propagate(idx);

    int mid = (l + r) >> 1;
    update(idx*2 + 1, l, mid+0, ll, rr, val);
    update(idx*2 + 2, mid+1, r, ll, rr, val);
    mini[idx] = min(mini[idx*2 + 1], mini[idx*2 + 2]);
  }

  int query(int idx, int l, int r, int ll, int rr) {
    if (l > rr || r < ll) return 1e9;
    if (l >= ll && r <= rr) return mini[idx];

    propagate(idx);

    int mid = (l + r) >> 1;
    return min(query(idx*2 + 1, l, mid, ll, rr), query(idx*2 + 2, mid+1, r, ll, rr));
  }

  void update(int l, int r, int val) {
    update(0, 0, n-1, l-1, r-1, val);
  }

  int query(int l, int r) {
    return query(0, 0, n-1, l-1, r-1);
  }
} tree;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    tree.update(prv[lst[a[i]]] + 1, lst[a[i]], -1);
    if (tree.query(1, lst[a[i]]) == 0) return 0 * printf("NO\n");
    tree.update(lst[a[i]] + 1, i, 1);
    prv[i] = lst[a[i]];
    lst[a[i]] = i;
  }

  printf("YES\n");
  return 0;
}
