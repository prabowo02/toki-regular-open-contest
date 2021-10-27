#include <algorithm>
#include <cstdio>
#include <vector>

const int N = 305 * 305;
const int Q = 100005;
const int M = 1000000000;

int _n, n;
int x[N], y[N];

int c[Q], a[Q], b[Q];

std::vector<std::pair<int, int>> comp;
int idxs[N];

struct BIT {
  int sum[N + Q];

  void add(int x, int val) {
    for (int i = x + 1; i <= comp.size(); i += i & -i) sum[i] += val;
  }

  int query(int x) {
    int ret = 0;
    for (int i = x + 1; i > 0; i -= i & -i) ret += sum[i];
    return ret;
  }
} bit;

int main() {
  scanf("%d", &n);

  _n = n;
  int divs = (M + n) / n;

  n = n*n;
  for (int i = 0; i < n; ++i) {
    scanf("%d %d", &x[i], &y[i]);
    x[i] /= divs;
    if (x[i] & 1) y[i] = M - y[i];
    comp.emplace_back(x[i], y[i]);
  }

  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    scanf("%d %d %d", &c[i], &a[i], &b[i]);
    --c[i];

    a[i] /= divs;
    if (a[i] & 1) b[i] = M - b[i];

    comp.emplace_back(a[i], b[i]);
  }

  std::sort(comp.begin(), comp.end());
  comp.resize(std::unique(comp.begin(), comp.end()) - comp.begin());

  for (int i = 0; i < n; ++i) {
    bit.add(idxs[i] = std::lower_bound(comp.begin(), comp.end(), std::make_pair(x[i], y[i])) - comp.begin(), 1);
  }

  std::vector<int> cnt(comp.size()), p(n);
  for (int i = 0; i < n; ++i) {
    p[bit.query(idxs[i] - 1) + cnt[idxs[i]]++] = i;
  }
  for (int i = 0; i < n; ++i) printf("%d ", p[i] + 1);
  printf("\n");

  for (int i = 0; i < q; ++i) {
    bit.add(idxs[c[i]], -1);
    idxs[c[i]] = std::lower_bound(comp.begin(), comp.end(), std::make_pair(a[i], b[i])) - comp.begin();
    bit.add(idxs[c[i]], 1);
    printf("%d\n", bit.query(idxs[c[i]]));
  }
  return 0;
}
