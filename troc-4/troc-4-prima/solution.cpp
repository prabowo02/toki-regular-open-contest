#include <bits/stdc++.h>
using namespace std;

int main() {
  set<int> s = {2, 3, 5, 7};
  for (int i = 0; i < 3; ++i) {
    int x; scanf("%d", &x);
    s.erase(x);
  }
  printf("%d\n", *s.begin());
  return 0;
}
