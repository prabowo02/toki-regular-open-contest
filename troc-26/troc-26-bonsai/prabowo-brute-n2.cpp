#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n;
int a[N];
vector<int> adj[N];

int k;
long long dfs(int u) {
  vector<long long> vals;
  for (int v : adj[u]) {
    vals.push_back(dfs(v));
  }
  if (vals.size() < k) return a[u];

  sort(vals.begin(), vals.end(), greater<long long>());
  long long ret = a[u];
  for (int i = 0; i < k; ++i) ret += vals[i];
  return ret;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  for (int i = 1; i < n; ++i) {
    int p;
    scanf("%d", &p);
    adj[--p].push_back(i);
  }

  for (k = 1; k <= n; ++k) {
    printf("%lld\n", dfs(0));
  }
  return 0;
}
