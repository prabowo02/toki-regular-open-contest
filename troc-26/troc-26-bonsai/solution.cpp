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
    if ((int) larger.size() > 0 && *larger.begin() < val) {
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
    while ((int) larger.size() < k) {
      long long val = *smaller.rbegin();
      larger.insert(val);
      sumLarge += val;
      sumSmall -= val;
      smaller.erase(smaller.find(val));
    }

    while ((int) larger.size() > k) {
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

constexpr int MOD = 998244353;

vector<int> order;
void dfs(int u, int p=0) {
  dp[u] = a[u];
  par[u] = p;
  for (int v : adj[u]) {
    if (v == p) continue;
    dfs(v, u);
    values[u].insert(dp[v]);
  }
  order.push_back(u);
}

int main() {
  assert(scanf("%d", &n) == 1);
  for (int i = 0; i < n; ++i) assert(scanf("%d", &a[i]) == 1);
  for (int i = 1; i < n; ++i) {
    int p; cin >> p; p--;
    adj[p].push_back(i);
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
    ans += (values[0].size >= k ? values[0].sumKLargest(k) + a[0] : a[0]);
  }
  cout << ans << endl;
  return 0;
}