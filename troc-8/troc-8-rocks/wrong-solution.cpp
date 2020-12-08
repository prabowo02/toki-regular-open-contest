#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int l, m, k;
char t[2005];
int pre[2005];

int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }

  return ret;
}

int main() {
  scanf("%d %d %d", &l, &m, &k);
  scanf("%s", t + 1);

  for (int i = 1; i <= l; ++i) {
    if (t[i] == 'b') {
      pre[i] = pre[i-1] + 3;
    } else if (t[i] == 'o') {
      pre[i] = pre[i-1] + 2;
    } else if (t[i] == 'n') {
      pre[i] = pre[i-1] + 1;
    }
  }

  int det = power(1LL * pre[l] * m % MOD, MOD - 2);

  while (k--) {
    long long b;
    scanf("%lld", &b);

    long long num = b / 3 / l * pre[l] + pre[b / 3 % l];
    char c = t[b / 3 % l + 1];

    if (c == 'b') {
      if (b % 3 == 1) num += 2;
      else if (b % 3 == 2) num += 1;
    } else if (c == 'o') {
      if (b % 3 == 1 || b % 3 == 2) num += 1;
    } else if (c == 'n') {
      if (b % 3 == 2) num += 1;
    }

    num %= MOD;

    printf("%lld\n", 1LL * num * det % MOD);
  }

  return 0;
}
