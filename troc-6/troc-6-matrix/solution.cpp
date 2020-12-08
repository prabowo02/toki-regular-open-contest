#include <bits/stdc++.h>
using namespace std;

const int N = 505;
const int MAX_SQRT = 1000;

int cnt[MAX_SQRT];
int prime[MAX_SQRT * MAX_SQRT + 1];
int arr[N][N];
int n;

void precompute() {
  for (int i = 2 ; i < MAX_SQRT ; i++)
    if (prime[i] == 0) {
      for (int j = i ; j <= MAX_SQRT * MAX_SQRT ; j += i)
        prime[j] = i;
    }
}

void read() {
  scanf("%d", &n);

  for (int i = 1 ; i <= n ; i++)
    for (int j = 1 ; j <= n ; j++)
      scanf("%d", &arr[i][j]);
}

int work() {
  arr[n][n] = 1;

  for (int i = 1 ; i <= n ; i++)
    for (int j = 1 ; j <= n ; j++) {
      int x = arr[i][j];
      while (x > 1) {
        int p = prime[x];
        cnt[p]++;
        x /= p;
      }
    }
  
  int ret = 1;
  for (int i = 2 ; i < MAX_SQRT ; i++) {
    while (cnt[i] % n != 0) {
      cnt[i]++;
      ret *= i;
    }
  }

  return ret;
}

int main() {
  precompute();
  read();
  printf("%d\n", work());
  return 0;
}
