// Author   : rama_pang
// Problem  : troc-12-fungsi
// Time     : O(A B log max(X, Y) + Q log max(X, Y))
// Memory   : O(A B log max(X, Y))

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int BITS = 30;

int A, B, KA, KB, LA, LB;
long long func[MAXN][BITS]; // Sparse Table on func()'s while loop decrement

void Build() { // Build Sparse Table
  for (int a = 0; a < A; a++) {
    for (int b = 0; b < B; b++) {
      if (a == KA) {
        func[a * B + b][0] = LA;
      } else if (b == KB) {
        func[a * B + b][0] = LB;
      } else {
        func[a * B + b][0] = 1;
      }
    }
  }

  for (int j = 1; j < BITS; j++) {
    for (int i = 0; i < A * B; i++) {
      int a = i / B, b = i % B;
      if ((a -= func[i][j - 1] % A) < 0) a += A; 
      if ((b -= func[i][j - 1] % B) < 0) b += B;
      func[i][j] = func[i][j - 1] + func[a * B + b][j - 1];
    }
  }
}

pair<int, int> FindRoot(int X) { // Find number of iteration of while loop in func() that X > 0 holds, (depth, final value)
  int depth = 0;
  for (int j = BITS - 1; j >= 0; j--) {
    if (X > func[(X % A) * B + (X % B)][j]) {
      X -= func[(X % A) * B + (X % B)][j];
      depth |= 1 << j;
    }
  }
  
  return {depth, X};
}

int Lift(int X, int D) { // Do D number of iterations of func()'s while loop on X
  for (int j = 0; (1 << j) <= D; j++) {
    if (D & (1 << j)) {
      X -= func[(X % A) * B + (X % B)][j];
    }
  }

  return X;
}

int Query(int X, int Y) { // Find Lowest Common Ancestor of X and Y by binary lifting
  pair<int, int> DX = FindRoot(X), DY = FindRoot(Y);
  if (DX > DY) swap(X, Y), swap(DX, DY);

  if (DX.second != DY.second) return -1;
  Y = Lift(Y, DY.first - DX.first);

  for (int j = BITS - 1; j >= 0; j--) {
    if (X - func[(X % A) * B + (X % B)][j] != Y - func[(Y % A) * B + (Y % B)][j]) {
      X -= func[(X % A) * B + (X % B)][j];
      Y -= func[(Y % A) * B + (Y % B)][j];
    }
  }

  return (X == Y ? X : X - func[(X % A) * B + (X % B)][0]);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);

  cin >> A >> B >> KA >> KB >> LA >> LB;  
  Build();

  int Q;
  cin >> Q;

  for (int i = 0; i < Q; i++) {
    int X, Y;
    cin >> X >> Y;
    cout << Query(X, Y) << "\n";
  }

  return 0;
}
