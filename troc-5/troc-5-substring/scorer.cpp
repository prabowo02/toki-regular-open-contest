#include <bits/stdc++.h>
using namespace std;

void giveScore(double points) {
  puts("OK");
  printf("%.2lf\n", points);
  exit(0);
}

void ac() {
  puts("AC");
  exit(0);
}

void wa() {
  puts("WA");
  exit(0);
}

string getString(ifstream &is, bool isFullLine) {
  string ret;

  if (isFullLine) {
    if (!(getline(is, ret))) wa();
  } else {
    if (!(is >> ret)) wa();
  }

  return ret;
}

int parseInt(string x) {
  if (x.length() == 0) wa();
  int sign = 1;

  if (x[0] == '-') {
    sign = -1;
    x = x.substr(0, x.length() - 1);
  }

  if (x.length() == 0 || x.length() > 9) wa();

  int ret = 0;
  for (char it : x) {
    if (it < '0' || it > '9') wa();
    ret = 10 * ret + (it - '0');
  }

  return ret * sign;
}

int getInt(ifstream &is, bool isFullLine) {
  return parseInt(getString(is, isFullLine));
}

vector<string> tokenize(string s) {
  stringstream ss(s);
  vector<string> ret;
  string token;

  while (ss >> token) {
    ret.push_back(token);
  }

  return ret;
}

int main(int argc, char *argv[]) {
  ifstream in, out, con;

  in.open(argv[1]);
  out.open(argv[2]);
  con.open(argv[3]);

  string x = getString(in, false);
  string y = getString(in, false);

  string judgeAns = getString(out, false);
  string conAns = getString(con, false);
  
  if (judgeAns != conAns) wa();
  if (conAns == "YA") {
    string ans = getString(con, false);

    if (!(ans.find(x) != string::npos && ans.find(y) == string::npos)) {
      wa();
    }
    if (ans.size() > 100) {
      wa();
    }

    for (char ch : ans) {
      if (ch < 'a' || ch > 'z') {
        wa();
      }
    }
  }

  string dummy;
  if (con >> dummy) {
    wa();
  }

  ac();
}
