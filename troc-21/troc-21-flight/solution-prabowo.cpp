#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, q;
int a[N];

struct SegTree {
  int n;
  vector<long long> pre;
  vector<int> hulls[N << 2];

  long long cross(int p, int q, int r) {
    return 1LL * (q - p) * (pre[r] - pre[q]) - 1LL * (r - q) * (pre[q] - pre[p]);
  }

  void build(int idx, int l, int r) {
    vector<int> &hull = hulls[idx];
    for (int i = l; i <= r; ++i) {
      while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), i) >= 0) hull.pop_back();
      hull.push_back(i);
    }

    if (l == r) return;

    int mid = (l + r) >> 1;
    build(idx * 2 + 1, l, mid + 0);
    build(idx * 2 + 2, mid + 1, r);
  };

  long long eval(const vector<int> &hull, int w) {
    int l = 1, r = (int) hull.size() - 1, ans = 0;
    while (l <= r) {
      int mid = (l + r) >> 1;
      if (pre[hull[mid]] - pre[hull[mid - 1]] >= -1LL * w * (hull[mid] - hull[mid - 1])) {
        l = mid + 1;
        ans = mid;
      } else {
        r = mid - 1;
        ans = mid - 1;
      }
    }

    return pre[hull[ans]] + 1LL * w * hull[ans];
  }

  long long query(int idx, int l, int r, int ll, int rr, int w) {
    if (r < ll) return eval(hulls[idx], 0);
    if (l > rr) return eval(hulls[idx], 0) + 1LL * w * (rr - ll + 1);
    if (l >= ll && r <= rr) return eval(hulls[idx], w) - 1LL * w * (ll - 1);
    int mid = (l + r) >> 1;
    return max(query(idx * 2 + 1, l, mid + 0, ll ,rr, w),
               query(idx * 2 + 2, mid + 1, r, ll, rr, w));
  }

  void build(const vector<long long> &_pre) {
    n = (int) _pre.size() - 1;
    pre = _pre;
    build(0, 1, n);
  }

  long long query(int l, int r, int w) {
    return max(0LL, query(0, 1, n, l, r, w));
  }
} treeMax, treeMin;

int main() {
  scanf("%d %d", &n, &q);
  vector<long long> prePos(n + 1), preNeg(n + 1);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    prePos[i] = prePos[i - 1] + a[i];
    preNeg[i] = preNeg[i - 1] - a[i];
  }

  treeMax.build(prePos); treeMin.build(preNeg);

  while (q--) {
    int l, r, w;
    scanf("%d %d %d", &l, &r, &w);

    printf("%lld\n", treeMax.query(l, r, w) + treeMin.query(l, r, -w));
  }
  return 0;
}
