#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, m, k;
vector<pair<int, int>> edges[N];
int p[N], a[N];

int enroll[N];
int school[N];
int dist[N];

void dijkstra() {
  priority_queue<tuple<int, int, int>> pq; // dist, source, cur
  for (int i = 0; i < n; ++i) {
    school[i] = n;
    pq.emplace(0, -i, i);
  }

  vector<pair<int, int>> students(k);
  for (int i = 0; i < k; ++i) {
    students[i] = make_pair(a[i], i);
  }
  sort(students.begin(), students.end(), greater<pair<int, int>>());

  while (pq.size()) {
    int d, s, u;
    tie(d, s, u) = pq.top();
    pq.pop();
    d = -d; s = -s;

    if (s > school[u] || (s == school[u] && d >= dist[u])) continue;

    while (students.size() > 0 && students.back().first < d) {
      int i = students.back().second;
      enroll[i] = school[p[i]];
      students.pop_back();

    }

    dist[u] = d; school[u] = s;

    for (int i = 0; i < edges[u].size(); ++i) {
      int v, w;
      tie(v, w) = edges[u][i];
      int nd = dist[u] + w;

      if (s < school[v] || (s == school[v] && nd < dist[v])) {
        pq.emplace(-nd, -s, v);
      }
    }
  }

  while (students.size() > 0) {
    int i = students.back().second;
    enroll[i] = school[p[i]];
    students.pop_back();
  }
}

int main() {
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    --u, --v;
    edges[u].emplace_back(v, w);
    edges[v].emplace_back(u, w);
  }

  for (int i = 0; i < k; ++i) {
    scanf("%d %d", &p[i], &a[i]);
    --p[i];
  }

  dijkstra();

  int ans = -1, school = -1;
  for (int i = 0; i < k; ++i) {
    if (enroll[i] >= school) {
      school = enroll[i];
      ans = i;
    }
  }

  printf("%d\n", ans + 1);
  return 0;
}
