#include <bits/stdc++.h>
using namespace std;

int Solve(int N, int M, vector<int> U, vector<int> V) {
  int ans = 0;

  const auto NotIntersect = [&](int x, int y) {
    for (int i = 0; i < int(U.size()); i++) {
      if (U[i] == x && V[i] == y) {
        return false;
      }
      if (U[i] < x && x < V[i] && V[i] < y) {
        return false;
      }
      if (x < U[i] && U[i] < y && y < V[i]) {
        return false;
      }
    }
    return true;
  };

  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      if (NotIntersect(i, j)) {
        ans += 1;
        U.emplace_back(i);
        V.emplace_back(j);
      }
    }
  }

  assert(ans == N + N - 3 - M);
  return ans;
}

int main() {
  int N, M;
  cin >> N >> M;

  vector<int> U(M), V(M);
  for (int i = 0; i < M; i++) {
    cin >> U[i] >> V[i];
    U[i]--, V[i]--;
  }

  cout << Solve(N, M, U, V) << '\n';
  return 0;
}
