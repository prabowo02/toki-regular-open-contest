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

const int MOD = 998244353;
using Mint = ModInt<MOD>;

Mint Solve(int N, int M, Mint A, Mint B, Mint C) {
  vector<vector<Mint>> choose(max(N, M) + 1, vector<Mint>(max(N, M) + 1));
  vector<vector<vector<Mint>>> cnt(5, vector<vector<Mint>>(N + 1, vector<Mint>(M + 1)));
  vector<vector<vector<Mint>>> sum(5, vector<vector<Mint>>(N + 1, vector<Mint>(M + 1)));

  for (int n = 0; n <= max(N, M); n++) {
    choose[n][0] = 1;
    for (int m = 1; m <= n; m++) {
      choose[n][m] = choose[n - 1][m] + choose[n - 1][m - 1];
    }
  }

  cnt[0][1][0] = 1;
  cnt[4][0][0] = 1;

  for (int n = 1; n <= N; n++) {
    for (int m = n - 1; m <= M; m++) {
      if (m > 0) {
        cnt[0][n][m] += cnt[0][n][m - 1] * n * (n + 1) / 2;
        sum[0][n][m] += cnt[0][n][m - 1] * n * (n + 1) / 2 * (B - A);
        sum[0][n][m] += sum[0][n][m - 1] * n * (n + 1) / 2;

        cnt[0][n][m] += cnt[2][n][m - 1] / 2;
        sum[0][n][m] += cnt[2][n][m - 1] / 2 * (C - A);
        sum[0][n][m] += sum[2][n][m - 1] / 2;

        cnt[1][n][m] += m * (cnt[2][n][m - 1] + cnt[0][n][m - 1] * n * n);
        sum[1][n][m] += m * (sum[2][n][m - 1] + sum[0][n][m - 1] * n * n);
      }

      for (int node = 1; node <= n; node++) {
        for (int edge = node - 1; edge <= m; edge++) {
          Mint ways = choose[n][node] * choose[m][edge] * node * node;
          cnt[2][n][m] += ways * cnt[0][node][edge] * cnt[1][n - node][m - edge];
          sum[2][n][m] += ways * sum[0][node][edge] * cnt[1][n - node][m - edge];
          sum[2][n][m] += ways * cnt[0][node][edge] * sum[1][n - node][m - edge];
        }
      }
    }
  }

  vector<vector<vector<Mint>>> c(N + 1, vector<vector<Mint>>(M + 1, vector<Mint>(M + 1)));
  vector<vector<vector<Mint>>> s(N + 1, vector<vector<Mint>>(M + 1, vector<Mint>(M + 1)));

  for (int n = 1; n <= N; n++) {
    for (int m = 0; m <= M; m++) {
      for (int t = 0; t <= M - m; t++) {
        if (t == 0) {
          c[n][m][t] = cnt[0][n][m];
          s[n][m][t] = sum[0][n][m];
        }
        Mint div_2 = Mint(1) / 2;
        for (int node = 1; node < n; node++) {
          for (int edge = 0; edge <= m; edge++) {
            for (int tedg = max(0, node - 1 - edge); tedg < t && n - node - 1 <= m - edge + t - 1 - tedg; tedg++) {
              Mint ways = choose[n][node] * choose[m][edge] * choose[t - 1][tedg] * node * (n - node);
              c[n][m][t] += ways * c[node][edge][tedg] * c[n - node][m - edge][t - 1 - tedg] * div_2;
              s[n][m][t] += ways * c[node][edge][tedg] * s[n - node][m - edge][t - 1 - tedg] * div_2;
              s[n][m][t] += ways * s[node][edge][tedg] * c[n - node][m - edge][t - 1 - tedg] * div_2;
            }
          }
        }
        cnt[3][n][m + t] += c[n][m][t] * choose[m + t][m];
        sum[3][n][m + t] += s[n][m][t] * choose[m + t][m];
      }
    }
  }

  for (int n = 1; n <= N; n++) {
    for (int m = 0; m <= M; m++) {
      for (int node = 1; node <= n; node++) {
        for (int edge = node - 1; edge <= m; edge++) {
          Mint ways = choose[n - 1][node - 1] * choose[m][edge];
          cnt[4][n][m] += ways * cnt[3][node][edge] * cnt[4][n - node][m - edge];
          sum[4][n][m] += ways * cnt[3][node][edge] * sum[4][n - node][m - edge];
          sum[4][n][m] += ways * sum[3][node][edge] * cnt[4][n - node][m - edge];
        }
      }
    }
  }

  return sum[4][N][M] / cnt[4][N][M] + M * A;
}

int main() {
  int N, M, A, B, C;
  cin >> N >> M >> A >> B >> C;
  cout << Solve(N, M, A, B, C) << '\n';
  return 0;
}
