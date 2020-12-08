// Author   : rama_pang
// Problem  : troc-12-frekuensi
// Time     : O(N^3)
// Memory   : O(N^3)

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 255;

int N, L, R;
int A[MAXN][MAXN];
int P[MAXN][MAXN][MAXN]; // Diagonal Prefix Sum (bottom left to top right) of frequency of values

pair<int, int> id[MAXN][MAXN];
int cnt[MAXN][MAXN][2 * MAXN]; // Count Contribution (i, j, dist)

void Read() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);

  cin >> N >> L >> R;
  
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      cin >> A[i][j];
      id[i][j] = {i, j};
    }
  }
}

void Rotate() { // Rotate A counter-clockwise
  int A_[MAXN][MAXN] = {};
  pair<int, int> id_[MAXN][MAXN] = {};

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      A_[N - j + 1][i] = A[i][j];
      id_[N - j + 1][i] = id[i][j];
    }
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      A[i][j] = A_[i][j];
      id[i][j] = id_[i][j];
    }
  }
}

void Calc() { // Calculate Prefix Sum
  memset(P, 0, sizeof(P));
  for (int i = N; i >= 1; i--) {
    for (int j = N; j >= 1; j--) {
      P[i][j][A[i][j]]++;
      for (int k = 0; k < MAXN; k++) {
        P[i][j][k] += P[i + 1][j - 1][k];
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      for (int k = 1; k < MAXN; k++) {
        P[i][j][k] += P[i][j][k - 1];
      }
    }
  }
}

void CountContribution() { // Solve for each cell when only considering upper left side (excluding row, including column)
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      for (int d = 1; d <= i + j - 2; d++) { // Manhattan Distance
        int l = (d * L + A[i][j] - 1) / A[i][j] - 1;
        int r = (d * R) / A[i][j];

        // Count (x, y) which satisfies l < A[x][y] <= r in the diagonal (distance is fixed)
        int offset = max(0, 1 - i + d);
        int &res = cnt[id[i][j].first][id[i][j].second][d];

        res += P[i - d + offset][max(j - offset, 0)][min(r, MAXN - 1)];
        res -= P[i][max(j - d, 0)][min(r, MAXN - 1)];
        if (l == -1) continue;
        res -= P[i - d + offset][max(j - offset, 0)][min(l, MAXN - 1)];
        res += P[i][max(j - d, 0)][min(l, MAXN - 1)];
      }
    }
  }
}

long long Solve() {
  for (int rot = 0; rot < 4; rot++) {
    Rotate(); Calc();
    CountContribution();
  }

  long long ans = 0;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      for (int d = 1; d <= 2 * N; d++) {
        ans += cnt[i][j][d] * cnt[i][j][d]; // (cnt for direct, (cnt * (cnt - 1)) for indirect)
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
