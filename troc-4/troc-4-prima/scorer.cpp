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
  ifstream in, con;

  in.open(argv[1]);
  con.open(argv[3]);

  int ans;
  con >> ans;

  if (ans < 2 || ans > 100) wa();

  for (int i = 0; i < 3; ++i) {
    int x; in >> x;
    if (ans % x == 0) wa();
  }

  string dummy;
  if (con >> dummy) {
    wa();
  }

  ac();
}
