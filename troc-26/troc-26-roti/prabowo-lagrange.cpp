#include <bits/stdc++.h>
using namespace std;

const __int128 ONE = 1;
const int N = 200005;

int n, k;
int t[N];

vector<int> dec;

struct Line {
  int id;
  long long c;
  int m;
  Line(int id, long long c=0, int m=0): id(id), c(c), m(m) {}

  long long eval(int x) {
    return 1LL * m * x + c;
  }
};

struct CHT {

  int cur;
  vector<Line> lines;

  CHT(): cur(0) {}

  void add(int id, long long c, int m) {
    assert(lines.size() == 0 || lines.back().m > m);
    while (lines.size() >= 2) {
      long long c1 = lines.end()[-2].c, c2 = lines.end()[-1].c;
      int m1 = lines.end()[-2].m, m2 = lines.end()[-1].m;
      if (ONE * (c1 - c) * (m - m2) < ONE * (c2 - c) * (m - m1)) break;
      lines.pop_back();
    }
    lines.push_back(Line(id, c, m));
  }

  Line query(int x) {
    if (cur >= lines.size()) cur = lines.size() - 1;

    while (cur > 0 && lines[cur - 1].eval(x) <= lines[cur].eval(x)) --cur;
    while (cur + 1 < lines.size() && lines[cur + 1].eval(x) < lines[cur].eval(x)) ++cur;

    return lines[cur];
  }
};

const int K = 30;

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &t[i]);
  }

  vector<int> dec;
  for (int i = n - 1; i >= 0; --i) {
    while (dec.size() > 0 && t[dec.back()] <= t[i]) dec.pop_back();
    dec.push_back(i);
  }

  // dp[n] = min_i (t_dec[i] * (n - dec[n]) + dp[i - 1]) + penalty

  long long l = 0, r = 2e14;
  long long ans = 1e18;
  while (l <= r) {
    long long mid = (l + r) / 2;

    long long val = 0;
    vector<int> ks(dec.size());
    CHT cht; cht.add(-1, 0, t[dec[0]]);
    for (int i = 0; i < dec.size(); ++i) {
      Line line = cht.query(n - dec[i]);
      val = line.eval(n - dec[i]) + mid;
      ks[i] = (line.id >= 0 ? ks[line.id] + 1 : 1);
      if (i + 1 < dec.size()) cht.add(i, val, t[dec[i + 1]]);
    }

    if (ks.back() <= k) {
      r = mid - 1;
      ans = val - mid * ks.back();
    } else {
      l = mid + 1;
    }
  }

  printf("%lld\n", ans);
  return 0;
}
