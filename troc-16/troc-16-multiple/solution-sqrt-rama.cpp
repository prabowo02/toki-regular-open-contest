#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  
  const int M = 1e5 + 5;
  const int SQRT = (int) sqrt(M) + 5;
  const int MOD = 1e9 + 7;

  const auto Power = [&](int a, long long x) {
    int res = 1;
    while (x > 0) {
      if (x & 1) {
        res = 1ll * res * a % MOD;
      }
      a = 1ll * a * a % MOD;
      x /= 2;
    }
    return res;
  };

  vector<int> isprime(M, 1);
  vector<int> factorize(M, 1);

  for (int i = 2; i < M; i++) {
    if (isprime[i]) {
      for (int j = i; j < M; j += i) {
        isprime[j] = 0;
        factorize[j] = i;
      }
    }
  }

  vector<vector<pair<int, int>>> occ(M);
  for (int i = 0; i < N; i++) {
    while (A[i] > 1) {
      int p = factorize[A[i]];
      A[i] /= p;
      if (!occ[p].empty() && occ[p].back().first == i) {
        occ[p].back().second += 1;
      } else {
        occ[p].emplace_back(i, 1);
      }
    }
  }

  int ans = 1;
  for (int p = 2; p < SQRT; p++) { 
    // Amoritzed O(N sqrt A).
    // There are O(sqrt A / log A) primes below sqrt A,
    // and processing each prime takes O(N log A).
    int power_sum = 0;
    vector<int> value(N);
    for (auto i : occ[p]) {
      value[i.first] = i.second;
    }
    vector<array<int, 3>> st;
    st.push_back({-1, MOD, 0});
    for (int i = 0; i < N; i++) {
      int id = i;
      int freq = value[i];
      while (!st.empty() && st.back()[1] <= freq) {
        power_sum -= st.back()[2];
        st.pop_back();
      }
      int add = freq * (id - st.back()[0]);
      power_sum += add;
      st.push_back({id, freq, add});
      ans = 1ll * ans * Power(p, power_sum) % MOD;
    }
  }

  for (int p = SQRT; p < M; p++) {
    for (auto i : occ[p]) {
      assert(i.second == 1);
    }
    int last = -1;
    occ[p].emplace_back(N, 0);
    long long cnt = 1ll * N * (N + 1) / 2;
    for (auto i : occ[p]) {
      int len = i.first - last - 1;
      last = i.first;
      cnt -= 1ll * len * (len + 1) / 2;
    }
    ans = 1ll * ans * Power(p, cnt) % MOD;
  }

  cout << ans << '\n';
  return 0; 
}
