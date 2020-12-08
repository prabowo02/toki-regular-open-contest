#include <cstdio>

int n, m, r;

int main() {
  scanf("%d %d %d", &n, &m, &r);
  printf("%d\n", ((n < m ? n : m) + r*2) / (r*2 + 1));
}
