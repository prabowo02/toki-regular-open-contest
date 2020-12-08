/**
 * Author   : rama_pang
 * Problem  : troc-11-ring
 * Time     : O(9^3 log^2 N)
 * Memory   : O(9^2)
**/

#include <bits/stdc++.h>
using namespace std;

template<typename T>
T inverse(T a, T m) {
  T x = 0, y = 1;
  while (a != 0) {
    T q = m / a;
    m -= q * a; swap(a, m);
    x -= q * y; swap(x, y);
  }
  assert(m == 1);
  return x;
}

template<typename T>
class Modular {
  
 private:

  using Type = typename decay<decltype(T::value)>::type;
  Type value;

 public:

  Modular() { value = 0; }

  template <typename U>
  Modular(const U& x) { value = normalize(x); }

  template<typename U>
  Type normalize(const U& x) {
    Type res;
    if (-mod() <= x && x < mod()) {
      res = static_cast<Type>(x);
    } else {
      res = static_cast<Type>(x % mod());
    }
    if (res < 0) {
      res += mod();
    }
    return res;
  }

  explicit operator Type() const { return value; }
  template <typename U> explicit operator U() const { return static_cast<U>(value); }
  constexpr static Type mod() { return T::value; }

  Modular& operator+=(const Modular& o) { if ((value += o.value) >= mod()) value -= mod(); return *this; }
  template <typename U> Modular& operator+=(const U& o) { return *this += Modular(o); }

  Modular& operator-=(const Modular& o) { if ((value -= o.value) < 0) value += mod(); return *this; }
  template <typename U> Modular& operator-=(const U& o) { return *this -= Modular(o); }

  Modular& operator*=(const Modular& o) { value = normalize(1ll * value * o.value); return *this; }
  template <typename U> Modular& operator*=(const U& o) { return *this *= Modular(o); }

  Modular& operator/=(const Modular &o) { return *this *= Modular(inverse(o.value, mod())); }
  template <typename U> Modular& operator/=(const U& o) { return *this /= Modular(o); }
  
  Modular operator+() { return Modular(+value); }
  Modular operator-() { return Modular(-value); }

  Modular& operator++() { return *this += 1; }
  Modular& operator--() { return *this -= 1; }

  friend ostream& operator<<(ostream &os, const Modular &x) { os << x.value; return os; }
  friend istream& operator>>(istream &is, Modular &x) { 
    typename common_type<Type, int64_t>::type in;
    is >> in; 
    x.value = x.normalize(in);
    return is; 
  }

  friend bool operator==(const Modular& a, const Modular& b) { return a.value == b.value; }
  template<typename U> friend bool operator==(const Modular &a, U b) { return a == Modular(b); }
  template<typename U> friend bool operator==(U a, const Modular &b) { return Modular(a) == b; }

  friend bool operator!=(const Modular& a, const Modular& b) { return a.value != b.value; }
  template<typename U> friend bool operator!=(const Modular &a, U b) { return a != Modular(b); }
  template<typename U> friend bool operator!=(U a, const Modular &b) { return Modular(a) != b; }
  
  friend bool operator>(const Modular& a, const Modular& b) { return a.value > b.value; }
  template<typename U> friend bool operator>(const Modular &a, U b) { return a > Modular(b); }
  template<typename U> friend bool operator>(U a, const Modular &b) { return Modular(a) > b; }

  friend bool operator<(const Modular& a, const Modular& b) { return a.value < b.value; }
  template<typename U> friend bool operator<(const Modular &a, U b) { return a < Modular(b); }
  template<typename U> friend bool operator<(U a, const Modular &b) { return Modular(a) < b; }

  friend bool operator>=(const Modular& a, const Modular& b) { return a.value >= b.value; }
  template<typename U> friend bool operator>=(const Modular &a, U b) { return a >= Modular(b); }
  template<typename U> friend bool operator>=(U a, const Modular &b) { return Modular(a) <= b; }

  friend bool operator<=(const Modular& a, const Modular& b) { return a.value <= b.value; }
  template<typename U> friend bool operator<=(const Modular &a, U b) { return a <= Modular(b); }
  template<typename U> friend bool operator<=(U a, const Modular &b) { return Modular(a) <= b; }
  
  friend Modular operator+(const Modular &a, const Modular& b) { return Modular(a) += b; }
  template <typename U> friend Modular operator+(const Modular &a, const U& b) { return Modular(a) += Modular(b); }
  template <typename U> friend Modular operator+(const U& a, const Modular &b) { return Modular(a) += b; }

  friend Modular operator-(const Modular &a, const Modular& b) { return Modular(a) -= b; }
  template <typename U> friend Modular operator-(const Modular &a, const U& b) { return Modular(a) -= Modular(b); }
  template <typename U> friend Modular operator-(const U& a, const Modular &b) { return Modular(a) -= b; }
  
  friend Modular operator*(const Modular &a, const Modular& b) { return Modular(a) *= b; }
  template <typename U> friend Modular operator*(const Modular &a, const U& b) { return Modular(a) *= Modular(b); }
  template <typename U> friend Modular operator*(const U& a, const Modular &b) { return Modular(a) *= b; }
    
  friend Modular operator/(const Modular &a, const Modular& b) { return Modular(a) /= b; }
  template <typename U> friend Modular operator/(const Modular &a, const U& b) { return Modular(a) /= Modular(b); }
  template <typename U> friend Modular operator/(const U& a, const Modular &b) { return Modular(a) /= b; }
  
};

constexpr int MOD = 1e9 + 7;
using Mint = Modular<integral_constant<decay<decltype(MOD)>::type, MOD>>;

using lint = long long;

template<typename T>
struct Matrix {
  int n, m;
  vector<vector<T>> M;

  vector<T>& operator[](int i) { return M[i]; }

  const vector<T>& operator[](int i) const { return M[i]; }
  
  Matrix() {}
  
  Matrix(int n, int m) : n(n), m(m) {
    M.assign(n, vector<T>(m, 0));
  }

  Matrix operator*(Matrix o) {
    assert(m == (int) o.M.size());

    Matrix res(n, (int) o[0].size());
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < (int) o[0].size(); j++) {
        for (int k = 0; k < m; k++) {
          res[i][j] += M[i][k] * o[k][j];
        }
      }
    }
    return res;
  }

  Matrix operator+(Matrix o) {
    assert(n == o.n);
    assert(m == o.m);

    Matrix res(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        res[i][j] = M[i][j] + o[i][j];
      }
    }
    return res;
  }

  Matrix operator-(Matrix o) {
    assert(n == o.n);
    assert(m == o.m);

    Matrix res(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        res[i][j] = M[i][j] - o[i][j];
      }
    }
    return res;
  }
  

};


//////// UNUSED
namespace unused_dp_misc { // see original DP transitions here, before being reduced to matrix exponentiation
  lint L, R, K, Rem, Mod;

  namespace DP_old { // states before reduction states of DP
    Mint memo_old[100][2][2][2][2];
    bool vis_old[100][2][2][2][2];

    Mint dp_old(lint n, bool f1b1, bool f1b2, bool f2b1, bool f2b2) { // f1 f2 ... b1 b2
      if (n <= 0) {
        return (n < 0 || f1b1 || f2b1 || f2b2) ? 0 : 1;
      }
      if (vis_old[n][f1b1][f1b2][f2b1][f2b2]) {
        return memo_old[n][f1b1][f1b2][f2b1][f2b2];
      }
      vis_old[n][f1b1][f1b2][f2b1][f2b2] = true;
      Mint& res = memo_old[n][f1b1][f1b2][f2b1][f2b2] = 0;

      if (f1b1 && f2b2) {
        res += dp_old(n - 1, f2b1, f2b2, false, false) * (K - 2);   // 123...12
      } else if (f1b2 && f2b1) {
        res += dp_old(n - 1, f2b1, f2b2, false, false) * (K - 2);   // 123...21
      } else if (f1b1) {
        res += dp_old(n - 1, f2b1, f2b2, false, false) * (K - 3);   // 124...13
        res += dp_old(n - 1, f2b1, f2b2, false, true);              // 123...13
      } else if (f1b2) {
        res += dp_old(n - 1, f2b1, f2b2, false, false) * (K - 3);   // 124...31
        res += dp_old(n - 1, f2b1, f2b2, true, false);              // 123...31
      } else if (f2b1) {
        res += dp_old(n - 1, f2b1, f2b2, false, false) * (K - 3);   // 124...23
        res += dp_old(n - 1, f2b1, f2b2, false, true);              // 123...23
      } else if (f2b2) {
        res += dp_old(n - 1, f2b1, f2b2, false, false) * (K - 3);   // 124...32
        res += dp_old(n - 1, f2b1, f2b2, true, false);              // 123...32
      } else {
        res += dp_old(n - 1, f2b1, f2b2, false, false) * (K - 4);   // 125...34
        res += dp_old(n - 1, f2b1, f2b2, true, false);              // 123...34
        res += dp_old(n - 1, f2b1, f2b2, false, true);              // 124...34
      }
      
      return res;
    }

    Mint calc_old(lint n) {
      return dp_old(n - 2, true, false, false, true) * K * (K - 1);
    }

  }

  namespace DP { // DP recurrence form, basis for matrix exponentiation DP. Reduced state from previous DP.
    Mint memo[100][3][3];
    bool vis[100][3][3];

    Mint dp(lint n, int f1, int f2) {
      if (n <= 0) {
        return (n < 0 || f1 == 1 || f2 != 0) ? 0 : 1;
      }
      if (vis[n][f1][f2]) {
        return memo[n][f1][f2];
      }

      vis[n][f1][f2] = true;
      Mint& res = memo[n][f1][f2] = 0;
      if ((f1 == 1 && f2 == 2) || (f1 == 2 && f2 == 1)) {
        res += dp(n - 1, f2, 0) * (K - 2);
      } else if (f1 == 1 || f2 == 1) {
        res += dp(n - 1, f2, 0) * (K - 3);
        res += dp(n - 1, f2, 2);
      } else if (f1 == 2 || f2 == 2) {
        res += dp(n - 1, f2, 0) * (K - 3);
        res += dp(n - 1, f2, 1);
      } else {
        res += dp(n - 1, f2, 0) * (K - 4);
        res += dp(n - 1, f2, 1);
        res += dp(n - 1, f2, 2);
      }
      return res;
    }

    Mint calc(lint n) {
      return dp(n - 2, 1, 2) * K * (K - 1);
    }

  }

}
//////// UNUSED



lint L, R, K, Rem, Mod;

Matrix<Mint> Base;          // Base Case for DP
Matrix<Mint> Transition;    // Transition for DP
Matrix<Mint> Identity;      // Identity Matrix
Matrix<Mint> Zero;          // Zero Matrix

Matrix<Mint> power(Matrix<Mint> a, lint x) {
  if (x == 0) {
    return Identity;
  }
  if (x & 1) {
    return a * power(a, x - 1);
  }
  Matrix<Mint> res = power(a, x / 2);
  return res * res;
}

inline int name(int _f1, int _f2) {
  return _f1 * 3 + _f2;
}

void read() {
  cin >> K >> L >> R >> Rem >> Mod;
  
  lint dec;
  
  dec = ((R % Mod) - Rem + Mod) % Mod;
  R -= dec;
  
  dec = (Rem - (L % Mod) + Mod) % Mod;
  L += dec;
  
  while (L <= 2) {
    L += Mod;
  }

  if (K <= 2 || R <= 2 || L > R) {
    cout << 0 << "\n";
    exit(0);
  }
}

void initializeMatrix() { // initialize Base, Transition, Identity, and Zero Matrix
  Base        = Matrix<Mint>(9, 1);
  Transition  = Matrix<Mint>(9, 9);
  Identity    = Matrix<Mint>(9, 9);
  Zero        = Matrix<Mint>(9, 9);

  Base[name(1, 2)][0] = 1;

  for (int i = 0; i < 9; i++) {
    Identity[i][i] = 1;
  }

  for (int f1 = 0; f1 < 3; f1++) { // can still be optimized, as there are only 6 reachable states
    for (int f2 = 0; f2 < 3; f2++) {
      if ((f1 == 1 && f2 == 2) || (f1 == 2 && f2 == 1)) {
        Transition[name(f2, 0)][name(f1, f2)] += K - 2;
      } else if (f1 == 1 || f2 == 1) {
        Transition[name(f2, 0)][name(f1, f2)] += K - 3;
        Transition[name(f2, 2)][name(f1, f2)] += 1;
      } else if (f1 == 2 || f2 == 2) {
        Transition[name(f2, 0)][name(f1, f2)] += K - 3;
        Transition[name(f2, 1)][name(f1, f2)] += 1;
      } else {
        Transition[name(f2, 0)][name(f1, f2)] += K - 4;
        Transition[name(f2, 1)][name(f1, f2)] += 1;
        Transition[name(f2, 2)][name(f1, f2)] += 1;
      }
    }
  }
}

Matrix<Mint> calc(lint n) { // Find dp(n) using matrix exponentiation in
  Matrix<Mint> res = power(Transition, n - 2) * Base;
  return res;
}

Matrix<Mint> geometric(Matrix<Mint> r, lint n) { // Geometric series on matrices using divide and conquer
  // Geometric Series of form 1 + r + r^2 + ...
  // 1 + r + r^2 + r^(n - 1)

  if (n == 0) {
    return Identity;
  }

  Matrix<Mint> res;
  if (n % 2 == 0) {
    return power(r, n) + geometric(r, n - 1);
  }

  Matrix<Mint> tmp = geometric(r, n / 2);
  return tmp * power(r, (n + 1) / 2) + tmp;
}

Mint solve() {
  lint num = (R - L + Mod) / Mod;

  // a + ar + .. + ar^(num - 1) -> Find sum of geometric series using Divide and Conquer Approach
  Matrix<Mint> a = calc(L);
  Matrix<Mint> r = power(Transition, Mod);
  Matrix<Mint> res = geometric(r, num - 1) * a;

  Mint ans = 0;
  ans = (res[name(0, 0)][0] + res[name(2, 0)][0]) * K * (K - 1);

  return ans;
}

int main() {
  read();
  initializeMatrix();

  Mint ans = solve();
  cout << ans << "\n";
  
  return 0;
}
