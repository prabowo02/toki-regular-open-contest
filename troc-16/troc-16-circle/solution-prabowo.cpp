#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int M = 200005;
const int MOD = 1000000007;
const long long INFLL = 5e14;

int n, m;
int w[N];

vector<tuple<int, int, long long>> edges;

void triangulate(vector<tuple<int, int, long long>> &edges) {
  set<pair<int, int>> sedges;
  vector<int> deg(n);
  for (tuple<int, int, long long> edge: edges) {
    int u, v; long long w;
    tie(u, v, w) = edge;
    sedges.insert({u, v});
    sedges.insert({v, u});
    ++deg[u], ++deg[v];
  }

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  vector<int> lft(n), rgt(n);
  for (int i = 0; i < n; ++i) {
    pq.emplace(deg[i], i);
    lft[i] = (i + n - 1) % n;
    rgt[i] = (i + 1) % n;
  }

  vector<bool> removed(n);
  for (int rem = 0; rem < n - 3; ) {
    int u = pq.top().second;
    pq.pop();
    if (removed[u]) continue;

    ++rem; assert(deg[u] == 2);
    removed[u] = true;
    int l = lft[u], r = rgt[u];

    if (sedges.find({l, r}) == sedges.end()) {
      edges.emplace_back(l, r, INFLL);
    } else {
      pq.push({--deg[l], l});
      pq.push({--deg[r], r});
    }

    rgt[l] = r; lft[r] = l;
  }
}

int inodes[N];
vector<long long> dijkstra(int u, const vector<int> &nodes, const vector<tuple<int, int, long long>> &edges) {
  vector<vector<pair<int, long long>>> adj(nodes.size());
  for (tuple<int, int, long long> edge: edges) {
    int u, v; long long w;
    tie(u, v, w) = edge;
    u = inodes[u], v = inodes[v];

    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  vector<long long> dist(nodes.size(), INFLL);
  dist[inodes[u]] = 0;
  priority_queue<pair<long long, int>> pq;
  pq.emplace(0LL, inodes[u]);
  while (pq.size()) {
    long long d; int u;
    tie(d, u) = pq.top();
    d = -d;
    pq.pop();

    if (dist[u] < d) continue;

    for (pair<int, long long> p: adj[u]) {
      int v; long long w;
      tie(v, w) = p;
      if (dist[u] + w >= dist[v]) continue;
      dist[v] = dist[u] + w;
      pq.emplace(-dist[v], v);
    }
  }

  return dist;
}

int dnc(vector<int> nodes, vector<tuple<int, int, long long>> edges) {
  assert(nodes.size() >= 3);
  if (nodes.size() == 3) {
    assert(edges.size() == 3);
    long long d0 = get<2>(edges[0]), d1 = get<2>(edges[1]), d2 = get<2>(edges[2]);
    return (min(d0, d1 + d2) + min(d1, d0 + d2) + min(d2, d0 + d1)) % MOD;
  }

  for (int i = 0; i < nodes.size(); ++i) {
    inodes[nodes[i]] = i;
  }

  int du = -1, dv = -1; // divide nodes
  function<int(int, int)> len = [&](int u, int v) {
    return max(abs(u - v), (int) nodes.size() - abs(u - v));
  };
  for (tuple<int, int, long long> edge: edges) {
    int u, v; long long w;
    tie(u, v, w) = edge;
    u = inodes[u], v = inodes[v];

    if (du == -1 || len(u, v) < len(du, dv)) {
      du = u, dv = v;
    }
  }
  if (dv < du) swap(du, dv);
  // cerr << "Split: " << nodes[du] << " " << nodes[dv] << " " << len(du, dv) << endl;

  vector<int> lnodes, rnodes;
  for (int node: nodes) {
    node = inodes[node];
    if (du <= node && node <= dv) {
      lnodes.push_back(nodes[node]);
    }
    if (node <= du || dv <= node) {
      rnodes.push_back(nodes[node]);
    }
  }
  // cerr << "Lnodes: "; for (int u: lnodes) cerr << nodes[u] << " "; cerr << endl;
  // cerr << "Rnodes: "; for (int u: rnodes) cerr << nodes[u] << " "; cerr << endl;

  vector<long long> distU = dijkstra(nodes[du], nodes, edges);
  vector<long long> distV = dijkstra(nodes[dv], nodes, edges);

  // cerr << "Dijkstra" << endl;
  // cerr << "DistU: "; for (long long d: distU) cerr << d << " "; cerr << endl;
  // cerr << "DistV: "; for (long long d: distV) cerr << d << " "; cerr << endl;

  vector<tuple<int, int, long long>> ledges, redges;
  for (tuple<int, int, long long> edge: edges) {
    int u, v; long long w;
    tie(u, v, w) = edge;
    u = inodes[u], v = inodes[v];

    if (u == du && v == dv || u == dv && v == du) w = distU[dv];

    if (du <= u && u <= dv && du <= v && v <= dv) {
      ledges.emplace_back(nodes[u], nodes[v], w);
    }
    if ((u <= du || dv <= u) && (v <= du || dv <= v)) {
      redges.emplace_back(nodes[u], nodes[v], w);
    }
  }

  // dist(u, du) + dist(v, du) < dist(u, dv) + dist(v, dv)
  // dist(u, du) - dist(u, dv) < dist(v, dv) - dist(v, du)

  vector<pair<long long, int>> distDu, distDv;
  for (int u: lnodes) {
    u = inodes[u];
    if (u == du || u == dv) continue;
    distDu.emplace_back(distU[u] - distV[u], u);
  }
  for (int u: rnodes) {
    u = inodes[u];
    if (u == du || u == dv) continue;
    distDv.emplace_back(distV[u] - distU[u], u);
  }
  sort(distDu.begin(), distDu.end());
  sort(distDv.begin(), distDv.end());

  vector<int> pre, suf;
  for (int i = 0; i < distDv.size(); ++i) {
    int u = distDv[i].second;
    pre.push_back(distV[u] % MOD); suf.push_back(distU[u] % MOD);
  }
  for (int i = 1; i < distDv.size(); ++i) (pre[i] += pre[i-1]) %= MOD;
  for (int i = (int) distDv.size() - 2; i >= 0; --i) (suf[i] += suf[i+1]) %= MOD;
  suf.push_back(0);

  long long ret = 0LL;
  for (int i = 0; i < distDu.size(); ++i) {
    int u = distDu[i].second;
    int idx = lower_bound(distDv.begin(), distDv.end(), make_pair(distDu[i].first, -1)) - distDv.begin();
    ret += (1LL * idx * (distV[u] % MOD) + 1LL * ((int) distDv.size() - idx) * (distU[u] % MOD)) % MOD;
    ret += (idx > 0 ? pre[idx - 1] : 0) + suf[idx];
  }

  ret = (ret + dnc(lnodes, ledges) + dnc(rnodes, redges) - distU[dv]) % MOD;
  if (ret < 0) ret += MOD;

  return ret;
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &w[i]);
  }
  for (int i = 0; i < m; ++i) {
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    --x, --y;

    if (x + 1 == y) {
      w[x] = min(w[x], z);
    } else if (x == 0 && y == n - 1) {
      w[n - 1] = min(w[n - 1], z);
    } else {
      edges.emplace_back(x, y, z);
    }
  }
  for (int i = 0; i < n; ++i) {
    edges.emplace_back(i, (i + 1) % n, w[i]);
  }

  vector<int> nodes(n);
  iota(nodes.begin(), nodes.end(), 0);

  triangulate(edges);

  printf("%d\n", dnc(nodes, edges));
  return 0;
}
