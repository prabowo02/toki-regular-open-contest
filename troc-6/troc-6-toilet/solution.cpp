#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

struct Command {
  int opt;
  int v;

  void print() {
    if (opt == 1) printf("%d %d\n", opt, v);
    else printf("%d\n", opt);
  }
};

int n, m;
char s[N];
bool flag[N];

void read() {
  scanf("%d %d", &n, &m);
  scanf("%s", s);

  for (int i = 0 ; i < n ; i++) {
    if (s[i] == '1')
      flag[i+1] = 1;
  }
}

void work() {
  vector<Command> ans;

  // fill even which will be empty
  for (int i = 2 ; i <= n ; i += 2) {
    if (!flag[i]) {
      ans.push_back((Command){1, i});
    }
  }
  // fill even which will be filled
  for (int i = 2 ; i <= n ; i += 2) {
    if (flag[i]) {
      ans.push_back((Command){1, i});
    }
  }
  // fill odd which will be filled
  for (int i = 1 ; i <= n ; i += 2) {
    if (flag[i]) {
      ans.push_back((Command){1, i});
    }
  }
  // pop even which will be empty
  for (int i = 2 ; i <= n ; i += 2) {
    if (!flag[i]) {
      ans.push_back((Command){2, -1});
    }
  }

  printf("%d\n", (int)ans.size());
  for (Command cmd : ans) {
    cmd.print();
  }
}

int main() {
  read();
  work();
  return 0;
}
