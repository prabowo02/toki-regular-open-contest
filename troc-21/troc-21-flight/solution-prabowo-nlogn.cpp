#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, q;
int a[N];

struct SegTree {
  int n;
  vector<long long> pre;
  vector<int> hulls[N << 2];
  long long maxi[N << 2];

  long long cross(int p, int q, int r) {
    return 1LL * (q - p) * (pre[r] - pre[q]) - 1LL * (r - q) * (pre[q] - pre[p]);
  }

  void build(int idx, int l, int r) {
    vector<int> &hull = hulls[idx];
    maxi[idx] = pre[l];
    for (int i = l; i <= r; ++i) {
      while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), i) >= 0) hull.pop_back();
      hull.push_back(i);
      maxi[idx] = max(maxi[idx], pre[i]);
    }

    if (l == r) return;

    int mid = (l + r) >> 1;
    build(idx * 2 + 1, l, mid + 0);
    build(idx * 2 + 2, mid + 1, r);
  };

  long long eval(vector<int> &hull, int w) {
    while (hull.size() >= 2 && pre[hull.back()] - pre[hull[hull.size() - 2]] <= -1LL * w * (hull.back() - hull[hull.size() - 2])) {
      hull.pop_back();
    }

    return pre[hull.back()] + 1LL * w * hull.back();
  }

  long long query(int idx, int l, int r, int ll, int rr, int w) {
    if (r < ll) return maxi[idx];
    if (l > rr) return maxi[idx] + 1LL * w * (rr - ll + 1);
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

  vector<tuple<int, int, int, int>> queries;
  for (int i = 0; i < q; ++i) {
    int l, r, w;
    scanf("%d %d %d", &l, &r, &w);
    queries.emplace_back(w, l, r, i);
  }
  sort(queries.begin(), queries.end());

  vector<long long> ans(q);
  for (int i = 0; i < q; ++i) {
    int l, r, w, idx;
    tie(w, l, r, idx) = queries[i];
    ans[idx] = treeMin.query(l, r, -w);
  }

  reverse(queries.begin(), queries.end());
  for (int i = 0; i < q; ++i) {
    int l, r, w, idx;
    tie(w, l, r, idx) = queries[i];
    ans[idx] += treeMax.query(l, r, w);
  }

  for (int i = 0; i < q; ++i) printf("%lld\n", ans[i]);
  return 0;
}
