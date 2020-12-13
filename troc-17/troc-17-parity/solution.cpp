#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; scanf("%d" , &n);

  int ans = 0;
  for (int i = 0 ; i < n ; i++) {
    int base; scanf("%d" , &base);
    ans ^= base & 1;
  }

  for (int i = 0 ; i < n ; i++) {
    int ex; scanf("%d" , &ex);
  }

  printf("%d\n" , ans);
}
