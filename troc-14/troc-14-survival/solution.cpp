#include <cstdio>

const int N = 200005;

int n, d;
int t[N], r[N], c[N];

bool check(int s) {
  int cur = s, lst = 1;
  for (int i = 0; i < n; ++i) {
    cur -= t[i] - lst;
    lst = t[i];

    if (cur < 0) return false;

    if (cur <= r[i]) cur += c[i];
    else if (r[i] + c[i] > cur) cur = r[i] + c[i];
  }

  cur -= d - lst + 1;
  if (cur < 0) return false;
  return true;
}

int main() {
  scanf("%d %d", &n, &d);

  for (int i = 0; i < n; ++i) {
    scanf("%d %d %d", &t[i], &r[i], &c[i]);
  }

  int l = 0, r = 1000000000, ans = -1;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (check(mid)) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }

  printf("%d\n", ans);
  return 0;
}
