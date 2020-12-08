#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);

  int H, N;
  cin >> H >> N;

  vector<int> D(N);
  for (int i = 0; i < N; i++) {
    cin >> D[i];
  }

  int S;
  cin >> S;

  vector<int> A(N), B(N), T(N), Q(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i] >> B[i] >> T[i] >> Q[i];
  }

  int X;
  cin >> X;
  X--;

  vector<long long> dist(N, 2e18);
  dist[X] = 0;

  for (int lo = X, hi = X; 0 <= lo || hi < N;) {
    int u = -1;
    if (lo >= 0) if (u == -1 || dist[u] > dist[lo]) u = lo;
    if (hi <  N) if (u == -1 || dist[u] > dist[hi]) u = hi;
    if (u == lo) lo--;
    if (u == hi) hi++;

    for (int v = 0; v <= lo; v++) {
      long long cost = 1ll * (D[u] - D[v]) * S;
      if (A[u] <= D[v] && D[v] <= B[u]) {
        cost = min(cost, Q[u] + 1ll * (D[u] - D[v]) * T[u]);
      } else if (D[v] < A[u]) {
        cost = min(cost, Q[u] + 1ll * (D[u] - A[u]) * T[u] + 1ll * (A[u] - D[v]) * S);
      }
      dist[v] = min(dist[v], cost + dist[u]);
    }

    for (int v = hi; v < N; v++) {
      long long cost = 1ll * (D[v] - D[u]) * S;
      if (A[u] <= D[v] && D[v] <= B[u]) {
        cost = min(cost, Q[u] + 1ll * (D[v] - D[u]) * T[u]);
      } else if (B[u] < D[v]) {
        cost = min(cost, Q[u] + 1ll * (B[u] - D[u]) * T[u] + 1ll * (D[v] - B[u]) * S);
      }
      dist[v] = min(dist[v], cost + dist[u]);
    }
  }

  for (int i = 0; i < N; i++) {
    cout << dist[i] << "\n";
  }
  return 0;
}
