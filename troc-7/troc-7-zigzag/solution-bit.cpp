#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n;
int a[N], b[N];

int prv[2][N];

struct BIT {
  pair<int, int> maxs[N];

  pair<int, int> query(int x) {
    pair<int, int> ret;
    for (int i = x; i > 0; i -= i & -i) {
      ret = max(ret, maxs[i]);
    }

    return ret;
  }

  void update(int x, int val, int idx) {
    for (int i = x; i <= n; i += i & -i) {
      maxs[i] = max(maxs[i], {val, idx});
    }
  }
} lft, rgt;

void compress(int a[]) {
  vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    v[i] = a[i];
  }

  sort(v.begin(), v.end());
  v.resize(unique(v.begin(), v.end()) - v.begin());

  for (int i = 0; i < n; ++i) {
    a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", a + i);
    b[i] = a[i];
  }
  reverse(a, a + n);
  reverse(b, b + n);

  compress(a);

  int ans = 0; pair<int, int> idx;
  for (int i = 0; i < n; ++i) {
    pair<int, int> p = lft.query(a[i] - 1);
    pair<int, int> q = rgt.query(n - a[i]);

    rgt.update(n - a[i] + 1, p.first + 1, i+1);
    lft.update(a[i], q.first + 1, i+1);

    prv[0][i+1] = p.second;
    prv[1][i+1] = q.second;

    if (ans < p.first + 1) {
      ans = p.first + 1;
      idx = {i+1, 0};
    }

    if (ans < q.first + 1) {
      ans = q.first + 1;
      idx = {i+1, 1};
    }
  }

  printf("%d\n", ans);
  while (true) {
    printf("%d", b[idx.first - 1]);
    idx = {prv[idx.second][idx.first], idx.second ^ 1};

    if (idx.first == 0) {
      printf("\n");
      break;
    } else printf(" ");
  }
  return 0;
}
