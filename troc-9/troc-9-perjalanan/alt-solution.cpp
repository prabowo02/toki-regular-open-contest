#pragma GCC diagnostic ignored "-Wshift-op-parentheses"

#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, q;
pair<char, char> roads[N];

vector<int> edges[N];

struct Node {
  // Cost if starts from lane A/B
  int mini[2];
  // Lane you ends up with if you start from lane A/B
  int lane[2];
  int lazy, same;

  Node() {
    mini[0] = mini[1] = lazy = same = 0;
    lane[0] = 0, lane[1] = 1;
  }

  void toggle() {
    lazy ^= 1;
    swap(mini[0], mini[1]);
    if (lane[0] == lane[1]) lane[0] ^= 1, lane[1] ^= 1;
    mini[0] += same * 3, mini[1] += same * 3;
    same = -same;
  }
};

Node operator + (const Node &v, const Node &u) {
  Node ret;
  ret.lazy = 0;
  ret.same = v.same + u.same;

  for (int i = 0; i < 2; ++i) {
    tie(ret.mini[i], ret.lane[i]) = min(
      min(
        make_pair(u.mini[i] + v.mini[u.lane[i]], v.lane[u.lane[i]]),
        make_pair(u.mini[i] + 1 + v.mini[u.lane[i]^1], v.lane[u.lane[i]^1])
      ),
      min(
        make_pair(1 + u.mini[i^1] + v.mini[u.lane[i^1]], v.lane[u.lane[i^1]]),
        make_pair(1 + u.mini[i^1] + 1 + v.mini[u.lane[i^1]^1], v.lane[u.lane[i^1]^1])
      )
    );
  }
  return ret;
}

struct SegTree {
  Node nodes[N << 2];
  
  void propagate(int node) {
    if (nodes[node].lazy == 0) return;
    
    nodes[node*2 + 1].toggle();
    nodes[node*2 + 2].toggle();
    
    nodes[node].lazy = 0;
  }

  void update(int node, int l, int r, int x, pair<char, char> road) {
    if (l > x || r < x) return;
    if (l == x && r == x) {
      nodes[node].lane[0] = 0;
      nodes[node].lane[1] = 1;

      if (road.first == 'a' && road.second == 'b') {
        nodes[node].mini[0] = nodes[node].mini[1] = 5;
        nodes[node].same = -1;
      } else {
        nodes[node].mini[0] = nodes[node].mini[1] = 2;
        nodes[node].same = 1;
        if (road.first == 'a') {
          ++nodes[node].mini[0];
          nodes[node].lane[0] = 1;
          nodes[node].same = 0;
        }
        if (road.second == 'b') {
          ++nodes[node].mini[1];
          nodes[node].lane[1] = 0;
          nodes[node].same = 0;
        }
      }

      if (nodes[node].lazy) {
        nodes[node].toggle();
        nodes[node].lazy ^= 1;
      }
      return;
    }

    propagate(node);

    int mid = l + r >> 1;

    update(node*2 + 1, l, mid+0, x, road);
    update(node*2 + 2, mid+1, r, x, road);
    nodes[node] = nodes[node*2 + 1] + nodes[node*2 + 2];
  }

  void toggle(int node, int l, int r, int a, int b) {
    if (l > b || r < a) return;
    if (l >= a && r <= b) {
      nodes[node].toggle();
      return;
    }

    propagate(node);

    int mid = l + r >> 1;

    toggle(node*2 + 1, l, mid+0, a, b);
    toggle(node*2 + 2, mid+1, r, a, b);

    nodes[node] = nodes[node*2 + 1] + nodes[node*2 + 2];
  }

  Node query(int node, int l, int r, int a, int b) {
    if (l > b || r < a) return Node();
    if (l >= a && r <= b) return nodes[node];

    propagate(node);

    int mid = l + r >> 1;

    return query(node*2 + 1, l, mid+0, a, b) + query(node*2 + 2, mid+1, r, a, b);
  }

  void update(int x, pair<int, int> road) {
    update(0, 1, n-1, x, road);
  }

  void toggle(int l, int r) {
    toggle(0, 1, n-1, l, r);
  }

  Node query(int l, int r) {
    return query(0, 1, n-1, l, r);
  }
};

struct HLD {
  SegTree tree;

  int heavy[N], head[N], cnt[N], depth[N], idx[N], par[N];

  void dfs(int u, int p) {
    par[u] = p; 
    heavy[u] = -1;
    cnt[u] = 1;

    for (int v: edges[u]) {
      depth[v] = depth[u] + 1;

      dfs(v, u);

      cnt[u] += cnt[v];
      if (heavy[u] == -1 || cnt[v] > cnt[heavy[u]]) {
        heavy[u] = v;
      }
    }
  }

  void build() {
    depth[0] = 0;
    dfs(0, 0);

    int cur = 0;
    for (int i=0; i<n; i++) {
      if (i == 0 || heavy[par[i]] != i) {
        for (int j=i; j!=-1; j=heavy[j]) {
          head[j] = i;
          idx[j] = cur++;

          tree.update(idx[j], roads[j]);
        }
      }
    }
  }

  void update(int x) {
    tree.update(idx[x], roads[x]);
  }

  void toggle(int u, int v) {
    while (head[u] != head[v]) {
      if (depth[head[u]] < depth[head[v]]) swap(u, v);

      tree.toggle(idx[head[u]], idx[u]);

      u = par[head[u]];
    }

    if (depth[u] < depth[v]) swap(u, v);

    tree.toggle(idx[v]+1, idx[u]);
  }

  Node query(int u, int v) {
    Node ret;
    while (head[u] != head[v]) {
      if (depth[head[u]] < depth[head[v]]) swap(u, v);

      ret = tree.query(idx[head[u]], idx[u]) + ret;

      u = par[head[u]];
    }

    if (depth[u] < depth[v]) swap(u, v);
    return tree.query(idx[v]+1, idx[u]) + ret;
  }

  int lca(int u, int v) {
    while (head[u] != head[v]) {
      if (depth[head[u]] < depth[head[v]]) swap(u, v);
      u = par[head[u]];
    }

    if (depth[u] < depth[v]) swap(u, v);

    return v;
  }
} hld;

void query1(int x, char r) {
  if (r == 'A') {
    if (roads[x].first == 'a') roads[x].first = 'A';
    else roads[x].first = 'a';
  } else if (r == 'B') {
    if (roads[x].second == 'b') roads[x].second = 'B';
    else roads[x].second = 'b';
  }

  hld.update(x);
}

void query2(int u, int v) {
  hld.toggle(u, v);
}

int query3(int u, char c, int v, char d) {
  int p = hld.lca(u, v);
  Node l = hld.query(u, p);
  Node r = hld.query(v, p);

  return l.mini[c - 'A'] + r.mini[d - 'A'] + (l.lane[c - 'A'] != r.lane[d - 'A']);
}

int main() {
  scanf("%d %d", &n, &q);

  for (int i=1; i<n; i++) {
    int u;
    scanf("%d %c %c", &u, &roads[i].first, &roads[i].second);

    --u;
    edges[u].push_back(i);
  }

  hld.build();

  while (q--) {
    int t;
    scanf("%d", &t);

    if (t == 1) {
      int x; char r;
      scanf("%d %c", &x, &r);
      query1(x, r);
    } else if (t == 2) {
      int u, v;
      scanf("%d %d", &u, &v);
      query2(--u, --v);
    } else if (t == 3) {
      int u, v; char c, d;
      scanf("%d %c %d %c", &u, &c, &v, &d);
      printf("%d\n", query3(--u, c, --v, d));
    }
  }

  return 0;
}