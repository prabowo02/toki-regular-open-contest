#include <bits/stdc++.h>
using namespace std;
const int M = 998244353;
const int ELM_MAX = 2005;
int n;

int main() {

  scanf("%d" , &n);
  vector <int> v(n + 1);
  vector <int> freq(ELM_MAX);
  for (int i = 1 ; i <= n ; i++) {
    scanf("%d" , &v[i]);
    freq[v[i]]++;
  }

  bool duplicate = 0;
  for (int i = 1 ; i <= ELM_MAX ; i++) {
    if (freq[i] > 1) duplicate = 1;
  }

  if (duplicate) {
    puts("0");
  } else {
    long long ans = 1;
    for (int i = 1 ; i <= n ; i++) {
      for (int j = i + 1 ; j <= n ; j++) {
        (ans *= (v[i] ^ v[j])) %= M;
      }
    }
    printf("%lld\n" , ans);
  }

  return 0;
}
