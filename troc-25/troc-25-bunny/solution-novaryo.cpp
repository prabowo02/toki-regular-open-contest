#include <bits/stdc++.h>
#define pii pair<int, int>
#define pll pair<long long, long long>
#define L(n) (n << 1)
#define R(n) (n << 1 | 1)
#define print_vector(n) for(auto a0 : n) cout << a0 << ' '; cout << endl;
#define vector_sort(n) sort(n.begin(), n.end())
#define print_array(n, l, r) for(int a0 = l; a0 <= r; a0++) cout << n[a0] << ' '; cout << '\n';
#define REP(i, l, r) for (int i = l; i <= r; i++) 
#define VREP(i, l, r) for (int i = l; i >= r; i--) 
#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)
#define ABS(a) ((a) > 0 ? (a) : -(a))
using namespace std;

template<class T>
istream & operator >> (istream &in, pair<T, T> &p) {
  in >> p.first >> p.second;
  return in;
}

template<class T>
ostream & operator <<(ostream &out, pair<T, T> &p) {
  out << p.first << ' ' << p.second;
  return out;
}

template<class Tuple, std::size_t N>
struct TuplePrinter {
  static void print(ostream &out, const Tuple& t) {
    TuplePrinter<Tuple, N-1>::print(out, t);
    out << ' ' << get<N-1>(t);
  }
};

template<class Tuple>
struct TuplePrinter<Tuple, 1> {
  static void print(ostream &out, const Tuple& t) {
    out << get<0>(t);
  }
};

template<class... Args>
ostream & operator <<(ostream &out, const tuple<Args...> &p) {
  TuplePrinter<decltype(p), sizeof...(Args)>::print(out, p);
  return out;
}

const int MAX_N = 2e5;

int T, M;
long long ans[MAX_N+5];
long long sum[MAX_N+5];
vector<int> primeDivs[MAX_N+5];
vector<int> divs[MAX_N+5];

void precomputePrimeDiv() {
  for (int i = 2; i <= MAX_N; i++) {
    if (primeDivs[i].size() > 0) continue;
    for (int j = i; j <= MAX_N; j += i) {
      primeDivs[j].emplace_back(i);
    }
  }
  for (int i = 2; i <= MAX_N; i++) {
    for (int j = i+i; j <= MAX_N; j += i) {
      divs[j].emplace_back(i);
    }
  }
}

int badDivisor[MAX_N+5];

bool isBadDivisor(int num) {
  if (badDivisor[num] != 0) 
    return badDivisor[num] == 1;

  badDivisor[num] = 1;
  for (int i : primeDivs[num]) {
    if (num % ((long long) i * i) == 0) 
      return true;
  }
  badDivisor[num] = 2;
  return false;
}

void genAns() {
  precomputePrimeDiv();

  ans[1] = 1;
  long long globalSum = 1;
  for (int i = 2; i <= MAX_N; i++) {
    ans[i] = globalSum % M;

    for (int divisor : divs[i]) {
      if (isBadDivisor(divisor)) continue;

      if (primeDivs[divisor].size() & 1) {
        ans[i] = (ans[i] - sum[divisor] + M) % M;
      } else {
        ans[i] = (ans[i] + sum[divisor]) % M;
      }
    }

    for (int divisor : divs[i]) {
      sum[divisor] = (sum[divisor] + ans[i]) % M;
    }
    sum[i] = (sum[i] + ans[i]) % M;

    globalSum = (globalSum + ans[i]) % M;
  }
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin >> T >> M;
  genAns();
  while (T--) {
    int N;
    cin >> N;
    cout << ans[N] << "\n";
  }
}
