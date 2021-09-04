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
    adj[i].emplace_back(P[i]);
    adj[P[i]].emplace_back(i);
  }
  Mint ans = 0;
  for (int mask = 0; mask < (1 << N); mask++) {
    vector<vector<int>> dist(2, vector<int>(N, -1));
    vector<vector<int>> que(2);
    for (int i = 0; i < N; i++) {
      que[(mask >> i) & 1].emplace_back(i);
      dist[(mask >> i) & 1][i] = 0;
    }
    for (int j = 0; j < 2; j++) {
      for (int i = 0; i < int(que[j].size()); i++) {
        int u = que[j][i];
        for (auto v : adj[u]) {
          if (dist[j][v] == -1) {
            dist[j][v] = dist[j][u] + 1;
            que[j].emplace_back(v);
          }
        }
      }
    }
    Mint sum = 0;
    for (int i = 0; i < N; i++) {
      assert(dist[0][i] == 0 || dist[1][i] == 0);
      assert(dist[0][i] != dist[1][i]);
      sum += dist[0][i] + dist[1][i];
    }
    ans += pow(sum, K);
  }
  return ans;
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
