#include <bits/stdc++.h>
using namespace std;

const int LG = 30;
const int MOD = 998244353;

int n;
int lst[LG];

int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }
  return ret;
}

int main() {
  scanf("%d", &n);

  for (int i = 0; i < LG; ++i) lst[i] = -1;

  int ans = 1;
  for (int i = 0; i < n; ++i) {
    int a; scanf("%d", &a);
    vector<pair<int, int>> v(LG);
    for (int j = LG - 1; j >= 0; --j) {
      if (a >> j & 1) lst[j] = i;
      v[j] = {lst[j], j};
    }
    sort(v.begin(), v.end(), greater<pair<int, int>>());

    int idx = i, cur = 0;
    for (int i = 0; i < LG; ++i) {
      ans = 1LL * ans * power(cur, idx - v[i].first) % MOD;
      cur |= 1 << v[i].second; idx = v[i].first;
    }
    ans = 1LL * ans * power(cur, idx + 1) % MOD;
  }

  printf("%d\n", ans);
  return 0;
}
