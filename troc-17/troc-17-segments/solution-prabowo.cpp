#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n;
int a[N];

int idx[N];
vector<int> pos[N];

struct SegTree {
  int maxi[N << 2];
  int lazy[N << 2];

  void propagate(int idx) {
    for (int i = 0; i < 2; ++i) {
      maxi[idx*2 + i + 1] += lazy[idx];
      lazy[idx*2 + i + 1] += lazy[idx];
    }
    lazy[idx] = 0;
  }

  void update(int idx, int l, int r, int ll, int rr, int val) {
    if (l > rr || r < ll) return;
    if (l >= ll && r <= rr) {
      maxi[idx] += val;
      lazy[idx] += val;
      return;
    }

    int mid = (l + r) >> 1;
    propagate(idx);

    update(idx*2 + 1, l, mid+0, ll, rr, val);
    update(idx*2 + 2, mid+1, r, ll, rr, val);
    maxi[idx] = max(maxi[idx*2 + 1], maxi[idx*2 + 2]);
  }

  void update(int l, int r, int val) {
    update(0, 0, N-1, l, r, val);
  }

  int query() { return maxi[0]; }
} tree;

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    pos[a[i]].emplace_back(i);
  }

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    ++idx[a[i]];
    if (idx[a[i]] == pos[a[i]].size());
    else if (idx[a[i]] == 1) {
      tree.update(pos[a[i]][idx[a[i]]], pos[a[i]].back() - 1, 1);
    } else {
      tree.update(pos[a[i]][idx[a[i]] - 1], pos[a[i]][idx[a[i]]] - 1, -1);
    }

    ans = max(ans, tree.query());
  }

  printf("%d\n", ans);
  return 0;
}
