#include <bits/stdc++.h>
using namespace std;

namespace algebra {

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
const int PRIMITIVE_ROOT = 3;

using Mint = ModInt<MOD>;
using Poly = vector<Mint>;

void fft(Poly &a, const vector<Mint> &roots, const bool inv = false) {
  int n = (int) a.size();
  for (int i = 1, j = 0; i < n; i++) {
    int bit = n / 2; for (; j & bit; bit /= 2) j ^= bit; j ^= bit;
    if (i < j) swap(a[i], a[j]);
  }
  for (int len = 1; len < n; len *= 2) {
    for (int i = 0; i < n; i += 2 * len) for (int j = 0; j < len; j++) {
      Mint u = a[i + j];
      Mint v = a[i + j + len] * roots[n / 2 / len * j];
      a[i + j] = u + v;
      a[i + j + len] = u - v;
    }
  }
  if (inv) {
    Mint d = Mint(1) / Mint(n);
    for (auto &i : a) i *= d;
  }
}

Poly operator*(Poly a, Poly b) {
  if (a.empty() || b.empty()) return {};
  int sz = a.size() + b.size() - 1;
  int n = 1; while (n < sz) n *= 2;

  vector<Mint> roots(n);
  roots[0] = 1, roots[1] = pow(Mint(PRIMITIVE_ROOT), (MOD - 1) / n);
  for (int i = 2; i < n; i++) {
    roots[i] = roots[i / 2] * roots[i / 2] * roots[i & 1];
  }

  a.resize(n); fft(a, roots);
  b.resize(n); fft(b, roots);
  for (int i = 0; i < n; i++) a[i] *= b[i];
  for (int i = 1; 2 * i < n; i++) swap(roots[i], roots[n - i]);
  fft(a, roots, 1); a.resize(sz); return a;
}

}

int Solve(int N) { // O(N log^2 N)
  using namespace algebra;

  vector<Mint> inv2(N + 1);
  inv2[0] = 1, inv2[1] = (MOD + 1) / 2;
  for (int i = 2; i <= N; i++) {
    inv2[i] = inv2[i - 1] * inv2[1];
  }

  vector<Mint> fact(N + 1);
  fact[0] = 1;
  for (int i = 1; i <= N; i++) {
    fact[i] = i * fact[i - 1];
  }

  vector<Mint> cat(N + 1);
  for (int i = 0; 2 * i <= N; i++) {
    cat[i] = fact[i + i] / fact[i] / fact[i] / (i + 1);
  }

  vector<Mint> cnt(N + 1);
  vector<Mint> noPrefix(N + 1);
  vector<Mint> f(N + 1);

  const auto DnC = [&](const auto &self, int L, int R) {
    if (L == R) {
      f[L] += noPrefix[L];
      if (L == 0) {
        cnt[L] += 1;
      } else {
        f[L] += (f[L - 1] + 1) * inv2[1];
      }
      return;
    }

    int M = (L + R) / 2;
    self(self, L, M);

    { // cnt[len] += cat[i] * inv2[i + i + 1] * cnt[len - i - i - 1];
      vector<Mint> g(R - L + 2);
      for (int i = 1; i < (R - L + 2); i += 2) {
        g[i] = cat[(i - 1) / 2] * inv2[i];
      }
      vector<Mint> h(M - L + 2);
      for (int i = L; i <= M; i++) {
        h[i - L] = cnt[i];
      }
      vector<Mint> res = g * h;
      for (int i = M + 1; i <= R; i++) {
        cnt[i] += res[i - L];
      }
    }

    { // noPrefix[len] += cat[i] * inv2[i + i + 1] * noPrefix[len - i - i - 1];
      vector<Mint> g(R - L + 2);
      for (int i = 1; i < (R - L + 2); i += 2) {
        g[i] = cat[(i - 1) / 2] * inv2[i];
      }
      vector<Mint> h(M - L + 2);
      for (int i = L; i <= M; i++) {
        h[i - L] = noPrefix[i];
      }
      vector<Mint> res = g * h;
      for (int i = M + 1; i <= R; i++) {
        noPrefix[i] += res[i - L];
      }
    }

    { // noPrefix[len] += cat[i] * (i + 1) * inv2[i + i + 1] * cnt[len - i - i - 1];
      vector<Mint> g(R - L + 2);
      for (int i = 1; i < (R - L + 2); i += 2) {
        g[i] = cat[(i - 1) / 2] * ((i + 1) / 2) * inv2[i];
      }
      vector<Mint> h(M - L + 2);
      for (int i = L; i <= M; i++) {
        h[i - L] = cnt[i];
      }
      vector<Mint> res = g * h;
      for (int i = M + 1; i <= R; i++) {
        noPrefix[i] += res[i - L];
      }
    }

    { // f[len] += cat[i - 1] * inv2[i + i] * f[len - i - i];
      vector<Mint> g(R - L + 2);
      for (int i = 2; i < (R - L + 2); i += 2) {
        g[i] = cat[(i - 2) / 2] * inv2[i];
      }
      vector<Mint> h(M - L + 2);
      for (int i = L; i <= M; i++) {
        h[i - L] = f[i];
      }
      vector<Mint> res = g * h;
      for (int i = M + 1; i <= R; i++) {
        f[i] += res[i - L];
      }
    }

    { // f[len] += cat[i - 1] * i * inv2[i + i];
      vector<Mint> g(R - L + 2);
      for (int i = 2; i < (R - L + 2); i += 2) {
        g[i] = cat[(i - 2) / 2] * (i / 2) * inv2[i];
      }
      vector<Mint> h(M - L + 2);
      for (int i = L; i <= M; i++) {
        h[i - L] = 1;
      }
      vector<Mint> res = g * h;
      for (int i = M + 1; i <= R; i++) {
        f[i] += res[i - L];
      }
    }

    return self(self, M + 1, R);
  };

  DnC(DnC, 0, N);
  return (N - f[N]).v;
}

int main() {
  int N;
  cin >> N;

  cout << Solve(N) << '\n';
  return 0;
}
