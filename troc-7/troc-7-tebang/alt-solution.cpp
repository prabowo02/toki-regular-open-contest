#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n;
vector<int> edges[N];

int prv[N]; bool vis[N];
pair<int, int> bfs(int u) {
  queue<int> q;
  q.push(u);
  vis[u] = true;

  int lst;
  while (q.size()) {
    int u = q.front();
    q.pop();
    lst = u;

    for (int v: edges[u]) {
      if (vis[v]) continue;
      vis[v] = true;
      q.push(v);
      prv[v] = u;
    }
  }

  pair<int, int> ret = {lst, 0};
  while (lst != u) {
    ++ret.second;
    lst = prv[lst];
  }

  return ret;
}

vector<int> diameter() {
  int d1 = bfs(0).first;
  for (int i = 0; i < n; ++i) vis[i] = false;
  int d2 = bfs(d1).first;
  for (int i = 0; i < n; ++i) vis[i] = false;

  vector<int> ret;
  while (d1 != d2) {
    ret.push_back(d2);
    d2 = prv[d2];
  }
  ret.push_back(d2);

  return ret;
}

void erase_diameter(const vector<int> &d) {
  for (int i = 1; i < d.size(); ++i) {
    for (int j = 0; j < edges[d[i-1]].size(); ++j) {
      if (edges[d[i-1]][j] == d[i]) {
        edges[d[i-1]][j] = edges[d[i-1]].back();
        edges[d[i-1]].pop_back();
        break;
      }
    }

    for (int j = 0; j < edges[d[i]].size(); ++j) {
      if (edges[d[i]][j] == d[i-1]) {
        edges[d[i]][j] = edges[d[i]].back();
        edges[d[i]].pop_back();
        break;
      }
    }
  }
}

int d1[N], d2[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;

    edges[u].push_back(v);
    edges[v].push_back(u);
  }

  vector<int> d = diameter();
  erase_diameter(d);

  // Try deleting every edge from diameter

  for (int i = 0; i < d.size(); ++i) {
    int dist = bfs(d[i]).second;
    d1[i] = i + dist;
    d2[i] = (int) d.size() - 1 - i + dist;
  }

  for (int i = 1; i < d.size(); ++i) {
    d1[i] = max(d1[i], d1[i-1]);
    d2[(int) d.size() - i - 1] = max(d2[(int) d.size() - i - 1], d2[(int) d.size() - i]);
  }

  int ans = n;
  for (int i = 1; i < d.size(); ++i) {
    ans = min(ans, max(d1[i-1], d2[i]));
  }
  printf("%d\n", ans);

  return 0;
}
