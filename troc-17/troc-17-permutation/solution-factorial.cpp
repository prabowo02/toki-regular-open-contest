// O(N! * NK)

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
const int MOD = 998244353;

int n, k;
int t[MAXN], a[MAXN];

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 0; i < k; ++i) {
    scanf("%d %d", &t[i], &a[i]);
    --a[i];
  }
  
  vector<int> p(n);
  iota(p.begin(), p.end(), 0);
  int ans = 0;
  do {
    bool okay = true;
    for (int i = 0; i < k; ++i) {
      for (int j = 0; j < a[i]; ++j) {
        if (t[i] == 0 && p[j] > p[a[i]] || t[i] == 1 && p[j] < p[a[i]]) {
          okay = false;
          break;
        }
      }
      if (!okay) break;
    }

    if (okay) ++ans;
  } while (next_permutation(p.begin(), p.end()));

  printf("%d\n", ans);
  return 0;
}
