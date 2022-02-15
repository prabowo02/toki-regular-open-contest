#include <bits/stdc++.h>
using namespace std;

const __int128 ONE = 1;
const int N = 200005;

int n, k;
int t[N];

vector<int> dec;

struct CHT {
  struct Line {
    long long c;
    int m;
    Line(long long c=0, int m=0): c(c), m(m) {}

    long long eval(int x) {
      return 1LL * m * x + c;
    }
  };

  int cur;
  vector<Line> lines;

  CHT(): cur(0) {}

  void add(long long c, int m) {
    assert(lines.size() == 0 || lines.back().m > m);
    while (lines.size() >= 2) {
      long long c1 = lines.end()[-2].c, c2 = lines.end()[-1].c;
      int m1 = lines.end()[-2].m, m2 = lines.end()[-1].m;
      if (ONE * (c1 - c) * (m - m2) < ONE * (c2 - c) * (m - m1)) break;
      lines.pop_back();
    }
    lines.push_back(Line(c, m));
  }

  long long query(int x) {
    if (cur >= lines.size()) cur = lines.size() - 1;

    while (cur > 0 && lines[cur - 1].eval(x) < lines[cur].eval(x)) --cur;
    while (cur + 1 < lines.size() && lines[cur + 1].eval(x) < lines[cur].eval(x)) ++cur;

    return lines[cur].eval(x);
  }
};

const int K = 30;

CHT cht[K];

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

  // dp[n] = min_i (t_dec[i] * (n - dec[n]) + dp[i - 1])

  long long ans = 1e18;
  k = min(k, K - 1);
  cht[0].add(0, t[dec[0]]);
  for (int i = 0; i < dec.size(); ++i) {
    for (int j = k; j > 0; --j) {
      if (j > i + 1) continue;
      long long val = cht[j - 1].query(n - dec[i]);
      if (i + 1 == dec.size()) {
        ans = min(ans, val);
      } else {
        cht[j].add(val, t[dec[i + 1]]);
      }
    }
  }

  printf("%lld\n", ans);
  return 0;
}
