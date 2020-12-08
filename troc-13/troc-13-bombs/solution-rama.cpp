#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M, R;
  cin >> N >> M >> R;
  cout << (min(N, M) + 2 * R) / (2 * R + 1) << "\n";
  return 0;
}
