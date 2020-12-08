#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

char s[N];

int main() {
  scanf("%s", s);

  sort(s, s + strlen(s));

  int b = upper_bound(s, s + strlen(s), 'b') - lower_bound(s, s + strlen(s), 'b');
  int o = upper_bound(s, s + strlen(s), 'o') - lower_bound(s, s + strlen(s), 'o');
  int n = upper_bound(s, s + strlen(s), 'n') - lower_bound(s, s + strlen(s), 'n');

  printf("%d\n", max(0, min(b, min(o, n)) - 1));
  return 0;
}
