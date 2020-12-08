#include <bits/stdc++.h>
using namespace std;

const double TOL = 1e-6;

void wa() {
  puts("WA");
  exit(0);
}

void ac() {
  puts("AC");
  exit(0);
}

int main(int argc, char *argv[]) {
  ifstream out, con;

  out.open(argv[2]);
  con.open(argv[3]);

  double judge, contestant;

  while(out >> judge) {
    if(!(con >> contestant)) {
      wa();
    }

    if(!(fabs(judge - contestant) / max(1.0, judge) <= TOL)) {
      wa();
    }
  }

  string dummy;
  if(con >> dummy) {
    wa();
  }

  ac();
}