#include <bits/stdc++.h>
using namespace std;

const int N = 30;

char s[N], t[N];
int cnt[N];

int main() {
  scanf("%s", s);
  scanf("%s", t);

  for (int i = 0; i < strlen(t); ++i) {
    cnt[t[i] - 'A'] += 1;
  }

  int ans = 1;
  for (int i = 0; i < strlen(t); ++i) {
    ans = 1LL * ans * (cnt[t[i] - 'A'] + 1) % 1000000007;
  }

  printf("%d\n", ans);
  return 0;
}
