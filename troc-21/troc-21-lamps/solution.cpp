#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const long long INF = 1e18;

int n, m, d;
vector<tuple<int, int, int>> edges[N];
int p[N], a[N];

long long dist[2][N];
long long risks[N];

void dijkstra(vector<int> starts, int bit, long long dist[]) {
  priority_queue<pair<long long, int>> pq;
  for (int i = 0; i < n; ++i) dist[i] = INF;
  for (int u : starts) {
    dist[u] = 0;
    pq.emplace(0, u);
  }

  while (pq.size()) {
    long long d;
    int u;
    tie(d, u) = pq.top();
    pq.pop();
    d = -d;

    if (dist[u] != d) continue;

    for (int i = 0; i < edges[u].size(); ++i) {
      int v, w, t;
      tie(v, w, t) = edges[u][i];
      if (t >> bit & 1); else continue;
      if (d + w >= dist[v]) continue;

      dist[v] = d + w;
      pq.emplace(-dist[v], v);
    }
  }
}

int main() {
  scanf("%d %d %d", &n, &m, &d);
  for (int i = 0; i < m; ++i) {
    int u, v, w, t;
    scanf("%d %d %d %d", &u, &v, &w, &t);
    --u, --v;

    edges[u].emplace_back(v, w, t);
    edges[v].emplace_back(u, w, t);
  }

  for (int i = 0; i < d; ++i) {
    scanf("%d %d", &p[i], &a[i]);
    --p[i];
  }

  for (int i = 0; i < d; ++i) risks[i] = INF;

  for (int bit = 0; bit < 17; ++bit) {
    vector<int> starts[2];
    for (int i = 0; i < d; ++i) {
      starts[a[i] >> bit & 1].push_back(p[i]);
    }

    dijkstra(starts[0], bit, dist[0]);
    dijkstra(starts[1], bit, dist[1]);

    for (int i = 0; i < d; ++i) {
      risks[i] = min(risks[i], dist[(a[i] >> bit & 1) ^ 1][p[i]]);
    }
  }

  long long ans = 0;
  for (int i = 0; i < d; ++i) {
    if (risks[i] == INF) return 0 * printf("-1\n");
    ans += risks[i];
  }
  printf("%lld\n", ans);
  return 0;
}
