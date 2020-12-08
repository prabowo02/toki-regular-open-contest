#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  cin >> s >> s;
  s.resize(unique(begin(s), end(s)) - begin(s));
  cout << s << "\n";
  return 0;
}
