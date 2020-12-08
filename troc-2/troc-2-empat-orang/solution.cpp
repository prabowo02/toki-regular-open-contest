#include <bits/stdc++.h>

using namespace std;

#define ll long long

const ll is_query = -(1LL<<62);
struct Line {
  ll m, b;
  mutable function<const Line*()> succ;
  bool operator<(const Line& rhs) const {
    if (rhs.b != is_query) return m > rhs.m; // min: reverse it
    const Line* s = succ();
    if (!s) return 0;
    ll x = rhs.m;
    return b - s->b > (s->m - m) * x; // min: reverse it
  }
};
struct HullDynamic : public multiset<Line> { // will maintain upper hull for maximum
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return 0;
      return y->m == z->m && y->b >= z->b; // min: reverse it
    }
    auto x = prev(y);
    if (z == end()) return y->m == x->m && y->b >= x->b; // min: reverse it
    return (x->b - y->b)*(z->m - y->m) >= (y->b - z->b)*(y->m - x->m); // beware overflow!
  }
  void insert_line(ll m, ll b) {
    auto y = insert({ m, b });
    y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
    if (bad(y)) { erase(y); return; }
    while (next(y) != end() && bad(next(y))) erase(next(y));
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }
  ll eval(ll x) {
    auto l = *lower_bound((Line) { x, is_query });
    return l.m * x + l.b;
  }
};

const int N = 5e4 + 5;
const int M = 4;
const ll inf = 1e17;

ll dp[N * 3][M];
vector<pair<ll, ll>> add[3 * N][M];   // m - b
ll c[N][M], w[N][M];
int s[M], t[M], n;

int dist(int from, int to) {
  int ret = to - from;
  if (ret < 0) ret += n;
  return ret;
}

int get(int from, int to, int k) {
  ll ret = c[to][k];
  for (int i = from; i != to; i = (i + 1) % n) {
    ret = min(ret, c[i][k]);
  }
  return ret;
}

ll cost(int from, int to, int k) {
  ll ret = 0;
  for (int i = from; i != to; i = (i + 1) % n) {
    ret += w[i][k];
  }
  return ret;
}

int main() {
  for (int i = 0; i < N * 3; i++) {
    for (int j = 0; j < M; j++) {
      dp[i][j] = inf;
    }
  }
  scanf("%d", &n);
  vector<ll> circle, mini;
  circle.assign(M, 0);
  mini.assign(M, inf);

  for (int k = 0; k < M; k++) {
    for (int i = 0; i < n; i++) scanf("%lld", &c[i][k]), mini[k] = min(mini[k], c[i][k]);
    for (int i = 0; i < n; i++) scanf("%lld", &w[i][k]), circle[k] += w[i][k];
  }

  for (int i = 0; i < M; i++) scanf("%d %d", s + i, t + i), s[i]--, t[i]--;
  vector<ll> full;
  full.resize(M);
  for (int k = 0; k < M; k++) {
    full[k] = min(circle[k], n * mini[k]);
  }

  for (int j = 0; j < M; j++) {
    ll rem = dist(s[j], t[j]);
    ll stay_in_near = get(s[j], t[j], j);
    ll walk_in_near = cost(s[j], t[j], j);
    add[rem][j].emplace_back(stay_in_near, walk_in_near - rem*stay_in_near);
    add[rem + n][j].emplace_back(mini[j], circle[j] + walk_in_near - (rem+n)*mini[j]);
    add[rem + 2*n][j].emplace_back(mini[j], circle[j] + full[j] + walk_in_near - (rem+2*n)*mini[j]);

    HullDynamic hull;
    for (int i = 0; i < 3 * N; i++) {
      for (auto it : add[i][j]) {
        hull.insert_line(it.first, it.second);
      }
      if (!hull.empty()) {
        dp[i][j] = hull.eval(i);
      }
    }
  }
  ll ans = inf; int at = -1;
  for (int i = 0; i < 3 * N; i++) {
    ll cur = 0;
    for (int j = 0; j < M; j++) {
      cur += dp[i][j];
    }
    if (cur < ans) {
      ans = cur;
      at = i;
    }
  }
  printf("%lld\n", ans);
  return 0;
}
