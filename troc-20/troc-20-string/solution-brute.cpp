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

Poly operator+(Poly a, Poly b) {
  if (a.size() < b.size()) swap(a, b);
  for (int i = 0; i < b.size(); i++) a[i] += b[i];
  return a;
}

Poly operator-(Poly a, Poly b) {
  if (a.size() < b.size()) a.resize(b.size());
  for (int i = 0; i < b.size(); i++) a[i] -= b[i];
  return a;
}

Poly operator-(Mint a, Poly b) {
  return Poly({a}) - b;
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

Poly operator*(Poly a, Mint b) {
  return a * Poly({b});
}

Poly inverse(int n, Poly a) {
  assert(!a.empty());
  a.resize(2 * n);
  Poly b = {Mint(1) / a[0]};
  for (int i = 1; i < n; i *= 2) {
    Poly c = b * b * Poly(begin(a), begin(a) + 2 * i);
    b.resize(2 * i);
    for (int j = 0; j < 2 * i; j++) {
      b[j] = 2 * b[j] - c[j];
    }
  }
  b.resize(n);
  return b;
}

Poly square(Poly a) {
  return a * a;
}

}

namespace validator {

using namespace algebra;

Mint SolveBruteForce(int N, vector<Mint> A, vector<Mint> B) {
  for (int i = 0; i < N; i++) {
    tie(A[i], B[i]) = pair(A[i] / (A[i] + B[i]), B[i] / (A[i] + B[i]));
  }

  Mint ans = 0;

  const auto CountDP = [&](string s) {
    vector<int> dp0(N + 1), dp1(N + 1);
    for (int i = 0; i < N; i++) {
      if (s[i] == '0') {
        dp0[i + 1] = max(dp0[i + 1], dp0[i] + 1);
        dp1[i + 1] = max(dp1[i + 1], dp0[i] + 1);
        dp1[i + 1] = max(dp1[i + 1], dp1[i] + 0);
      } else if (s[i] == '1') {
        dp0[i + 1] = max(dp0[i + 1], dp0[i] + 0);
        dp1[i + 1] = max(dp1[i + 1], dp0[i] + 1);
        dp1[i + 1] = max(dp1[i + 1], dp1[i] + 1);
      } else {
        assert(false);
      }
    }
    return dp1[N];
  };

  const auto CountGreedy = [&](string s) {
    int res = 0;
    int cnt0 = 0;
    int cnt1 = 0;
    for (int i = 0; i < N; i++) {
      cnt0 += s[i] == '0';
      cnt1 += s[i] == '1';
      if (cnt0 >= cnt1) {
        res += cnt0;
        cnt0 = 0;
        cnt1 = 0;
      }
    }
    res += cnt1;
    return res;
  };

  const auto Count2 = [&](string s) {
    int res = 0;
    vector<int> pref(N);
    vector<int> suff(N);
    for (int i = 0; i < N; i++) {
      pref[i] = s[i] == '0';
      suff[i] = s[i] == '1';
    }
    for (int i = 1; i < N; i++) {
      pref[i] += pref[i - 1];
    }
    for (int i = int(N) - 2; i >= 0; i--) {
      suff[i] += suff[i + 1];
    }
    for (int i = -1; i < (int) N; i++) {
      res = max(res, (i == -1 ? 0 : pref[i]) + (i + 1 == N ? 0 : suff[i + 1]));
    }
    return res;
  };

  string S(N, '?');
  const auto Dfs = [&](const auto &self, int n, Mint probability) {
    if (n == N) {
      int x = CountDP(S);
      int y = CountGreedy(S);
      int z = Count2(S);
      if (x != y || x != z || y != z) cout << S << ' ' << x << ' ' << y << ' ' << z << endl;
      assert(x == y && y == z);
      ans += probability * x;
      return;
    }
    S[n] = '0';
    self(self, n + 1, probability * A[n]);
    S[n] = '1';
    self(self, n + 1, probability * B[n]);
    S[n] = '?';
  };

  Dfs(Dfs, 0, 1);
  return N - ans;
}

Mint SolveDynamicProgrammingConstantAB(int N, Mint A, Mint B) {
  tie(A, B) = pair(A / (A + B), B / (A + B));

  vector<Mint> fact(N + 1);
  fact[0] = 1;
  for (int i = 1; i <= N; i++) {
    fact[i] = i * fact[i - 1];
  }

  vector<Mint> cat(N + 1);
  for (int i = 0; 2 * i <= N; i++) {
    cat[i] = fact[i + i] / fact[i] / fact[i] / (i + 1);
  }

  vector<Mint> pwA(N + 1);
  vector<Mint> pwB(N + 1);
  pwA[0] = pwB[0] = 1;
  for (int i = 1; i <= N; i++) {
    pwA[i] = A * pwA[i - 1];
    pwB[i] = B * pwB[i - 1];
  }

  vector<Mint> cnt(N + 1);
  cnt[0] = 1;
  for (int len = 1; len <= N; len++) {
    for (int i = 0; 2 * i <= len - 1; i++) {
      cnt[len] += cat[i] * cnt[len - 1 - 2 * i] * pwA[i] * pwB[i + 1];
    }
  }

  vector<Mint> noPrefix(N + 1);
  for (int len = 1; len <= N; len++) {
    for (int i = 0; 2 * i <= len - 1; i++) {
      noPrefix[len] += cat[i] * noPrefix[len - 1 - 2 * i] * pwA[i] * pwB[i + 1];
      noPrefix[len] += cat[i] * (i + 1) * cnt[len - 1 - 2 * i] * pwA[i] * pwB[i + 1];
    }
  }

  vector<Mint> f(N + 1);
  for (int len = 1; len <= N; len++) {
    // Case 1: first element is 0
    f[len] += (f[len - 1] + 1) * pwA[1];
    // Case 2: Iterate shortest prefix where cnt[0] == cnt[1]
    for (int i = 1; i <= len / 2; i++) {
      f[len] += f[len - 2 * i] * cat[i - 1] * pwA[i] * pwB[i];
      f[len] += i * cat[i - 1] * pwA[i] * pwB[i];
    }
    // Case 3: No prefix where cnt[0] == cnt[1] exist
    f[len] += noPrefix[len];
  }

  return N - f[N];
}

}

namespace solution {

using namespace algebra;

Mint SolveDynamicProgramming(int N, vector<Mint> A, vector<Mint> B) {
  for (int i = 0; i < N; i++) {
    tie(A[i], B[i]) = pair(A[i] / (A[i] + B[i]), B[i] / (A[i] + B[i]));
  }

  vector<vector<vector<Mint>>> cnt(2, vector<vector<Mint>>(2, vector<Mint>(N + 2)));
  vector<vector<vector<Mint>>> sum(2, vector<vector<Mint>>(2, vector<Mint>(N + 2)));

  for (int i = N; i >= 0; i--, swap(cnt[0], cnt[1]), swap(sum[0], sum[1])) {
    for (int bal = 0; bal <= N; bal++) {
      cnt[1][0][bal] = cnt[1][1][bal] = 0;
      sum[1][0][bal] = sum[1][1][bal] = 0;
      if (i == N) {
        cnt[1][0][bal] += bal == 0;
        cnt[1][1][bal] += bal >= 1;
      } else {
        // Place 0
        cnt[1][0][bal] += (bal >= 0) * A[i] * cnt[0][0][max(bal - 1, 0)];
        sum[1][0][bal] += (bal >= 0) * A[i] * cnt[0][0][max(bal - 1, 0)];
        sum[1][0][bal] += (bal >= 0) * A[i] * sum[0][0][max(bal - 1, 0)];

        cnt[1][1][bal] += (bal >= 2) * A[i] * cnt[0][1][max(bal - 1, 0)];
        sum[1][1][bal] += (bal >= 2) * A[i] * sum[0][1][max(bal - 1, 0)];

        // Place 1
        cnt[1][0][bal] += (bal >= 0) * B[i] * cnt[0][0][bal + 1];
        sum[1][0][bal] += (bal >= 0) * B[i] * sum[0][0][bal + 1];

        cnt[1][0][bal] += (bal == 0) * B[i] * cnt[0][1][bal + 1];
        sum[1][0][bal] += (bal == 0) * B[i] * cnt[0][1][bal + 1];
        sum[1][0][bal] += (bal == 0) * B[i] * sum[0][1][bal + 1];

        cnt[1][1][bal] += (bal >= 0) * B[i] * cnt[0][1][bal + 1];
        sum[1][1][bal] += (bal >= 0) * B[i] * cnt[0][1][bal + 1];
        sum[1][1][bal] += (bal >= 0) * B[i] * sum[0][1][bal + 1];
      }
    }
  }

  assert(cnt[0][0][0] == 1);
  return N - sum[0][0][0];
}

Mint SolveGeneratingFunction(int N, Mint A, Mint B) {
  tie(A, B) = pair(A / (A + B), B / (A + B));

  vector<Mint> factorial(N + 1);
  factorial[0] = 1;
  for (int i = 1; i <= N; i++) {
    factorial[i] = i * factorial[i - 1];
  }

  vector<Mint> C(N + 1), D(N + 1);
  for (int i = 0; i <= N; i += 2) {
    Mint catalan = factorial[i] / factorial[i / 2] / factorial[i / 2] / (i / 2 + 1);
    C[i] = catalan * pow(A, i / 2) * pow(B, i / 2 + 1);
    D[i] = catalan * pow(A, i / 2) * pow(B, i / 2 + 1) * (i / 2 + 1);
  }

  vector<Mint> numF = (Poly({0, +A}) + Poly({0, 0, A}) * D) * square(1 - Poly({0, 1}) * C) + Poly({0, 1, -1}) * D;
  vector<Mint> denF = (Poly({1, -A}) - Poly({0, 0, A}) * C) * square(1 - Poly({0, 1}) * C) * Poly({1, -1, 0}) * 1;

  return N - (numF * inverse(N + 1, denF))[N];
}

}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N;
  cin >> N;

  string S;
  cin >> S;

  vector<algebra::Mint> A(N);
  vector<algebra::Mint> B(N);
  for (int i = 0; i < N; i++) {
    A[i] = (S[i] != '1');
    B[i] = (S[i] != '0');
  }

  cout << validator::SolveBruteForce(N, A, B) << '\n';
  return 0;
}
