// Author   : rama_pang
// Problem  : troc-12-kursi
// Time     : O(Q log max(X, Y))
// Memory   : O(1)

#include <bits/stdc++.h>
using namespace std;

bool Solve(int X, int Y, int T, int L) {
  // T = 0: detect form (1, 1), T = 1: detect form (3, 1) 
  // T = 2: detect form (1, 3), T = 3: detect form (7, 3)
  while (true) {
    if (X == 0 || Y == 0) return false;
    while (L > 2 && L / 2 > max(X, Y)) L /= 2;
    if      (X == L / 2 && Y == L / 2) return T == 0;
    else if (X == L / 2 || Y == L / 2) return false;
    else if (X >= L / 2 && Y >= L / 2) X -= L / 2, Y -= L / 2;
    else if (X >= L / 2 && Y <= L / 2) X = L - X, T ^= 1;
    else if (X <= L / 2 && Y >= L / 2) Y = L - Y, T ^= 2;            
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);

  int Q;
  cin >> Q;

  for (int i = 0; i < Q; i++) {
    int X, Y;
    cin >> X >> Y;
    cout << (X + Y + 2 * Solve(X, Y, 0, 1 << 30)) << "\n";
  }

  return 0;
}
