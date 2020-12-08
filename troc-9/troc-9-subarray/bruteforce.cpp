#include <bits/stdc++.h>
using namespace std;

const int N = 40005;

int n, q;
int a[N];

vector<int> b;

int rights[N];

vector<int> naive_substring_search(const vector<int> &b) {
  vector<int> ret;
  for (int i = 0; i + b.size() <= n; ++i) {
    bool match = true;
    int x = b[0] ^ a[i];
    for (int j = 1; j < b.size(); ++j) {
      if ((b[j] ^ a[i+j]) != x) {
        match = false;
        break;
      }
    }

    if (match) ret.push_back(i);
  }

  return ret;
}

void solve() {
  scanf("%d %d", &n, &q);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  for (int i = 0; i < n; ++i) rights[i] = n;

  for (int i = 0; i < q; ++i) {
    int k;
    scanf("%d", &k);

    b.resize(k);
    for (int j = 0; j < k; ++j) {
      scanf("%d", &b[j]);
    }

    int cur = n, ans = 0;
    for (int idx: naive_substring_search(b)) {
      int R = min(idx + k-1, n-1);
      if (idx > cur) {
        ++ans;
        cur = R;
      } else cur = min(cur, R);

      rights[idx] = min(rights[idx], R);
    }

    if (cur < n) ++ans;
    printf("%d\n", ans);
  }

  int cur = n, ans = 0;
  for (int i = 0; i < n; ++i) {
    if (i > cur) {
      ++ans;
      cur = rights[i];
    } else {
      cur = min(cur, rights[i]);
    }
  }

  if (cur < n) ++ans;
  printf("%d\n", ans);
}

int main() {
  solve();
  return 0;
}
