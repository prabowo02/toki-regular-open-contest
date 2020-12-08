/**
 * Author   : rama_pang
 * Problem  : troc-11-fungsi
 * Time     : O(A_max log^2 A_max)
 * Memory   : O(A_max)
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

const int MAX = 100005;

int N, K;
int Freq[MAX];
int Divisor[MAX];
Mint Factorial[MAX];

inline Mint Choose(int n, int k) { // number of ways choosing k items from n items
  return (0 <= k && k <= n) ? Factorial[n] / (Factorial[k] * Factorial[n - k]) : 0;
}

int vis[MAX];
int curIteration = 0;
Mint memo[MAX];

Mint dp(int n, int k) { // number of k tuples having n as their GCD
  Mint &res = memo[n];
  if (vis[n] == curIteration) {
    return res;
  }
  vis[n] = curIteration;
  res = Choose(Divisor[n], k);
  for (int i = n + n; i < MAX; i += n) {
    res -= dp(i, k);
  }
  return res;
}

Mint solve() {
  Mint ans = 0;
  for (int k = 1; k <= K; k++) {
    if (K % k == 0) {
      curIteration++;
      ans += dp(k, K / k);
    }
  }
  return ans;
}

void read() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);

  cin >> N >> K;
  for (int i = 0; i < N; i++) {
    int Ai;
    cin >> Ai;
    Freq[Ai]++;
  }
}

void init() {
  /* Initialize Factorial */
  Factorial[0] = 1;
  for (int i = 1; i < MAX; i++) {
    Factorial[i] = i * Factorial[i - 1];   
  }

  /* Initialize number of Divisors */
  for (int i = 1; i < MAX; i++) {
    for (int j = i; j < MAX; j += i) {
      Divisor[i] += Freq[j];
    }
  }
}

int main() {
  read();
  init();

  cout << solve() << "\n";
  return 0;
}
