#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n;
int a[N];
vector<int> adj[N];

struct Value {
  int size;
  long long sumLarge, sumSmall;
  multiset<long long> larger, smaller;

  void insert(long long val) {
    ++size;
    if (larger.size() > 0 && *larger.begin() < val) {
      larger.insert(val);
      sumLarge += val;
    } else {
      smaller.insert(val);
      sumSmall += val;
    }
  }

  void erase(long long val) {
    --size;
    auto it = larger.find(val);
    if (it != larger.end()) {
      larger.erase(it);
      sumLarge -= val;
    } else {
      smaller.erase(smaller.find(val));
      sumSmall -= val;
    }
  }

  long long sumKLargest(int k) {
    while (larger.size() < k) {
      long long val = *smaller.rbegin();
      larger.insert(val);
      sumLarge += val;
      sumSmall -= val;
      smaller.erase(smaller.find(val));
    }

    while (larger.size() > k) {
      long long val = *larger.begin();
      smaller.insert(val);
      sumLarge -= val;
      sumSmall += val;
      larger.erase(larger.begin());
    }

    return sumLarge;
  }
};

long long dp[N];
int par[N];
Value values[N];

vector<int> order;
void dfs(int u) {
  dp[u] = a[u];
  for (int v : adj[u]) {
    dfs(v);
    values[u].insert(dp[v]);
  }
  order.push_back(u);
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  for (int i = 1; i < n; ++i) {
    scanf("%d", &par[i]);
    adj[--par[i]].push_back(i);
  }

  dfs(0);

  long long ans = 0;
  for (int k = 1; k <= n; ++k) {
    vector<int> norder;
    for (int u : order) {
      if (u == 0) continue;
      if (values[u].size < k) {
        values[par[u]].erase(dp[u]);
        values[par[u]].insert(dp[u] = a[u]);
      } else {
        norder.push_back(u);
        values[par[u]].erase(dp[u]);
        values[par[u]].insert(dp[u] = values[u].sumKLargest(k) + a[u]);
      }
    }
    order = norder;
    ans += a[0] + (values[0].size >= k ? values[0].sumKLargest(k) : 0);
  }
  printf("%lld\n", ans);
  return 0;
}
