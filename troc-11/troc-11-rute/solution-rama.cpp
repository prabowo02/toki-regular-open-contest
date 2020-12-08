/**
 * Author   : rama_pang
 * Problem  : troc-11-rute
 * Time     : O(N^2)
 * Memory   : O(N)
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


struct Node {
  int s, t, sz;
  vector<Mint> DP; // DP Connected Components on Tree

  Node() : s(0), t(0), sz(0) { DP.assign(1, 0); DP[0] = 1; }

  Mint& operator[](int i) { return DP[i]; }
  const Mint& operator[](int i) const { return DP[i]; }

  friend Node merge(const Node &a, const Node &b) { // merge DP states from children of nodes
    Node res;

    res.s = a.s + b.s;              // check if current node has already processed S
    res.t = a.t + b.t;              // check if current node has already processed T
    res.sz = a.sz + b.sz;           // size of current subtree
    res.DP.assign(res.sz + 1, 0);   // merged DP table

    for (int i = 0; i <= a.sz; i++) {
      for (int j = 0; j <= b.sz; j++) {
        res[i + j] += a[i] * b[j];
      }
    }

    return res;
  }

  void calc(int type) { // process current node
    sz++;
    vector<Mint> nextDP(sz + 1, 0);
    if (type == 0) { // current node is not S nor T
      for (int comp = 0; comp < sz; comp++) {
        nextDP[comp + 1] += DP[comp]; // add new component
        if (comp - 1 >= 0) {
          nextDP[comp - 1] += DP[comp] * comp * (comp - 1);   // merge two components
          nextDP[comp - 1] += DP[comp] * comp * s;            // merge with left end
          nextDP[comp - 1] += DP[comp] * comp * t;            // merge with right end
        }
        nextDP[comp] += DP[comp] * comp;    // append to front of an existing component
        nextDP[comp] += DP[comp] * comp;    // append to back of an existing component
        nextDP[comp] += DP[comp] * s;       // append to left end
        nextDP[comp] += DP[comp] * t;       // append to right end
      }
    } else if (type == 1) { // current node is S or T
      for (int comp = 0; comp < sz; comp++) {
        nextDP[comp] += DP[comp]; // add new component
        if (comp - 1 >= 0) {
          nextDP[comp - 1] += DP[comp] * comp; // append to front (if S) or end (if T) of an existing component
        }
      }
    }

    DP = nextDP;
    return;
  }

  void clear() { // Flying Table Optimization, as only O(N) DP elements can be alive at one moment
    s = t = sz = 0;
    vector<Mint>().swap(DP);
  }

};

int N, S, T;
vector<int> P;      // parent array
vector<Node> tree;  // solver, bottom up approach from the leaf

void read() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);

  cin >> N;
  
  P.assign(N, -1); // parent array
  tree.resize(N);

  for (int i = 1; i < N; i++) {
    cin >> P[i];
    P[i]--;
  }
  
  cin >> S >> T;
  S--, T--;
}

Mint solve() {
  tree[S].s = 1;
  tree[T].t = 1;

  for (int i = N - 1; i >= 1; i--) {
    if (i != S && i != T) {
      tree[i].calc(0); // current node is not S nor T
    } else {
      tree[i].calc(1); // current node is S or T
    }
    tree[P[i]] = merge(tree[P[i]], tree[i]);
    tree[i].clear();
  }

  return tree[0][0];
} 

int main() {
  read();
  cout << solve() << "\n";
  return 0;
}
