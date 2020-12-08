#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m, k;
  cin >> n >> m >> k;


  vector<string> ans;
  for (int i = 0 ; i < n ; i++) {
    string s;
    for (int j = 0 ; j < m ; j++) {
      s += '.';
    }
    // printf("%s\n", s.c_str());
    ans.push_back(s);
  }

  int used = 0;
  if (n * m <= 2) {
    used = n * m;
    for (int i = 0 ; i < n ; i++) {
      for (int j = 0 ; j < m ; j++) {
        ans[i][j] = 'X';
      }
    }
  } else if (n == 1) {
    for (int j = 0 ; j < m ; j += 2) {
      ans[0][j] = 'X';
      used++;
    }
    if (m % 2 == 0) {
      ans[0][m-1] = 'X';
      used++;
    }
  } else if (m == 1) {
    for (int i = 0 ; i < n ; i += 2) {
      ans[i][0] = 'X';
      used++;
    }
    if (n % 2 == 0) {
      ans[n-1][0] = 'X';
      used++;
    }
  } else {
    int divInN = 0;
    int divInM = 0;

    divInN = n / 2 + (m - 1);
    if (n % 2 == 1 && m <= 2) {
      divInN++;
    }

    divInM = m / 2 + (n - 1);
    if (m % 2 == 1 && n <= 2) {
      divInM++;
    }

    if (divInN <= divInM) {
      used = divInN;

      for (int i = 1 ; i < n ; i += 2) {
        ans[i][0] = 'X';
      }
      ans[0][1] = 'X';
      for (int j = 2 ; j < m ; j++) {
        ans[n-1][j] = 'X';
      }

      if (n % 2 == 1 && m <= 2) {
        ans[n-1][0] = 'X';
      }
    } else {
      used = divInM;

      for (int i = 1; i < m; i += 2) {
        ans[0][i] = 'X';
      }
      ans[1][0] = 'X';
      for (int j = 2; j < n; j++) {
        ans[j][m-1] = 'X';
      }

      if (m % 2 == 1 && n <= 2) {
        ans[0][m-1] = 'X';
      }
    }
  }

  if (used > k) {
    puts("TIDAK");
    return 0;
  }

  puts("YA");
  for (int i = 0 ; i < n ; i++) {
    for (int j = 0 ; j < m ; j++) {
      if (ans[i][j] == '.' && used < k) {
        ans[i][j] = 'X';
        used++;
      }
    }
    printf("%s\n", ans[i].c_str());
  }

  return 0;
}
