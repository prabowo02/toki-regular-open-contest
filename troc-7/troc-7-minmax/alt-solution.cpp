#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n;
int l[N], r[N];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", l + i);
  for (int i = 0; i < n; ++i) scanf("%d", r + i);

  long long diff = 0;
  for (int i = 0; i < n; ++i) diff += r[i] - l[i];
  if (diff < 2) return 0 * printf("-1\n");

  diff = 0;
  for (int i = 0; i < n; ++i) {
    if (i > 0) printf(" ");
    if (l[i] != r[i] && diff == 0) printf("%d", l[i] + 1), ++diff;
    else printf("%d", l[i]);
  }

  printf("\n");
  return 0;
}
