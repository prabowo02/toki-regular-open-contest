#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  string ord = "pie";
  for (int i = 0; i < N; i++) {
    cout << ord[i % 3];
  }
  cout << '\n';
  return 0;
}
