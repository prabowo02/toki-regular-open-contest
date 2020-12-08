#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  scanf("%d", &n);

  int a, b, c, d, e, f, g, h, x;
  if (n == 1) {
    scanf("%d", &a);
    scanf("%d", &x);
    if (a == x) printf("1\n");
  } else if (n == 2) {
    scanf("%d %d", &a, &b);
    scanf("%d", &x);
    if (a == x) printf("1\n");
    else if (b == x) printf("2\n");
  } else if (n == 3) {
    scanf("%d %d %d", &a, &b, &c);
    scanf("%d", &x);
    if (a == x) printf("1\n");
    else if (b == x) printf("2\n");
    else if (c == x) printf("3\n");
  } else if (n == 4) {
    scanf("%d %d %d %d", &a, &b, &c, &d);
    scanf("%d", &x);
    if (a == x) printf("1\n");
    else if (b == x) printf("2\n");
    else if (c == x) printf("3\n");
    else if (d == x) printf("4\n");
  } else if (n == 5) {
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
    scanf("%d", &x);
    if (a == x) printf("1\n");
    else if (b == x) printf("2\n");
    else if (c == x) printf("3\n");
    else if (d == x) printf("4\n");
    else if (e == x) printf("5\n");
  } else if (n == 6) {
    scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
    scanf("%d", &x);
    if (a == x) printf("1\n");
    else if (b == x) printf("2\n");
    else if (c == x) printf("3\n");
    else if (d == x) printf("4\n");
    else if (e == x) printf("5\n");
    else if (f == x) printf("6\n");
  } else if (n == 7) {
    scanf("%d %d %d %d %d %d %d", &a, &b, &c, &d, &e, &f, &g);
    scanf("%d", &x);
    if (a == x) printf("1\n");
    else if (b == x) printf("2\n");
    else if (c == x) printf("3\n");
    else if (d == x) printf("4\n");
    else if (e == x) printf("5\n");
    else if (f == x) printf("6\n");
    else if (g == x) printf("7\n");
  } else if (n == 8) {
    scanf("%d %d %d %d %d %d %d %d", &a, &b, &c, &d, &e, &f, &g, &h);
    scanf("%d", &x);
    if (a == x) printf("1\n");
    else if (b == x) printf("2\n");
    else if (c == x) printf("3\n");
    else if (d == x) printf("4\n");
    else if (e == x) printf("5\n");
    else if (f == x) printf("6\n");
    else if (g == x) printf("7\n");
    else if (h == x) printf("8\n");
  }

  return 0;
}