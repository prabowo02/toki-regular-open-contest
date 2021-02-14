#include <bits/stdc++.h>
using namespace std;

template<int MOD>
class ModInt {
 public:
  int v;

  ModInt() : v(0) {}
  ModInt(long long _v) {
    v = int((-MOD < _v && _v < MOD) ? (_v) : (_v % MOD));
    if (v < 0) v += MOD; }

  friend bool operator==(const ModInt &a, const ModInt &b) { return a.v == b.v; }
  friend bool operator!=(const ModInt &a, const ModInt &b) { return a.v != b.v; }
  friend bool operator<(const ModInt &a, const ModInt &b) { return a.v < b.v; }
  friend bool operator<=(const ModInt &a, const ModInt &b) { return a.v <= b.v; }
  friend bool operator>(const ModInt &a, const ModInt &b) { return a.v > b.v; }
  friend bool operator>=(const ModInt &a, const ModInt &b) { return a.v >= b.v; }

  ModInt& operator+=(const ModInt &a) {
    if ((v += a.v) >= MOD) v -= MOD;
    return *this; }
  ModInt& operator-=(const ModInt &a) {
    if ((v -= a.v) < 0) v += MOD;
    return *this; }
  ModInt& operator*=(const ModInt &a) {
    v = 1ll * v * a.v % MOD;
    return *this; }
  ModInt& operator/=(const ModInt &a) {
    return (*this) *= inverse(a); }

  friend ModInt pow(ModInt a, long long x) {
    ModInt res = 1; assert(x >= 0);
    for (; x; x /= 2, a *= a) if (x & 1) res *= a;
    return res; }
  friend ModInt inverse(ModInt a) {
    assert(a.v != 0);
    return pow(a, MOD - 2); }

  ModInt operator+() const { return ModInt(v); }
  ModInt operator-() const { return ModInt(-v); }
  ModInt operator++() const { return *this += 1; }
  ModInt operator--() const { return *this -= 1; }

  friend ModInt operator+(ModInt a, const ModInt &b) { return a += b; }
  friend ModInt operator-(ModInt a, const ModInt &b) { return a -= b; }
  friend ModInt operator*(ModInt a, const ModInt &b) { return a *= b; }
  friend ModInt operator/(ModInt a, const ModInt &b) { return a /= b; }

  friend istream& operator>>(istream &is, ModInt &v) { is >> v.v; return is; }
  friend ostream& operator<<(ostream &os, const ModInt &v) { os << v.v; return os; }
};

const int MAX = 40;
const int MOD = 998244353;
using Mint = ModInt<MOD>;

vector<vector<Mint>> choose(MAX + 1, vector<Mint>(MAX + 1));
vector<vector<vector<bool>>> vis(MAX + 6, vector<vector<bool>>(MAX + 1, vector<bool>(MAX + 1)));
vector<vector<vector<Mint>>> cnt(MAX + 6, vector<vector<Mint>>(MAX + 1, vector<Mint>(MAX + 1)));
vector<vector<vector<Mint>>> sum(MAX + 6, vector<vector<Mint>>(MAX + 1, vector<Mint>(MAX + 1)));

pair<Mint, Mint> Solve(int t, int n, int m, const Mint &A, const Mint &B, const Mint &C) {
  if (m < 0) {
    return pair(0, 0);
  } else if (vis[t][n][m]) {
    return pair(cnt[t][n][m], sum[t][n][m]);
  }
  pair<Mint, Mint> res = pair(0, 0);
  if (t == 0) {
    if (m == 0) {
      return pair(n == 1, 0);
    }
    res.first  += Solve(0, n, m - 1, A, B, C).first  * n * (n + 1) / 2;
    res.second += Solve(0, n, m - 1, A, B, C).first  * n * (n + 1) / 2 * (B - A);
    res.second += Solve(0, n, m - 1, A, B, C).second * n * (n + 1) / 2;
    res.first  += Solve(2, n, m - 1, A, B, C).first  / 2;
    res.second += Solve(2, n, m - 1, A, B, C).first  / 2 * (C - A);
    res.second += Solve(2, n, m - 1, A, B, C).second / 2;
  } else if (t == 1) {
    res.first  += m * (Solve(2, n, m - 1, A, B, C).first  + Solve(0, n, m - 1, A, B, C).first  * n * n);
    res.second += m * (Solve(2, n, m - 1, A, B, C).second + Solve(0, n, m - 1, A, B, C).second * n * n);
  } else if (t == 2) {
    for (int node = 1; node <= n; node++) {
      for (int edge = node - 1; edge <= m; edge++) {
        Mint ways = choose[n][node] * choose[m][edge] * node * node;
        res.first  += ways * Solve(0, node, edge, A, B, C).first  * Solve(1, n - node, m - edge, A, B, C).first;
        res.second += ways * Solve(0, node, edge, A, B, C).second * Solve(1, n - node, m - edge, A, B, C).first;
        res.second += ways * Solve(0, node, edge, A, B, C).first  * Solve(1, n - node, m - edge, A, B, C).second;
      }
    }
  } else if (t == 3) {
    for (int node = 1; node <= n; node++) {
      for (int edge = node - 1; edge <= m; edge++) {
        Mint ways = choose[n - 1][node - 1] * choose[m][edge];
        for (int child = 0; child <= n - node && child <= m - edge; child++, ways *= node) {
          res.first  += ways * Solve(0, node, edge, A, B, C).first  * Solve(5 + child, n - node, m - edge, A, B, C).first;
          res.second += ways * Solve(0, node, edge, A, B, C).first  * Solve(5 + child, n - node, m - edge, A, B, C).second;
          res.second += ways * Solve(0, node, edge, A, B, C).second * Solve(5 + child, n - node, m - edge, A, B, C).first;
        }
      }
    }
  } else if (t == 4) {
    if (n == 0 && m == 0) {
      return pair(1, 0);
    }
    for (int node = 1; node <= n; node++) {
      for (int edge = node - 1; edge <= m; edge++) {
        Mint ways = choose[n - 1][node - 1] * choose[m][edge];
        res.first  += ways * Solve(3, node, edge, A, B, C).first  * Solve(4, n - node, m - edge, A, B, C).first;
        res.second += ways * Solve(3, node, edge, A, B, C).first  * Solve(4, n - node, m - edge, A, B, C).second;
        res.second += ways * Solve(3, node, edge, A, B, C).second * Solve(4, n - node, m - edge, A, B, C).first;
      }
    }
  } else {
    int child = t - 5;
    if (child == 0) return pair(n == 0 && m == 0, 0);
    for (int node = 1; node <= n; node++) {
      for (int edge = node - 1; edge <= m - 1; edge++) {
        Mint ways = choose[n - 1][node - 1] * choose[m][edge] * node * (m - edge);
        res.first  += ways * Solve(3, node, edge, A, B, C).first  * Solve(5 + child - 1, n - node, m - 1 - edge, A, B, C).first;
        res.second += ways * Solve(3, node, edge, A, B, C).first  * Solve(5 + child - 1, n - node, m - 1 - edge, A, B, C).second;
        res.second += ways * Solve(3, node, edge, A, B, C).second * Solve(5 + child - 1, n - node, m - 1 - edge, A, B, C).first;
      }
    }
  }

  vis[t][n][m] = true;
  cnt[t][n][m] = res.first;
  sum[t][n][m] = res.second;

  return res;
}

Mint Solve(int N, int M, Mint A, Mint B, Mint C) {
  for (int n = 0; n <= MAX; n++) {
    choose[n][0] = 1;
    for (int m = 1; m <= n; m++) {
      choose[n][m] = choose[n - 1][m] + choose[n - 1][m - 1];
    }
  }
  pair<Mint, Mint> res = Solve(4, N, M, A, B, C);
  return res.second / res.first + M * A;
}

int main() {
  int N, M, A, B, C;
  cin >> N >> M >> A >> B >> C;
  cout << Solve(N, M, A, B, C) << '\n';
  return 0;
}
