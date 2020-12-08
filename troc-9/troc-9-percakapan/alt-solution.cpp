#pragma GCC diagnostic ignored "-Wshift-op-parentheses"

#include <bits/stdc++.h>
using namespace std;

char dir[4] = {'U', 'D', 'R', 'L'};
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int x[4], y[4];

char s[5];
void go() {
  scanf("%s", s);
  if (s[0] == 'S') exit(0);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (s[i] == dir[j]) {
        x[i] += dx[j];
        y[i] += dy[j];
        break;
      }
    }
  }
}

char getNextStep() {
  vector<tuple<int, int, int>> v;
  for (int i = 0; i < 3; ++i) {
    for (int j = i+1; j < 3; ++j) {
      int walk = abs(x[i] - x[j]) + abs(y[i] - y[j]) >> 1;

      for (int k = 0; k < 4; ++k) {
        if (abs(x[i]+walk*dx[k] - x[j]) + abs(y[i]+walk*dy[k] - y[j]) == walk) {
          // cerr << x[i] << " " << y[i] << " " << walk << " " << dx[k] << " " << dy[k] << " " << x[i] + walk*dx[k] << " " << y[i] + walk*dx[k] << endl;
          v.emplace_back(x[i] + walk*dx[k], y[i] + walk*dy[k], walk);
        }
      }

      for (int k = 0; k < 4; ++k) {
        if (abs(x[i] - (x[j]+walk*dx[k])) + abs(y[i] - (y[j]+walk*dy[k])) == walk) {
          v.emplace_back(x[j] + walk*dx[k], y[j] + walk*dy[k], walk);
        }
      }
    }
  }

  for (int i = 0; i < 4; ++i) {
    bool can = true;
    for (int j = 0; j < v.size(); ++j) {
      int xx, yy, walk;
      tie(xx, yy, walk) = v[j];

      // cerr << xx << " " << yy << " " << walk << endl;

      if (abs(xx - x[3]-dx[i]) + abs(yy - y[3]-dy[i]) > walk) {
        can = false;
        break;
      }
    }

    if (can) {
      x[3] += dx[i];
      y[3] += dy[i];
      return dir[i];
    }
  }

  return 'X';
}

int main() {
  while (true) {
    go();
    printf("%c\n", getNextStep());
    fflush(stdout);
  }

  return 0;
}
