#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <cstdio>

constexpr int MAXN = 250;

int N, L, R;
int A[MAXN][MAXN];

int dist[MAXN<<1];
int d, mul;

long long ans;

int main() {
  scanf("%d %d %d", &N, &L, &R);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      scanf("%d", &A[i][j]);
    }
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      for (int k = 0; k < i; ++k) {
        for (int l = 0; l < j; ++l) {
          d = i-k + j-l;
          mul = A[i][j] * A[k][l];
          dist[d] += L*d <= mul && mul <= R*d;
        }
        for (int l = j; l < N; ++l) {
          d = i-k + l-j;
          mul = A[i][j] * A[k][l];
          dist[d] += L*d <= mul && mul <= R*d;
        }
      }

      for (int k = i; k < N; ++k) {
        for (int l = 0; l < j; ++l) {
          d = k-i + j-l;
          mul = A[i][j] * A[k][l];
          dist[d] += L*d <= mul && mul <= R*d;
        }
        for (int l = j; l < N; ++l) {
          d = k-i + l-j;
          mul = A[i][j] * A[k][l];
          dist[d] += L*d <= mul && mul <= R*d;
        }
      }

      for (int d = N*2 - 2; d > 0; --d) {
        ans += dist[d] * dist[d];
        dist[d] = 0;
      }
    }
  }

  printf("%lld\n", ans);
  return 0;
}
