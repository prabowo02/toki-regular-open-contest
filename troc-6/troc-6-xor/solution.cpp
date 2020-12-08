#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;
const int LOG = 30;

int n, k;
int arr[N];

void read() {
  scanf("%d %d", &n, &k);

  for (int i = 1 ; i <= n ; i++) {
    scanf("%d", &arr[i]);
  }
}

int calc(int bit) {
  int one = 0;
  int zero = 0;

  for (int i = 1 ; i <= n ; i++) {
    if (arr[i] & (1 << bit)) one++;
    else zero++;
  }

  for (int i = 0 ; i < k ; i++) {
    int nextOne = (2ll * one * zero) % MOD;
    int nextZero = (1ll * one * one + 1ll * zero * zero) % MOD;
    
    one = nextOne;
    zero = nextZero;
  }

  return 1ll * one * (1 << bit) % MOD;
}

int work() {
  int ret = 0;
  for (int i = 0 ; i < LOG ; i++) {
    ret = (ret + calc(i)) % MOD;
  }
  return ret;
}

int main() {
  read();
  printf("%d\n", work());
  return 0;
}
