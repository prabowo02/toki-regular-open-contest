#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int MOD = 998244353;

using Poly = vector<int>;

int n;

int fact[N], ifact[N];
int catalan[N];

int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }
  return ret;
}

namespace FFT {

const int LN = 21;
const int N = 1 << LN;
const int PRIMITIVE_ROOT = 3;

int root[N];

void init_fft() {
  const int UNITY = power(PRIMITIVE_ROOT, (MOD-1) >> LN);
  root[0] = 1;
  for (int i = 1; i < N; ++i) {
    root[i] = 1LL * UNITY * root[i-1] % MOD;
  }
}

// n is the length of polynom
void fft(int n, vector<int> &a, bool invert) {
  for (int i = 1, j = 0; i < n; ++i) {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1) j ^= bit;
    j ^= bit;
    if (i < j) swap(a[i], a[j]);
  }

  for (int len = 2; len <= n; len <<= 1) {
    int wlen = (invert ? root[N - N/len] : root[N/len]);
    for (int i = 0; i < n; i += len) {
      int w = 1;
      for (int j = 0; j < len>>1; ++j) {
        int u = a[i+j];
        int v = 1LL * a[i+j + len/2] * w % MOD;

        a[i+j] = (u + v) % MOD;
        a[i+j + len/2] = (u - v + MOD) % MOD;

        w = 1LL * w * wlen % MOD;
      }
    }
  }

  if (invert) {
    int inv = power(n, MOD-2);
    for (int i = 0; i < n; ++i) a[i] = 1LL * a[i] * inv % MOD;
  }
}

} // namespace FFT

Poly operator + (Poly a, Poly b) {
  if (a.size() < b.size()) swap(a, b);
  for (int i = 0; i < b.size(); ++i) a[i] = (a[i] + b[i]) % MOD;
  return a;
}

Poly operator - (Poly a, Poly b) {
  if (a.size() < b.size()) a.resize(b.size());
  for (int i = 0; i < b.size(); ++i) a[i] = (a[i] - b[i] + MOD) % MOD;
  return a;
}

Poly operator * (Poly a, Poly b) {
  int deg = (int) (a.size() + b.size()) - 2;
  int len = (deg == 0 ? 1 : 1 << (32 - __builtin_clz(deg)));
  a.resize(len); b.resize(len);
  FFT::fft(len, a, false); FFT::fft(len, b, false);
  a.resize(len);
  for (int i = 0; i < len; ++i) a[i] = 1LL * a[i] * b[i] % MOD; 
  FFT::fft(len, a, true);
  a.resize(deg + 1);
  return a;
}

Poly inverse(Poly a) {
  int n = a.size();
  a.resize(n*2);
  Poly res = {power(a[0], MOD-2)};
  for (int len = 2; len < n<<1; len <<= 1) {
    Poly tmp = res * res * vector<int>(a.begin(), a.begin() + len);
    res.resize(len);
    for (int i = 0; i < len; ++i) res[i] = (2LL * res[i] - tmp[i] + MOD) % MOD;
  }
  res.resize(n);
  return res;
}

Poly square(Poly p) {
  return p * p;
}

void init() {
  fact[0] = 1;
  for (int i = 1; i < N; ++i) fact[i] = 1LL * i * fact[i - 1] % MOD;
  ifact[N - 1] = power(fact[N - 1], MOD - 2);
  for (int i = N - 2; i >= 0; --i) ifact[i] = 1LL * ifact[i + 1] * (i + 1) % MOD;

  for (int i = 0; i < N/2; ++i) catalan[i] = 1LL * fact[i * 2] * ifact[i] % MOD * ifact[i + 1] % MOD;

  FFT::init_fft();
}

int main() {
  init();
  scanf("%d", &n);

  Poly oddCatalans(n + 1);
  for (int i = 1; i <= n; i += 2) oddCatalans[i] = catalan[i/2];

  Poly evenCatalans(n + 1);
  for (int i = 2; i <= n; i += 2) evenCatalans[i] = catalan[i/2 - 1];

  Poly twos(n + 1);
  twos[0] = 1; for (int i = 1; i <= n; ++i) twos[i] = 2LL * twos[i - 1] % MOD;

  Poly oddCatalans2(n + 1);
  for (int i = 1; i <= n; i += 2) oddCatalans2[i] = 1LL * oddCatalans[i] * (i/2 + 1) % MOD;

  Poly evenCatalans2(n + 1);
  for (int i = 2; i <= n; i += 2) evenCatalans2[i] = 1LL * evenCatalans[i] * (i/2) % MOD;

  Poly twos2(n + 1);
  for (int i = n; i > 0; --i) twos2[i] = twos[i - 1]; twos2[0] = 0;

  int ans = (((oddCatalans2 * square(inverse(Poly({1}) - oddCatalans))) + (evenCatalans2 * twos) + twos2) * inverse(Poly({1, MOD - 1}) - evenCatalans))[n];

  ans = 1LL * ans * power(power(2, n), MOD - 2) % MOD;
  ans = (MOD - ans + n) % MOD;
  printf("%d\n", ans);
  return 0;
}
