#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int n;
int a[N];
int b[N];

int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = ret * x;
    x = x * x;
  }
  return ret;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  for (int i = 0; i < n; ++i) scanf("%d", &b[i]);

  int sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += power(a[i], b[i]);
  }
  printf("%d\n", sum & 1);
  return 0;
}
