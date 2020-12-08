#include <bits/stdc++.h>
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

  int n, x, y;
  input >> n >> x >> y;

  int judgeAns; judgeOutput >> judgeAns;
  bool solutionExist = judgeAns != -1;
  string dummy;

  if (solutionExist) {
    vector<int> ret(4);
    
    for (int &x : ret) {
      if (!(contestantOutput >> x)) {
        wa();
      }
      if (x < 0 || x > n) wa();
    }
    if (contestantOutput >> dummy) wa();

    if (ret[0] - ret[2] != y) wa();
    if (ret[1] - ret[3] != x) wa();
    if (accumulate(ret.begin(), ret.end(), 0) != n) wa();
  } else {
    int ret;

    if (!(contestantOutput >> ret)) wa();
    if (contestantOutput >> dummy) wa();
    if (ret != -1) wa();
  }

  ac();
  return 0;
}