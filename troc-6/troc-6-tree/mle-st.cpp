// O(QK log N) time and memory
// should be MLE
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int LOG = 17;

int k;

struct Node {
  int len;
  long long ans;
  vector<pair<int, int>> pref, suf;

  Node() {
    len = 0;
    ans = 0;
    pref = suf = {{0, 0}};
  }

  void init(int v) {
    len = 1;
    ans = (k == 1);
    pref = suf = {{1 << v, 1}};
  }

  Node operator +(Node other) const {
    Node ret;
    ret.len = len + other.len;
    ret.ans = ans + other.ans;

    for (int i = (int)suf.size()-1, j = 0, otherLen = other.len ; i >= 0 ; i--) {
      while (j < other.pref.size() && __builtin_popcount(suf[i].first | other.pref[j].first) != k) {
        otherLen -= other.pref[j].second;
        j++;
      }

      ret.ans += 1ll * suf[i].second * otherLen;
    }

    {
      ret.pref = pref;
      for (pair<int, int> it : other.pref) {
        int lst = ret.pref.back().first;
        int cur = lst | it.first;
        if (cur == lst) {
          ret.pref[ret.pref.size()-1].second += it.second;
        } else {
          ret.pref.push_back({cur, it.second});
        }
      }
    }

    {
      ret.suf = other.suf;
      for (pair<int, int> it : suf) {
        int lst = ret.suf.back().first;
        int cur = lst | it.first;
        if (cur == lst) {
          ret.suf[ret.suf.size() - 1].second += it.second;
        } else {
          ret.suf.push_back({cur, it.second});
        }
      }
    }

    return ret;
  }
};

int n, q;

Node sparseTable[N][LOG];
int anc[N][LOG];

vector<pair<int, int>> adj[N];
int depth[N];

void build(int now, int prv, int v) {
  depth[now] = depth[prv] + 1;
  anc[now][0] = prv;
  sparseTable[now][0].init(v);

  for (int i = 1 ; (1 << i) <= depth[now] ; i++) {
    int papa = anc[now][i-1];
    anc[now][i] = anc[papa][i-1];
    sparseTable[now][i] = sparseTable[now][i-1] + sparseTable[papa][i-1];
  }
}

void dfs(int now, int prv) {
  for (pair<int, int> nex : adj[now]) {
    if (nex.first == prv) continue;
    build(nex.first, now, nex.second);
    dfs(nex.first, now);
  }
}

int getLCA(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  int diff = depth[u] - depth[v];
  for (int i = 0 ; diff ; i++) {
    if (diff & (1 << i)) {
      diff -= (1 << i);
      u = anc[u][i];
    }
  }

  if (u == v) return u;

  for (int i = LOG-1 ; i >= 0 ; i--) {
    if (depth[u] >= (1 << i) && anc[u][i] != anc[v][i]) {
      u = anc[u][i];
      v = anc[v][i];
    }
  }

  return anc[u][0];
}

Node getUpwardPath(int u, int k) {
  Node ret;

  for (int i = 0 ; k ; i++) {
    if (k & (1 << i)) {
      ret = ret + sparseTable[u][i];
      u = anc[u][i];
      k -= (1 << i);
    }
  }

  return ret;
}

long long solve(int u, int v) {
  int lca = getLCA(u, v);

  int lenU = depth[u] - depth[lca];
  int lenV = depth[v] - depth[lca];
  Node pathU = getUpwardPath(u, lenU);
  Node pathV = getUpwardPath(v, lenV);
  swap(pathV.pref, pathV.suf);
  Node ret = pathU + pathV;

  return ret.ans;
}

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
}

void prepare() {
  dfs(1, -1);
}

void work() {
  scanf("%d", &q);
  for (int i = 0 ; i < q ; i++) {
    int u, v;
    scanf("%d %d", &u, &v);

    printf("%lld\n", solve(u, v));
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}
