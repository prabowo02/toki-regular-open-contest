#include <bits/stdc++.h>
using namespace std;

void WA(string reason) {
  // cout << "WA " << reason << endl;
  cout << "WA" << endl;
  exit(0);
}

void AC() {
  puts("AC");
  exit(0);
}

const int LN = 18;
const int N = 200005;

const int MAX_QUERY = 200000;

int n;
vector<int> edges[N];
int w[N];

bool isLeaf[N];

vector<pair<int, int>> con_ans;

int depth[N];
int par[LN][N];
int leafCount[N];
void dfs(int u, int p) {
  par[0][u] = p;
  isLeaf[u] = true;
  for (int v: edges[u]) {
    if (v == p) continue;
    isLeaf[u] = false;

    depth[v] = depth[u] + 1;
    dfs(v, u);
    leafCount[u] += leafCount[v];
  }

  if (isLeaf[u]) leafCount[u] = w[u];
}

int lca(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  while (depth[u] != depth[v]) {
    u = par[__builtin_ctz(depth[u] - depth[v])][u];
  }

  if (u == v) return u;

  for (int i = LN-1; i >= 0; --i) {
    if (par[i][u] == par[i][v]) continue;
    u = par[i][u];
    v = par[i][v];
  }

  return par[0][u];
}

int leaf_count[N];
int lca_count[N];
int con_w[N];
int dfs_con(int u, int p) {
  int ret = 0;
  bool leaf = true;
  for (int v: edges[u]) {
    if (v == p) continue;
    ret += dfs_con(v, u);
    leaf = false;
  }

  if (leaf) {
    con_w[u] = leaf_count[u];
    return leaf_count[u];
  }

  con_w[u] = ret - lca_count[u];
  return ret - lca_count[u]*2;
}

void check() {
  for (int i = 0; i < con_ans.size(); ++i) {
    int u = con_ans[i].first, v = con_ans[i].second;
    if (!isLeaf[u] || !isLeaf[v]) WA("u or v is not leaf");
    ++lca_count[lca(u, v)];
    ++leaf_count[u], ++leaf_count[v];
  }

  dfs_con(0, 0);

  for (int i = 0; i < n; ++i) {
    if (con_w[i] != w[i]) WA("different w");
  }

  AC();
}

void init() {
  depth[0] = 0;
  dfs(0, 0);

  for (int i = 1; i < LN; ++i) {
    for (int j = 0; j < n; ++j) {
      par[i][j] = par[i-1][par[i-1][j]];
    }
  }
}

void read_tc_in(ifstream &is) {
  is >> n;
  for (int i = 1; i < n; ++i) {
    int u, v;
    is >> u >> v;
    --u, --v;

    edges[u].push_back(v);
    edges[v].push_back(u);
  }

  for (int i = 0; i < n; ++i) is >> w[i];
}

void read_contestant(ifstream &is) {
  int Q;
  if (!(is >> Q)) WA("No input Q");
  if (Q < 0 || Q > MAX_QUERY) WA("Q out of bound");

  con_ans.resize(Q);
  for (int i = 0; i < Q; ++i) {
    int u, v;
    if (!(is >> u >> v)) WA("no input u, v");
    --u, --v;

    if (u < 0 || u >= n) WA("u out of bound");
    if (v < 0 || v >= n) WA("v out of bound");
    if (u == v) WA("u equals to v");

    con_ans[i] = {u, v};
  }

  // Check for extra output
  if (is >> Q) WA("has extra output");
}

int main(int argc, char *argv[]) {
  ifstream tc_in(argv[1]);
  ifstream tc_out(argv[2]);
  ifstream con_out(argv[3]);

  read_tc_in(tc_in);
  read_contestant(con_out);
  init();
  check();
  return 0;
}
