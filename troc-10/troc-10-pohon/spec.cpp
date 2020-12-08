#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 200000;
const int MAXQ = 200000;
vector<int> constructW(const vector<int> &U, const vector<int> &V, const vector<pair<int, int>> &queries);

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  vector<int> U, V;
  vector<int> W;
  
  int Q;
  vector<int> conU, conV;

  void InputFormat() {
    LINE(N);
    LINES(U, V) % SIZE(N-1);
    LINE(W % SIZE(N));
  }
  
  void OutputFormat() {
    LINE(Q);
    LINES(conU, conV) % SIZE(Q);
  }
  
  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(64);
  }
  
  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(eachElementBetween(U, 1, N));
    CONS(eachElementBetween(V, 1, N));
    CONS(eachElementBetween(W, 0, 200000));
    CONS(isTree(N, U, V));
  }

  void StyleConfig() {
    CustomScorer();
  }
  
  void Subtask1() {
    Points(100);
  }

 private:
  bool eachElementBetween(const vector<int> &V, int mins, int maxs) {
    for (int x: V) {
      if (x < mins || x > maxs) {
        return false;
      }
    }
    
    return true;
  }

  bool isTree(int N, const vector<int> &U, const vector<int> &V) {
    vector<int> par(N);
    iota(par.begin(), par.end(), 0);

    auto root = [&](int u) {
      vector<int> pars;
      while (u != par[u]) {
        pars.push_back(u);
        u = par[u];
      }

      for (int p: pars) par[p] = u;

      return u;
    };

    for (int i = 0; i < N-1; ++i) {
      if (root(U[i] - 1) == root(V[i] - 1)) return false;
      par[root(V[i] - 1)] = root(U[i] - 1);
    }

    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "5",
      "1 2",
      "1 3",
      "3 4",
      "3 5",
      "1 1 2 2 1",
    });
    Output({
      "2",
      "4 5",
      "4 2",
    });
  }
  
  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "1",
      "0",
    });
  }

  void BeforeTestCase() {
    U.clear(); V.clear(); W.clear();
  }

  void AfterTestCase() {
    // Shuffle edges
    vector<int> idxs(N-1);
    iota(idxs.begin(), idxs.end(), 0);
    rnd.shuffle(idxs.begin(), idxs.end());
    vector<int> tU, tV;
    for (int i = 0; i < idxs.size(); ++i) {
      tU.push_back(U[idxs[i]]);
      tV.push_back(V[idxs[i]]);
    }
    U = tU, V = tV;

    // Swap vertices
    for (int i = 0; i < N-1; ++i) {
      if (rnd.nextInt(2)) swap(U[i], V[i]);
    }

    // Convert to 1-index
    for (int i = 0; i < N-1; ++i) {
      ++U[i], ++V[i];
    }
  }
  
  void TestGroup1() {
    Subtasks({1});

    CASE(N = 5; Q = 4; starTree(N); W = {4, 1, 1, 3, 3});
    CASE(N = 4; Q = 2; starTree(N); W = {2, 1, 1, 2});
    CASE(N = 10; Q = 10; randomQuery(Q, randomTree(N)));
    CASE(N = 50000; Q = (N-1)*4; starTree(N); W = vector<int>(N, 8); W[0] = Q);

    CASE(N = MAXN; Q = 0; randomTree(N); W = vector<int>(N, 0));

    CASE(N = MAXN; Q = MAXQ; randomQuery(Q, randomTree(N)));
    CASE(N = MAXN; Q = MAXQ; randomQuery(Q, binaryTree(N)));
    CASE(N = MAXN; Q = MAXQ; randomQuery(Q, starTree(N)));
    CASE(N = MAXN; Q = MAXQ; randomQuery(Q, almostLTree(N)));
    CASE(N = MAXN; Q = MAXQ; randomQuery(Q, longStarTree(N)));

    CASE(N = MAXN; Q = MAXQ; twoEndsQuery(Q, randomTree(N)));
    CASE(N = MAXN; Q = MAXQ; twoEndsQuery(Q, LTree(N)));

    CASE(N = MAXN; Q = MAXQ; pivotedQuery(Q, randomTree(N)));
    CASE(N = MAXN; Q = MAXQ; pivotedQuery(Q, starTree(N)));
    CASE(N = MAXN; Q = MAXQ; pivotedQuery(Q, binaryTree(N)));

    CASE(N = (1 << (31 - __builtin_clz(MAXN))) - 1; Q = MAXQ; firstHalfSecondHalfQuery(Q, binaryTree(N)));
    CASE(N = (1 << (31 - __builtin_clz(MAXN))) - 1; differentLcaPerfectBinaryTreeQuery(binaryTree(N)));
  }

 private:
  vector<int> randomTree(int N) {
    vector<bool> isLeaf(N, true);
    for (int i = 1; i < N; ++i) {
      U.push_back(rnd.nextInt(i));
      V.push_back(i);

      isLeaf[U.back()] = false;
    }

    vector<int> leaves;
    for (int i = 0; i < N; ++i) if (isLeaf[i]) {
      leaves.push_back(i);
    }

    return leaves;
  }

  vector<int> starTree(int N) {
    vector<int> leaves(N-1);
    for (int i = 1; i < N; ++i) {
      U.push_back(0);
      V.push_back(i);
      leaves[i-1] = i;
    }
    return leaves;
  }

  vector<int> binaryTree(int N) {
    for (int i = 1; i < N; ++i) {
      U.push_back((i-1) >> 1);
      V.push_back(i);
    }

    vector<int> leaves;
    for (int i = N>>1; i < N; ++i) {
      leaves.push_back(i);
    }

    return leaves;
  }

  vector<int> LTree(int N) {
    assert(N >= 3);
    U.push_back(0); V.push_back(1);
    U.push_back(0); V.push_back(2);
    for (int i = 3; i < N; ++i) {
      U.push_back(i-2);
      V.push_back(i);
    }

    return {V[N-3], V[N-2]};
  }

  vector<int> longStarTree(int N) {
    int sn = sqrt(N);
    for (int i = 1; i <= sn; ++i) {
      U.push_back(0);
      V.push_back(i);
    }

    for (int i = sn+1; i < N; ++i) {
      U.push_back(i-sn);
      V.push_back(i);
    }

    vector<int> leaves(sn);
    iota(leaves.begin(), leaves.end(), N - sn);
    return leaves;
  }

  vector<int> almostLTree(int N) {
    int bias = N / 10;
    U.push_back(0); V.push_back(1);
    U.push_back(0); V.push_back(2);
    for (int i = 3; i < N - bias; ++i) {
      U.push_back(i-2);
      V.push_back(i);
    }

    set<int> leaves;
    leaves.insert(V[V.size() - 2]);
    leaves.insert(V.back());

    for (int i = N - bias; i < N; ++i) {
      U.push_back(rnd.nextInt(i));
      V.push_back(i);

      if (leaves.find(U.back()) != leaves.end()) leaves.erase(U.back());
      leaves.insert(i);
    }

    return vector<int>(leaves.begin(), leaves.end());
  }

  void randomQuery(int Q, const vector<int> &leaves) {
    vector<pair<int, int>> queries(Q);
    for (int i = 0; i < Q; ++i) {
      int u = -1, v = -1;

      while (u == v) {
        u = leaves[rnd.nextInt(leaves.size())];
        v = leaves[rnd.nextInt(leaves.size())];
      }

      queries[i] = {u, v};
    }

    constructW(queries);
  }

  void twoEndsQuery(int Q, const vector<int> &leaves) {
    assert(leaves.size() >= 2);
    int u = leaves[0], v = leaves.back();

    constructW(vector<pair<int, int>>(Q, make_pair(u, v)));
  }

  void firstHalfSecondHalfQuery(int Q, const vector<int> &leaves) {
    int mid = leaves.size() >> 1;

    vector<pair<int, int>> queries(Q);
    for (int i = 0; i < Q; ++i) {
      queries[i] = {leaves[rnd.nextInt(mid)], leaves[mid + rnd.nextInt(mid)]};
    }

    constructW(queries);
  }

  void differentLcaPerfectBinaryTreeQuery(vector<int> leaves) {
    vector<pair<int, int>> queries;

    vector<int> level;
    while (leaves.size() > 1) {
      while (leaves.size() > 1) {
        int u = leaves.back(); leaves.pop_back();
        int v = leaves.back(); leaves.pop_back();

        queries.emplace_back(u, v);

        level.push_back(rnd.nextInt(2) ? u : v);
      }
      leaves = level;
      level.clear();
    }

    Q = queries.size();
    constructW(queries);
  }

  void pivotedQuery(int Q, const vector<int> &leaves) {
    int u = leaves[rnd.nextInt(leaves.size())];
    vector<pair<int, int>> queries(Q);
    for (int i = 0; i < Q; ++i) {
      int v = u;
      while (v == u) {
        v = leaves[rnd.nextInt(leaves.size())];
      }

      queries[i] = {u, v};
    }

    constructW(queries);
  }

  void constructW(const vector<pair<int, int>> &queries) {
    W = ::constructW(U, V, queries);
  }
};

class WConstructor {
 private:
  static const int LN = 18;
  static const int N = 200005;

  int n;
  vector<int> edges[N];

  int depth[N];
  int par[LN][N];
  void dfs_lca(int u, int p) {
    par[0][u] = p;
    for (int v: edges[u]) {
      if (v == p) continue;

      depth[v] = depth[u] + 1;
      dfs_lca(v, u);
    }
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
  int w[N];
  int dfs(int u, int p) {
    int ret = 0;
    bool leaf = true;
    for (int v: edges[u]) {
      if (v == p) continue;
      ret += dfs(v, u);
      leaf = false;
    }

    if (leaf) {
      w[u] = leaf_count[u];
      return leaf_count[u];
    }

    w[u] = ret - lca_count[u];
    return ret - lca_count[u]*2;
  }

  void build(const vector<pair<int, int>> &queries) {
    for (int i = 0; i < n; ++i) leaf_count[i] = lca_count[i] = 0;

    for (const pair<int, int> &query: queries) {
      int u = query.first, v = query.second;
      ++lca_count[lca(u, v)];
      ++leaf_count[u], ++leaf_count[v];
    }

    dfs(0, 0);
  }

  void init_tree(const vector<int> &U, const vector<int> &V) {
    n = U.size() + 1;

    for (int i = 0; i < n; ++i) edges[i].clear();

    for (int i = 0; i < n-1; ++i) {
      edges[U[i]].push_back(V[i]);
      edges[V[i]].push_back(U[i]);
    }
  }

  void init_lca() {
    depth[0] = 0;
    dfs_lca(0, 0);

    for (int i = 1; i < LN; ++i) {
      for (int j = 0; j < n; ++j) {
        par[i][j] = par[i-1][par[i-1][j]];
      }
    }
  }

 public:
  vector<int> constructW(const vector<int> &U, const vector<int> &V, const vector<pair<int, int>> &queries) {
    init_tree(U, V);
    init_lca();
    build(queries);
    return vector<int>(w, w + n);
  }
} wConstructor;

vector<int> constructW(const vector<int> &U, const vector<int> &V, const vector<pair<int, int>> &queries) {
  return wConstructor.constructW(U, V, queries);
}
