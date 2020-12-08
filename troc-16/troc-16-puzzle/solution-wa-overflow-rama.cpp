#include <bits/stdc++.h>
using namespace std;

ostream& operator<<(ostream &os, __int128_t x) {
  string s;
  while (x > 0) {
    s.push_back(x % 10 + '0');
    x /= 10;
  }
  reverse(begin(s), end(s));
  os << s;
  return os;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N;
  cin >> N;
  
  __int128_t A = (__int128_t) LLONG_MAX;
  __int128_t B = (__int128_t) LLONG_MAX;

  A *= 2;
  B *= 2;

  A += 2;
  B += 2;

  A += 1;
  B += N;

  cout << A << ' ' << B << '\n';
  return 0; 
}
