#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(begin(a), end(a));
  a.resize(unique(begin(a), end(a)) - begin(a));
  if (a.size() == 1 || a.size() == n) {
    cout << a.size() << "\n";
  } else {
    cout << n - 1 << "\n";
  }
  return 0;
}
