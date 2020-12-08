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

  int n, k, p;
  vector<int> arr;

  n = getInt(in, false);
  k = getInt(in, false);
  p = getInt(in, false);

  for (int i = 0 ; i < n ; i++) {
    int x = getInt(in, false);
    arr.push_back(x);
  }

  int judgeAns = getInt(out, false);

  int conAns = getInt(con, false);
  vector<int> conArr;
  for (int i = 0 ; i < n ; i++) {
    int x = getInt(con, false);
    conArr.push_back(x);
  }

  int diff = 0;
  int cnt = 0;
  int mx = 0;

  for (int i = 0 ; i < n ; i++) {
    diff += (arr[i] != conArr[i]);
    if (i == 0 || conArr[i] != conArr[i-1]) cnt = 1;
    else cnt++;

    if (conArr[i] < 1 || conArr[i] > p) {
      wa();
    }
    mx = max(mx, cnt);
  }

  if (diff > k) wa();
  if (mx != conAns) wa();
  if (conAns > judgeAns) wa();

  ac();
  return 0;
}