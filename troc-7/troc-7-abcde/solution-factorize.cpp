#include <bits/stdc++.h>
using namespace std;

const int N = 5;

int a[N];
int ans[N];

int main() {
  for (int i = 0; i < N; ++i) {
    scanf("%d", a + i);
  }

  for (int i = 1; i <= 8; ++i) {
    if (a[0] % i != 0) continue;

    bool ok = true;

    ans[0] = i;
    for (int i = 1; i < N; ++i) {
      ans[i] = a[i-1] / ans[i-1];

      if (a[i] % ans[i] != 0) {
        ok = false;
        break;
      }
    }

    if (!ok) continue;
    if (a[N-1] != i * ans[N-1]) continue;

    for (int i = 0; i < N; ++i) {
      if (i > 0) printf(" ");
      printf("%d", ans[i]);
    }
    printf("\n");
    return 0;
  }

  printf("-1\n");
  return 0;
}
