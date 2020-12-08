#include <cstdio>
#include <algorithm>

int n;
char s[105];

int main() {
  scanf("%d", &n);
  scanf("%s", s);
  s[std::unique(s, s + n) - s] = 0;
  printf("%s\n", s);
  return 0;
}
