#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n;
int a[N];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

  if (n <= 4 || unique(a, a + n) - a <= 3) printf("YeS\n");
  else printf("No\n");
  return 0;
}
