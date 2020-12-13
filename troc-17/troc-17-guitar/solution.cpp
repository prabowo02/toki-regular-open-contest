#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }
  return ret;
}

namespace FFT {

const int LN = 23;
const int N = 1 << LN;

const int PRIMITIVE_ROOT = 3;

int root[N];

void init_fft() {
  const int UNITY = power(PRIMITIVE_ROOT, MOD-1 >> LN);
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

const int MAXN = 100005;

int N, M, T, K;
char F[MAXN], S[MAXN];

int main() {
  scanf("%d %d %d %d", &N, &M, &T, &K);
  scanf("%s", F);
  scanf("%s", S);

  int len = 1 << 32 - __builtin_clz(N + K);
  vector<vector<int>> P(T, vector<int>(len)), Q(T, vector<int>(len));

  for (int i = 0; i < N; ++i) {
    P[F[i] - 'A'][i] = 1;
  }

  reverse(S, S + K);
  for (int i = 0; i < K; ++i) {
    Q[S[i] - 'A'][i] = 1;
  }

  FFT::init_fft();
  for (int i = 0; i < T; ++i) {
    FFT::fft(len, P[i], false);
    FFT::fft(len, Q[i], false);
  }

  vector<int> R(len);
  int mod = M % T;
  for (int k = 0; k < len; ++k) {
    for (int i = 0; i < T; ++i) {
      for (int j = 0; j < mod; ++j) {
        R[k] = (R[k] + 1LL * P[i][k] * Q[(i + j) % T][k]) % MOD;
      }
    }
  }
  FFT::fft(len, R, true);

  int ans = 0;
  for (int i = 0; i < N - K + 1; ++i) {
    int cnt = R[K - 1 + i];
    ans = (ans + 1LL * power(M/T, K - cnt) * power(M/T + 1, cnt)) % MOD;
  }

  printf("%d\n", ans);
  return 0;
}
