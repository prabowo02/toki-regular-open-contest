#include <bits/stdc++.h>
using namespace std;

int N, sum;

int main() {
  ios_base::sync_with_stdio(0);
  cin >> N;
  int A;
  for(int i = 1; i <= N; i++) {
    cin >> A;
    sum += A;
  }
  if(N == 2 && !(sum & 1)) cout << "NO\n";
  else if(sum == 0) cout << "NO\n";
  else cout << "YES\n";
}