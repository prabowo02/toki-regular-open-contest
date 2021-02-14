#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  const auto Query = [&](int L, int R) {
    static map<pair<int, int>, int> memo;
    if (L > R) return 0;
    if (L == R) return 1;
    if (memo.count({L, R}) == 0) {
      cout << '?' << ' ' << L + 1 << ' ' << R + 1 << endl;
      cin >> memo[{L, R}];
    }
    return memo[{L, R}];
  };

  vector<int> ans;
  for (int i = 0; i < N; i++) {
    if (Query(0, i - 1) + 1 == Query(0, i) && Query(i, N - 1) == 1 + Query(i + 1, N - 1)) {
      ans.emplace_back(i);
    }
  }

  cout << '!' << ' ' << ans.size();
  for (int i = 0; i < (int) ans.size(); i++) {
    cout << ' ' << ans[i] + 1;
  }
  cout << endl;
  return 0;
}
