#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

// so it can be captured by Node
int k;

struct Node {
  int len;
  long long ans;
  vector<pair<int, int>> pref, suf;

  void reset() {
    len = 0;
    ans = 0;
    pref = suf = {{0, 0}};
  }

  void add(int v) {
    len++;
    int nval;

    nval = pref.back().first | (1 << v);
    if (pref.back().first != nval) {
      pref.push_back({nval, 1});
    } else {
      pref[pref.size()-1].second++;
    }

    vector<pair<int, int>> newSuf = {{1 << v, 1}};
    for (auto it : suf) {
      nval = newSuf.back().first | it.first;

      if (newSuf.back().first != nval) {
        newSuf.push_back({nval, it.second});
      } else {
        newSuf[newSuf.size()-1].second += it.second;
      }
    }

    suf = newSuf;
    if (__builtin_popcount(suf.back().first) == k) {
      ans += suf.back().second;
    }
  }

  long long getCombined(Node other) {
    long long ret = ans + other.ans;

    for (int i = (int)pref.size()-1, j = 0, otherLen = other.len ; i >= 0 ; i--) {
      while (j < other.pref.size() && __builtin_popcount(pref[i].first | other.pref[j].first) != k) {
        otherLen -= other.pref[j].second;
        j++;
      }

      ret += 1ll * pref[i].second * otherLen;
    }

    return ret;
  }
};

struct Query {
  int a, b, idx;
};

vector<pair<int, int>> adj[N];
vector<Query> queries[N];

bool blocked[N];
int sz[N];
int worst[N];
int subtree[N];

Node nodeVal[N];

int n, q;
long long ans[N];

void read() {
  scanf("%d %d", &n, &k);
  
  for (int i = 1 ; i < n ; i++) {
    int u, v;
    char s[5];

    scanf("%d %d %s", &u, &v, s);
    int ch = s[0] - 'a';

    adj[u].push_back({v, ch});
    adj[v].push_back({u, ch});
  }

  scanf("%d", &q);
  for (int i = 1 ; i <= q ; i++) {
    Query query;
    scanf("%d %d", &query.a, &query.b);
    query.idx = i;

    queries[1].push_back(query);
  }
}

void dfsSize(vector<int> &visited, int now, int prv) {
  sz[now] = 1;
  worst[now] = 0;
  visited.push_back(now);

  for (pair<int, int> nex : adj[now]) {
    if (nex.first == prv || blocked[nex.first]) continue;

    dfsSize(visited, nex.first, now);
    sz[now] += sz[nex.first];
    worst[now] = max(worst[now], sz[nex.first]);
  }
}

void dfsCentroidSubtree(int subRoot, int now, int prv, int edgeVal) {
  subtree[now] = subRoot;
  nodeVal[now] = nodeVal[prv];
  nodeVal[now].add(edgeVal);

  for (pair<int, int> nex : adj[now]) {
    if (nex.first == prv || blocked[nex.first]) continue;
    dfsCentroidSubtree(subRoot, nex.first, now, nex.second);
  }
}

void centroidSolve(int cur) {
  vector<Query> que = queries[cur];
  queries[cur].clear();

  vector<int> visited;
  dfsSize(visited, cur, -1);

  int root = cur;
  for (int x : visited) {
    worst[x] = max(worst[x], sz[cur] - sz[x]);
    if (worst[x] < worst[root]) {
      root = x;
    }
  }

  subtree[root] = root;
  nodeVal[root].reset();
  for (pair<int, int> nex : adj[root]) {
    if (blocked[nex.first]) continue;
    dfsCentroidSubtree(nex.first, nex.first, root, nex.second);
  }

  for (Query query : que) {
    int a = query.a;
    int b = query.b;
    int idx = query.idx;

    if (subtree[a] == subtree[b]) {
      queries[subtree[a]].push_back(query);
    } else {
      Node nodeA = nodeVal[a];
      Node nodeB = nodeVal[b];
      long long ret = nodeA.getCombined(nodeB);
      
      ans[idx] = ret;
    }
  }

  blocked[root] = true;
  for (pair<int, int> nex : adj[root]) {
    if (blocked[nex.first]) continue;
    centroidSolve(nex.first);
  }
}

void work() {
  centroidSolve(1);

  for (int i = 1 ; i <= q ; i++) {
    printf("%lld\n", ans[i]);
  }
}

int main() {
  read();
  work();
  return 0;
}
