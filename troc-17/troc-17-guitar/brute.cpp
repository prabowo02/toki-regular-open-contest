#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <cstdio>

const int MOD = 998244353;
const int MAXN = 100005;
const int MAXT = 7;

int N, M, T, K;
char F[MAXN], S[MAXN];

int ones[MAXT][MAXT];

int main() {
  scanf("%d %d %d %d", &N, &M, &T, &K);
  scanf("%s", F);
  scanf("%s", S);

  int d = M/T, m = M%T;
  for (int i = 0; i < T; ++i) for (int j = 0; j < T; ++j) {
    ones[i][j] = ((i - j + T) % T < m);
  }

  for (int i = 0; i < N; ++i) F[i] -= 'A';
  for (int i = 0; i < K; ++i) S[i] -= 'A';

  int ans = 0;
  for (int i = 0; i < N - K + 1; ++i) {
    int prod = 1;
    for (int j = 0; j < K; ++j) {
      prod = 1LL * prod * (d + ones[S[j]][F[i + j]]) % MOD;
    }
    ans = (ans + prod) % MOD;
  }

  printf("%d\n", ans);
  return 0;
}
