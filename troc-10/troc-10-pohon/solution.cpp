#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n;
int w[N];
vector<int> edges[N];

vector<int> leaves[N];
vector<pair<int, int>> ans;

void dfs(int u, int p=-1) {
  bool leaf = true;
  auto compareLeafSize = [&](int u, int v) {
    return leaves[u].size() < leaves[v].size();
  };
  priority_queue<int, vector<int>, decltype(compareLeafSize)> pq(compareLeafSize);
  int sz = 0;

  for (int v: edges[u]) {
    if (v == p) continue;

    leaf = false;
    dfs(v, u);
    sz += leaves[v].size();
    if (leaves[v].size() > 0) pq.push(v);
  }

  if (leaf) {
    leaves[u] = vector<int>(w[u], u);
    return;
  }

  while (sz > w[u]) {
    assert(pq.size() >= 2);
    int v1 = pq.top(); pq.pop();
    int v2 = pq.top(); pq.pop();

    ans.emplace_back(leaves[v1].back(), leaves[v2].back());
    --sz;
    leaves[v1].pop_back();
    leaves[v2].pop_back();

    if (leaves[v1].size() > 0) pq.push(v1);
    if (leaves[v2].size() > 0) pq.push(v2);
  }

  // small-to-large
  if (pq.size() > 0) {
    swap(leaves[u], leaves[pq.top()]);
    pq.pop();

    while (pq.size() > 0) {
      int v = pq.top(); pq.pop();
      for (int leaf: leaves[v]) leaves[u].push_back(leaf);
      leaves[v].clear();
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;

    edges[u].push_back(v);
    edges[v].push_back(u);
  }

  for (int i = 0; i < n; ++i) scanf("%d", &w[i]);

  dfs(0);

  assert(leaves[0].size() == 0);

  printf("%d\n", (int) ans.size());
  for (pair<int, int> p: ans) {
    printf("%d %d\n", p.first + 1, p.second + 1);
  }
  return 0;
}
