#include <bits/stdc++.h>
using namespace std;

const int N = 20205;
const int K = 20;

const int INF = 1e9 + 5;
constexpr long long INFLL = 1LL * INF * INF;

int n, m, k;
long long s[N];
vector<int> edges[N], weights[N];
int p[K]; long long c[K];

long long sumS;

struct Dinic {
  int s, t;
  vector<int> edges[N], rev[N];
  vector<long long> cap[N];
  int dist[N], it[N];
  
  void addEdge(int u, int v, long long c) {
    if (u == v) return;
    
    rev[u].push_back(edges[v].size());
    cap[u].push_back(c);
    edges[u].push_back(v);
    
    rev[v].push_back((int) edges[u].size() - 1);
    cap[v].push_back(0LL);
    edges[v].push_back(u);
  }
  
  bool bfs() {
    queue<int> q;
    q.push(s);
    
    for (int i=0; i<=t; i++) dist[i] = -1;
    dist[s] = 0;
    
    while (q.size()) {
      int u = q.front();
      q.pop();
      
      for (int i=0; i<edges[u].size(); i++) {
        int v = edges[u][i];
        long long c = cap[u][i];
        if (dist[v] >= 0 || c == 0) continue;
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
    
    return dist[t] >= 0;
  }
  
  long long dfs(int u, long long f) {
    if (u == t) return f;
    for (; it[u]<edges[u].size(); ++it[u]) {
      int i = it[u];
      int v = edges[u][i];
      long long c = cap[u][i];
      if (dist[v] == dist[u] + 1 && c > 0) {
        long long flow = dfs(v, min(f, c));
        if (flow > 0) {
          cap[u][i] -= flow;
          cap[v][rev[u][i]] += flow;
          return flow;
        }
      }
    }
    
    return 0LL;
  }
  
  long long maxflow() {
    long long ret = 0;
    while (bfs()) {
      for (int i=0; i<=t; i++) it[i] = 0;
      while (long long flow = dfs(s, INF)) {
        ret += flow;
      }
    }
    
    return ret;
  }
};

int dist[K][N];
void dijkstra(int u, int dist[]) {
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  vector<bool> vis(n, false);

  pq.push({0, u});

  while (pq.size()) {
    int u = pq.top().second;
    int d = pq.top().first;
    pq.pop();

    if (vis[u]) continue;
    vis[u] = true;
    dist[u] = d;

    for (int i = 0; i < edges[u].size(); ++i) {
      int v = edges[u][i];
      int w = weights[u][i];

      if (vis[v]) continue;
      pq.push({d + w, v});
    }
  }
}

void read() {
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%lld", s + i);
  }

  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    --u, --v;

    edges[u].push_back(v);
    weights[u].push_back(w);

    edges[v].push_back(u);
    weights[v].push_back(w);
  }

  for (int i = 0; i < k; ++i) {
    scanf("%d %lld", p + i, c + i);
    --p[i];
  }
}

void init() {
  for (int i = 0; i < k; ++i) {
    dijkstra(p[i], dist[i]);
  }

  sumS = 0;
  for (int i = 0; i < n; ++i) sumS += s[i];
}

bool check(int d) {
  Dinic dinic;
  dinic.s = 0, dinic.t = n + k + 1;
  for (int i = 0; i < n; ++i) {
    dinic.addEdge(dinic.s, i + 1, s[i]);
  }
  for (int i = 0; i < k; ++i) {
    dinic.addEdge(n + i + 1, dinic.t, c[i]);
  }

  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < n; ++j) {
      if (dist[i][j] <= d) {
        dinic.addEdge(j+1, n+i+1, INFLL);
      }
    }
  }

  return dinic.maxflow() == sumS;
}

void solve() {
  int l = 0, r = INF, ans = -1;
  while (l <= r) {
    int mid = l + r >> 1;
    if (check(mid)) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }

  printf("%d\n", ans);
}

int main() {
  read();
  init();
  solve();
  return 0;
}
