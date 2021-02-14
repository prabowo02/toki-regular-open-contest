#include <bits/stdc++.h>
using namespace std;

int main() {
  int K;
  cin >> K;

  vector<int> ans;
  for (int i = 0; i < 15; i++) {
    if ((K >> i) & 1) {
      ans.emplace_back((1 << i) + (0 << (i + 15)));
      ans.emplace_back((0 << i) + (1 << (i + 15)));
    }
  }

  int N = (int) ans.size();
  for (int i = N - 1; i > 0; i--) {
    ans[i - 1] |= ans[i];
  }

  [&]() { // Verify answer
    int xor_all = 0;
    for (int i = 0; i < N; i++) {
      xor_all ^= ans[i];
      for (int j = i + 1; j < N; j++) {
        assert(ans[i] != ans[j]);
        assert((ans[i] & ans[j]) == ans[j]);
        assert(1 <= ans[i] && ans[i] < (1 << 30));
      }
    }
    assert(xor_all == K);
  };

  cout << N << '\n';
  for (int i = 0; i < N; i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << ans[i];
  }
  cout << '\n';
  return 0;
}
