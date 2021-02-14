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

Mint Solve(int N, int M, Mint A, Mint B, Mint C, string arr) {
  vector<vector<Mint>> choose(max(N, M) + 1, vector<Mint>(max(N, M) + 1));
  vector<vector<vector<Mint>>> cnt(min(N, M) + 6, vector<vector<Mint>>(N + 1, vector<Mint>(M + 1)));
  vector<vector<vector<Mint>>> sum(min(N, M) + 6, vector<vector<Mint>>(N + 1, vector<Mint>(M + 1)));

  for (int n = 0; n <= max(N, M); n++) {
    choose[n][0] = 1;
    for (int m = 1; m <= n; m++) {
      choose[n][m] = choose[n - 1][m] + choose[n - 1][m - 1];
    }
  }

  cnt[0][1][0] = 1;
  cnt[4][0][0] = 1;
  cnt[5][0][0] = 1;

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

      for (int node = 1; node <= n; node++) {
        for (int edge = node - 1; edge <= m - 1; edge++) {
          Mint ways = choose[n - 1][node - 1] * choose[m][edge] * node * (m - edge);
          for (int child = 1; child - 1 <= n - node && child - 1 <= m - 1 - edge; child++) {
            cnt[5 + child][n][m] += ways * cnt[3][node][edge] * cnt[5 + child - 1][n - node][m - 1 - edge];
            sum[5 + child][n][m] += ways * cnt[3][node][edge] * sum[5 + child - 1][n - node][m - 1 - edge];
            sum[5 + child][n][m] += ways * sum[3][node][edge] * cnt[5 + child - 1][n - node][m - 1 - edge];
          }
        }
      }

      for (int node = 1; node <= n; node++) {
        for (int edge = node - 1; edge <= m; edge++) {
          Mint ways = choose[n - 1][node - 1] * choose[m][edge];
          for (int child = 0; child <= n - node && child <= m - edge; child++, ways *= node) {
            cnt[3][n][m] += ways * cnt[0][node][edge] * cnt[5 + child][n - node][m - edge];
            sum[3][n][m] += ways * cnt[0][node][edge] * sum[5 + child][n - node][m - edge];
            sum[3][n][m] += ways * sum[0][node][edge] * cnt[5 + child][n - node][m - edge];
          }
        }
      }
    }

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

  for (int n = 1; n <= N; n++) {
    for (int m = 1; m <= M; m++) {
      cout << "  " << arr << "[" << n << "][" << m << "] = " << (sum[4][n][m] / cnt[4][n][m] + m * A) << ";\n";
    }
  }
}

int main() {
  freopen("solution-hardcode.cpp", "w", stdout);

  cout << "#include <bits/stdc++.h>\n";
  cout << "using namespace std;\n\n";
  cout << "int main() {\n";
  cout << "  vector<vector<int>> a(41, vector<int>(41));\n";
  cout << "  vector<vector<int>> b(41, vector<int>(41));\n";
  cout << "  vector<vector<int>> c(41, vector<int>(41));\n";

  Solve(40, 40, 1, 0, 0, "a");
  Solve(40, 40, 0, 1, 0, "b");
  Solve(40, 40, 0, 0, 1, "c");

  cout << "  int N, M, A, B, C, MOD = 998244353;\n";
  cout << "  cin >> N >> M >> A >> B >> C;\n";
  cout << "  cout << (1ll * a[N][M] * A % MOD + 1ll * b[N][M] * B % MOD + 1ll * c[N][M] * C % MOD) % MOD << '\\n';\n";
  cout << "  return 0;\n";
  cout << "}\n";
  return 0;
}
