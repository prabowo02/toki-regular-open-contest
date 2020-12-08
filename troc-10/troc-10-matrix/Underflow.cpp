#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int n, m, p;
int arr[N][N];
long long vals[N][N];

void read() {
  scanf("%d %d %d", &n, &m, &p);
  for (int i = 1 ; i <= n ; i++) {
    for (int j = 1 ; j <= m ; j++) {
      scanf("%d", &arr[i][j]);
    }
  }
}

void add(int x, int y, long long val) {
  // printf("add (%d, %d) by %d\n", x, y, val);
  vals[x][y] += val;
}

bool work() {
  for (int i = 1 ; i <= n ; i++) {
    for (int j = 1 ; j <= m ; j++) {
      vals[i][j] = vals[i][j] + vals[i-1][j] + vals[i][j-1] - vals[i-1][j-1];
      
      // printf("(%d, %d) -> arr %d vals %d\n", i, j, arr[i][j], vals[i][j]);
      if (vals[i][j] > arr[i][j]) {
        // return false;
      }
      if (vals[i][j] == arr[i][j]) {
        continue;
      }
      if (i + p - 1 > n || j + p - 1 > m) {
        return false;
      }

      long long diff = (arr[i][j] - vals[i][j]);
      add(i, j, diff);
      add(i+p, j, -diff);
      add(i, j+p, -diff);
      add(i+p, j+p, diff);
    }
  }

  return true;
}

int main() {
  read();
  printf("%s\n", work() ? "YA" : "TIDAK");
  return 0;
}