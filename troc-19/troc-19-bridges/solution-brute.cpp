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

Mint Solve(int N, int M, int A, int B, int C) {
  Mint ans = 0;
  vector<pair<int, int>> edges;

  // cp-algorithms
  vector<int> par, dsu_2ecc, dsu_cc, dsu_cc_size;
  int bridges;
  int lca_iteration;
  vector<int> last_visit;
  vector<int> path_a, path_b;

  const auto init = [&](int n) {
    par.resize(n);
    dsu_2ecc.resize(n);
    dsu_cc.resize(n);
    dsu_cc_size.resize(n);
    lca_iteration = 0;
    last_visit.assign(n, 0);
    for (int i = 0; i < n; i++) {
      dsu_2ecc[i] = i;
      dsu_cc[i] = i;
      dsu_cc_size[i] = 1;
      par[i] = -1;
    }
    bridges = 0;
  };

  const auto find_2ecc = [&](const auto &find_2ecc, int v) {
    if (v == -1) return -1;
    return dsu_2ecc[v] == v ? v : dsu_2ecc[v] = find_2ecc(find_2ecc, dsu_2ecc[v]);
  };

  const auto find_cc = [&](const auto &find_cc, int v) -> int {
    v = find_2ecc(find_2ecc, v);
    return dsu_cc[v] == v ? v : dsu_cc[v] = find_cc(find_cc, dsu_cc[v]);
  };

  const auto make_root = [&](int v) {
    v = find_2ecc(find_2ecc, v);
    int root = v;
    int child = -1;
    while (v != -1) {
      int p = find_2ecc(find_2ecc, par[v]);
      par[v] = child;
      dsu_cc[v] = root;
      child = v;
      v = p;
    }
    dsu_cc_size[root] = dsu_cc_size[child];
  };

  const auto merge_path = [&](int a, int b) {
    ++lca_iteration;
    path_a.clear(), path_b.clear();
    int lca = -1;
    while (lca == -1) {
      if (a != -1) {
        a = find_2ecc(find_2ecc, a);
        path_a.push_back(a);
        if (last_visit[a] == lca_iteration) {
          lca = a;
          break;
        }
        last_visit[a] = lca_iteration;
        a = par[a];
      }
      if (b != -1) {
        b = find_2ecc(find_2ecc, b);
        path_b.push_back(b);
        if (last_visit[b] == lca_iteration) {
          lca = b;
          break;
        }
        last_visit[b] = lca_iteration;
        b = par[b];
      }
    }
    for (int v : path_a) {
      dsu_2ecc[v] = lca;
      if (v == lca) break;
      --bridges;
    }
    for (int v : path_b) {
      dsu_2ecc[v] = lca;
      if (v == lca) break;
      --bridges;
    }
  };

  const auto add_edge = [&](int a, int b) {
    a = find_2ecc(find_2ecc, a);
    b = find_2ecc(find_2ecc, b);
    if (a == b) return;

    int ca = find_cc(find_cc, a);
    int cb = find_cc(find_cc, b);

    if (ca != cb) {
      ++bridges;
      if (dsu_cc_size[ca] > dsu_cc_size[cb]) {
        swap(a, b);
        swap(ca, cb);
      }
      make_root(a);
      par[a] = dsu_cc[a] = b;
      dsu_cc_size[cb] += dsu_cc_size[a];
    } else {
      merge_path(a, b);
    }
  };

  const auto Brute = [&](const auto &Brute) {
    if (edges.size() == M) {
      init(N);
      Mint cur = 0;
      for (auto [u, v] : edges) {
        int x = bridges;
        add_edge(u, v);
        int y = bridges;
        if (x < y) {
          cur += A;
        } else if (x == y) {
          cur += B;
        } else if (x > y) {
          cur += C;
        }
      }
      ans += cur;
      return;
    }
    for (int i = 0; i < N; i++) {
      for (int j = i; j < N; j++) {
        edges.emplace_back(i, j);
        Brute(Brute);
        edges.pop_back();
      }
    }
  };

  Brute(Brute);
  return ans / pow(Mint(N * (N + 1) / 2), M);
}

int main() {
  int N, M, A, B, C;
  cin >> N >> M >> A >> B >> C;
  cout << Solve(N, M, A, B, C) << '\n';
  return 0;
}
