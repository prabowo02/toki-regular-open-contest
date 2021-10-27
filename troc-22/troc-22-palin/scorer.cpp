#include <bits/stdc++.h>
using namespace std;

void WA(string reason) {
  cout << "WA" << endl;
  exit(0);
}

void AC() {
  cout << "AC" << endl;
  exit(0);
}

bool isPalindrome(string s) {
  for (int i = 0; i < int(s.size()); i++) {
    if (s[i] != s[int(s.size()) - 1 - i]) {
      return false;
    }
  }
  return true;
}

int getScore(string s) {
  vector<string> palins;
  for (int i = 0; i < int(s.size()); i++) {
    string t;
    for (int j = i; j < int(s.size()); j++) {
      t.push_back(s[j]);
      if (isPalindrome(t)) {
        palins.emplace_back(t);
      }
    }
  }
  sort(begin(palins), end(palins));
  palins.resize(unique(begin(palins), end(palins)) - begin(palins));
  return palins.size();
}

int main(int argc, char *argv[]) {
  ifstream tc_in(argv[1]);
  ifstream tc_out(argv[2]);
  ifstream con_out(argv[3]);

  int N;
  string judge_ans;
  string contestant_ans;

  tc_in >> N;
  tc_out >> judge_ans;

  if (!(con_out >> contestant_ans)) {
    WA("No output");
  }

  string eof;
  if (con_out >> eof) {
    WA("Incorrect output format");
  }

  if (contestant_ans.size() != N) {
    WA("Incorrect size of string");
  }

  for (int i = 0; i < N; i++) {
    if (!('a' <= contestant_ans[i] && contestant_ans[i] <= 'z')) {
      WA("Incorrect alphabet");
    }
  }

  int judge_score = getScore(judge_ans);
  int contestant_score = getScore(contestant_ans);
  assert(contestant_score >= judge_score);

  if (contestant_score > judge_score) {
    WA("Contestant's answer is not optimal");
  } else {
    AC();
  }
  return 0;
}
