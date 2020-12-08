/**
 * Author   : rama_pang
 * Problem  : troc-11-robot
 * Time     : O(|S|)
 * Memory   : O(|S|)
**/

#include <bits/stdc++.h>
using namespace std;

int main() {
  string S;
  cin >> S;

  map<char, pair<int, int>> dir;
  dir['R'] = {+1, 0};
  dir['L'] = {-1, 0};
  dir['U'] = {0, +1};
  dir['D'] = {0, -1};
  
  int X = 0,Y = 0;

  for (int i = 0; i < (int) S.size(); i++) {
    X += dir[S[i]].first;
    Y += dir[S[i]].second;       
  }

  cout << X << " " << Y << "\n";
  return 0;
}
