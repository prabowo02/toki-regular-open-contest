#include <cstdio>

int main() {
  int n, d;
  scanf("%d %d", &n, &d);

  int ans = 0, cur = 0, lst = 1;
  for (int i = 0; i < n; ++i) {
    int t, r, c;
    scanf("%d %d %d", &t, &r, &c);
    cur -= t - lst;
    lst = t;

    if (cur < 0) {
      ans += -cur;
      cur = 0;
    }

    if (cur <= r) cur += c;
    else if (r + c > cur) cur = r + c;
  }

  cur -= d - lst + 1;
  if (cur < 0) ans += -cur;

  printf("%d\n", ans);
  return 0;
}
