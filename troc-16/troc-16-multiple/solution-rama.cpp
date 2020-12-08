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
  for (int p = 2; p < M; p++) {
    if (occ[p].empty()) {
      continue;
    }
    
    long long total_power_sum = 0;
    int current_power_sum = 0;
    
    vector<array<int, 3>> st;
    st.push_back({-1, MOD, 0});
    occ[p].emplace_back(N, 0);

    for (int i = 0; i + 1 < (int) occ[p].size(); i++) {
      auto [id, freq] = occ[p][i];
      while (!st.empty() && st.back()[1] <= freq) {
        current_power_sum -= st.back()[2];
        st.pop_back();
      }
      int add = freq * (id - st.back()[0]);
      current_power_sum += add;
      st.push_back({id, freq, add});
      total_power_sum += 1ll * current_power_sum * (occ[p][i + 1].first - id);
    }

    ans = 1ll * ans * Power(p, total_power_sum) % MOD;
  }

  cout << ans << '\n';
  return 0; 
}
