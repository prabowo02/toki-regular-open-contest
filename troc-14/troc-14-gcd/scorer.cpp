#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void ac() {
  puts("AC");
  exit(0);
}

void wa() {
  puts("WA");
  exit(0);
}

int main(int argc, char** argv) {
  ifstream input(argv[1]);
  ifstream judgeOutput(argv[2]);
  ifstream contestantOutput(argv[3]);

  int N;
  input >> N;

  int len;
  string ans;
  if (!(contestantOutput >> len)) wa();

  if (len > 0) {
    if (!(contestantOutput >> ans)) wa();
  }

  string dummy;
  if (contestantOutput >> dummy) wa();

  if (ans.size() != len) wa();
  if (len > 101) wa();

  int cur = 0;
  vector<int> positions;
  for (char c: ans) {
    if (c == 'L') {
      cur = (cur + N-1) % N;
    } else if (c == 'R') {
      cur = (cur + 1) % N;
    } else if (c == 'G') {
      positions.push_back(cur);
    } else {
      wa();
    }
  }

  sort(positions.begin(), positions.end());

  if (N > 1 && unique(positions.begin(), positions.end()) - positions.begin() <= N/2) wa();

  ac();
  return 0;
}

