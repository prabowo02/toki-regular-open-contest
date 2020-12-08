// Author   : rama_pang
// Problem  : troc-12-frekuensi
// Time     : O(N^6)
// Memory   : O(N^2)

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 255;

int N, L, R;
int A[MAXN][MAXN];

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
  long long ans = 0;

  for (int i1 = 1; i1 <= N; i1++) {
    for (int j1 = 1; j1 <= N; j1++) {
      for (int i2 = 1; i2 <= N; i2++) {
        for (int j2 = 1; j2 <= N; j2++) {
          if (i1 == i2 && j1 == j2) continue;
          
          int d = abs(i2 - i1) + abs(j2 - j1);
          int f = A[i1][j1] * A[i2][j2];
          if (L * d <= f && f <= R * d) ans++;

          for (int i3 = 1; i3 <= N; i3++) {
            for (int j3 = 1; j3 <= N; j3++) {
              if (i1 == i3 && j1 == j3) continue;
              if (i2 == i3 && j2 == j3) continue;

              int d1 = abs(i3 - i1) + abs(j3 - j1);
              int d2 = abs(i3 - i2) + abs(j3 - j2);
              int f1 = A[i1][j1] * A[i3][j3];
              int f2 = A[i2][j2] * A[i3][j3];
              
              if (d1 == d2 && L * d1 <= f1 && f1 <= R * d1 && L * d2 <= f2 && f2 <= R * d2) {
                ans++;
              }
            }
          }
        }
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
