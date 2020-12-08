// Author   : rama_pang
// Problem  : troc-12-frekuensi
// Time     : O(N^4)
// Memory   : O(N^3)

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 255;

int N, L, R;
int A[MAXN][MAXN];
int cnt[MAXN][MAXN][2 * MAXN];

void Read() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);

  cin >> N >> L >> R;
  
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      cin >> A[i][j];
    }
  }
}

long long Solve() {
  int dist;
  for (int i1 = 1; i1 <= N; i1++) {
    for (int j1 = 1; j1 <= N; j1++) {
      for (int i2 = i1; i2 <= N; i2++) {
        for (int j2 = (i1 == i2 ? j1 + 1 : 1); j2 <= N; j2++) {
          dist = (i2 - i1) + (j2 - j1 < 0 ? j1 - j2 : j2 - j1);
          if (L * dist <= A[i1][j1] * A[i2][j2] && A[i1][j1] * A[i2][j2] <= R * dist) {
            cnt[i1][j1][dist]++;
            cnt[i2][j2][dist]++;
          }
        }
      }
    }
  }

  long long ans = 0;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      for (int d = 1; d <= 2 * N; d++) {
        ans += 1ll * cnt[i][j][d] * cnt[i][j][d];
      }
    } 
  }

  return ans;
}

int main() {
  Read();
  cout << Solve() << "\n";
  return 0;
}
