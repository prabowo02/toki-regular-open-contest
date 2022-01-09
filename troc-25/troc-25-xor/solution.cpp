#include <bits/stdc++.h>
using namespace std;

pair<int, int> maxmin(const vector<int> &A, int K) {
  int N = A.size();
  int sum = 0;
  for (int i = 0; i < K; ++i) {
    sum += A[i];
  }

  int maxi = sum, mini = sum;
  for (int i = K; i < N; ++i) {
    sum += A[i] - A[i - K];
    maxi = max(maxi, sum);
    mini = min(mini, sum);
  }

  return make_pair(maxi, mini);
}

int main() {
  int N, M, K;
  scanf("%d %d %d", &N, &M, &K);
  vector<int> A(N), B(M);
  for (int i = 0; i < N; ++i) scanf("%d", &A[i]);
  for (int j = 0; j < M; ++j) scanf("%d", &B[j]);

  pair<int, int> p = maxmin(A, K), q = maxmin(B, K);
  printf("%lld\n", max({1LL * p.first * (K - q.second) + 1LL * (K - p.first) * q.second,
                        1LL * (K - p.second) * q.first + 1LL * p.second * (K - q.first),
                        1LL * p.first * (K - q.first) + 1LL * (K - p.first) * q.first,
                        1LL * (K - p.second) * q.second + 1LL * p.second * (K - q.second)}));
  return 0;
}
