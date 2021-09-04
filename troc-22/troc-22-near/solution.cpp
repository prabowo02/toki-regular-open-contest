#include <bits/stdc++.h>
using namespace std;

template <int MOD>
class ModInt {
 public:
  int v;

  ModInt() : v(0) {}
  ModInt(long long _v) {
    v = int((-MOD < _v && _v < MOD) ? (_v) : (_v % MOD));
    if (v < 0) v += MOD;
  }

  friend bool operator==(const ModInt &a, const ModInt &b) { return a.v == b.v; }
  friend bool operator!=(const ModInt &a, const ModInt &b) { return a.v != b.v; }
  friend bool operator<(const ModInt &a, const ModInt &b) { return a.v < b.v; }
  friend bool operator<=(const ModInt &a, const ModInt &b) { return a.v <= b.v; }
  friend bool operator>(const ModInt &a, const ModInt &b) { return a.v > b.v; }
  friend bool operator>=(const ModInt &a, const ModInt &b) { return a.v >= b.v; }

  ModInt &operator+=(const ModInt &a) {
    if ((v += a.v) >= MOD) v -= MOD;
    return *this;
  }
  ModInt &operator-=(const ModInt &a) {
    if ((v -= a.v) < 0) v += MOD;
    return *this;
  }
  ModInt &operator*=(const ModInt &a) {
    v = 1ll * v * a.v % MOD;
    return *this;
  }
  ModInt &operator/=(const ModInt &a) {
    return (*this) *= inverse(a);
  }

  friend ModInt pow(ModInt a, long long x) {
    ModInt res = 1;
    assert(x >= 0);
    for (; x; x /= 2, a *= a)
      if (x & 1) res *= a;
    return res;
  }
  friend ModInt inverse(ModInt a) {
    assert(a.v != 0);
    return pow(a, MOD - 2);
  }

  ModInt operator+() const { return ModInt(v); }
  ModInt operator-() const { return ModInt(-v); }
  ModInt operator++() const { return *this += 1; }
  ModInt operator--() const { return *this -= 1; }

  friend ModInt operator+(ModInt a, const ModInt &b) { return a += b; }
  friend ModInt operator-(ModInt a, const ModInt &b) { return a -= b; }
  friend ModInt operator*(ModInt a, const ModInt &b) { return a *= b; }
  friend ModInt operator/(ModInt a, const ModInt &b) { return a /= b; }

  friend istream &operator>>(istream &is, ModInt &v) {
    is >> v.v;
    return is;
  }
  friend ostream &operator<<(ostream &os, const ModInt &v) {
    os << v.v;
    return os;
  }
};

const int MOD = 998244353;
using Mint = ModInt<MOD>;

Mint Solve(int N, int K, vector<int> P) {
  vector<vector<int>> adj(N);
  for (int i = 1; i < N; i++) {
    adj[P[i]].emplace_back(i);
  }
  vector<vector<Mint>> choose(K + 1, vector<Mint>(K + 1));
  for (int i = 0; i <= K; i++) {
    choose[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      choose[i][j] = choose[i - 1][j - 1] + choose[i - 1][j];
    }
  }
  // dp[power][node][label][is connected to lower label]
  vector<Mint> dp((K + 1) * N * N * 2);
  const auto id = [&](int i, int u, int x, int y) {
    return i * N * N * 2 + u * N * 2 + x * 2 + y;
  };
  for (int u = N - 1; u >= 0; u--) {
    vector<Mint> all_g, all_b, cur_g, cur_b;
    all_g = all_b = cur_g = cur_b = vector<Mint>(K + 1);
    for (int x = N - 1; x >= 0; x--) {
      for (int y = 0; y < 2; y++) {
        if (x == 0) {
          for (int i = 0; i <= K; i++) {
            dp[id(i, u, x, y)] = dp[id(i, u, 1, y)];
          }
          continue;
        }
        all_g[0] = 1, all_b[0] = (y == 0);
        for (int i = 1; i <= K; i++) {
          all_g[i] = all_g[i - 1] * x;
          all_b[i] = all_b[i - 1] * x;
        }
        for (auto v : adj[u]) {
          for (int i = 0; i <= K; i++) {
            cur_g[i] = cur_b[i] = 0;
            for (int d = -1; d <= 1; d++) {
              if (0 <= x + d && x + d < N) {
                cur_g[i] += dp[id(i, v, x + d, d == 1 || (x + d == 0))];
                if (d != -1) {
                  cur_b[i] += dp[id(i, v, x + d, d == 1 || (x + d == 0))];
                }
              }
            }
          }
          for (int i = K; i >= 0; i--) {
            Mint new_g = 0, new_b = 0;
            for (int j = 0; j <= i; j++) {
              new_g += choose[i][j] * all_g[j] * cur_g[i - j];
              new_b += choose[i][j] * all_b[j] * cur_b[i - j];
            }
            all_g[i] = new_g, all_b[i] = new_b;
          }
        }
        for (int i = 0; i <= K; i++) {
          dp[id(i, u, x, y)] = all_g[i] - all_b[i];
        }
      }
    }
  }
  Mint ans = pow(Mint(-N), K);
  for (int i = 1; i < N; i++) {
    ans += dp[id(K, 0, i, i == 0)];
  }
  return 2 * ans;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N, K = 2;
  cin >> N;

  vector<int> P(N, -1);
  for (int i = 1; i < N; i++) {
    cin >> P[i];
    P[i]--;
  }

  cout << Solve(N, K, P) << '\n';
  return 0;
}
