#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int A = 100005;
const int MOD = 1000000007;

int n;
int a[N];

int power(int x, long long y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }
  return ret;
}

int largestPrimes[A];
vector<int> primes;
void sieve() {
  for (int i = 2; i < A; ++i) {
    if (largestPrimes[i]) continue;
    for (int j = i; j < A; j += i) {
      largestPrimes[j] = i;
    }
    primes.push_back(i);
  }
}

vector<int> primePos[A];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

  sieve();
  
  for (int i = 0; i < n; ++i) {
    int num = a[i];
    while (num > 1) {
      int p = largestPrimes[num], pe = 1;
      do {
        num /= p;
        primePos[pe *= p].push_back(i);
      } while (num % p == 0);
    }
  }
  
  int ans = 1;
  for (int p: primes) {
    for (long long pe = p; pe < A; pe *= p) {
      long long cnt = 1LL * n * (n + 1) / 2;
      int lst = -1;
      for (int pos: primePos[pe]) {
        cnt -= 1LL * (pos - lst) * (pos - lst - 1) / 2;
        lst = pos;
      }
      cnt -= 1LL * (n - lst) * (n - lst - 1) / 2;

      ans = 1LL * ans * power(p, cnt) % MOD;
    }
  }

  printf("%d\n", ans);
  return 0;
}
