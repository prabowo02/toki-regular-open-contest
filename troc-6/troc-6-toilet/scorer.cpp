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

int n, m;
string s;
vector<bool> target;
vector<bool> flag;
set<int> availables;

void readInput(ifstream &input) {
  input >> n >> m;
  input >> s;

  target.resize(n, false);
  flag.resize(n, false);

  for (int i = 0 ; i < n ; i++) {
    if (s[i] == '1')
      target[i] = true;
  }
}

void update(int idx) {
  for (int i = max(0, idx-1) ; i <= min(n-1, idx+1) ; i++) {
    bool ok = !flag[i];
    if (i > 0) ok &= (!flag[i-1]);
    if (i+1 < n) ok &= (!flag[i+1]);

    if (ok) availables.insert(i);
    else availables.erase(i);
  }
}

int main(int argc, char** argv) {
  ifstream input(argv[1]);
  ifstream judgeOutput(argv[2]);
  ifstream contestantOutput(argv[3]);

  readInput(input);
  for (int i = 0 ; i < n ; i++) {
    update(i);
  }

  int k;

  if (!(contestantOutput >> k)) {
    wa();
  }
  // K must be in [1, 3N]
  if (k < 1 || k > 3 * n) wa();
  
  queue<int> q;
  for (int i = 0 ; i < k ; i++) {
    int opt;

    // we only have 2 opt
    if (!(contestantOutput >> opt)) wa();
    if (opt < 1 || opt > 2) wa();

    if (opt == 2) {
      // can only pop if not empty
      if (q.empty()) wa();

      int idx = q.front(); q.pop();
      flag[idx] = false;
      update(idx);
    } else {
      int idx;

      // pos in range [1, N]
      if (!(contestantOutput >> idx)) wa();
      if (idx < 1 || idx > n) wa();
      idx--;

      // don't use occupied toilet..
      if (flag[idx]) wa();
      // if there is still option but we don't take it
      if (!availables.empty() && !availables.count(idx)) wa();

      flag[idx] = true;
      update(idx);
      q.push(idx);
    }
  }

  // trailing output
  string dummy;
  if (contestantOutput >> dummy) wa();

  // check final state
  if (target != flag) wa();
  ac();

  return 0;
}
