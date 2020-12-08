#include <iostream>
using namespace std;

int main() {
  int g1 = 0;
  int b1 = 0;
  int k1 = 0;
  int g2 = 0;
  int b2 = 0;
  int k2 = 0;

  int n;
  string sequence1, sequence2;
  cin >> n >> sequence1 >> sequence2;

  for (int i = 0; i < n; ++i) {
    if (sequence1[i] == 'G') {
      g1++;
    }
    if (sequence1[i] == 'B') {
      b1++;
    }
    if (sequence1[i] == 'K') {
      k1++;
    }
    if (sequence2[i] == 'G') {
      g2++;
    }
    if (sequence2[i] == 'B') {
      b2++;
    }
    if (sequence2[i] == 'K') {
      k2++;
    }
  }

  int answer = min(g1, k2) + min(b1, g2) + min(k1, b2);
  cout << answer << endl;

  return 0;
}