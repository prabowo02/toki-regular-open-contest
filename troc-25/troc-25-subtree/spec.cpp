#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 100000;
const int MAXQ = 100000;
const int MAXA = 998244353;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  vector<int> A;
  vector<int> U, V;
  int Q;
  vector<int> T, X;

  vector<int> ANS;

  void InputFormat() {
    LINE(N);
    LINE(A % SIZE(N));
    LINES(U, V) % SIZE(N - 1);
    LINE(Q);
    LINES(T, X) % SIZE(Q);
  }

  void OutputFormat() {
    LINES(ANS) % SIZE(queryCount(T));
  }

  void Constraints() {
    CONS(2 <= N && N <= MAXN);
    CONS(eachElementBetween(A, 0, MAXA - 1));
    CONS(isTree(U, V));
    CONS(2 <= Q && Q <= MAXN);
    CONS(eachElementBetween(T, 1, 2));
    CONS(eachElementBetween(X, 1, N));
    CONS(queryCount(T) >= 1);
  }

  void Subtask1() {
    Points(100);
  }

  int queryCount(const vector<int> &T) {
    int ret = 0;
    for (int t : T) if (t == 2) ++ret;
    return ret;
  }

  bool eachElementBetween(const vector<int> &X, int lo, int hi) {
    return all_of(X.begin(), X.end(), [&](int x) { return lo <= x && x <= hi; });
  }
  bool isTree(const vector<int> &U, const vector<int> &V) {
    int N = U.size() + 1;
    vector<int> par(N);
    iota(par.begin(), par.end(), 0);
    function<int(int)> dsu = [&](int u) {
      if (u == par[u]) return u;
      return par[u] = dsu(par[u]);
    };

    for (int i = 0; i < N - 1; ++i) {
      int u = U[i] - 1, v = V[i] - 1;
      if (u < 0 || u >= N || v < 0 || v >= N) return false;
      if (dsu(u) == dsu(v)) return false;
      par[par[u]] = par[v];
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "3",
      "1 2 3",
      "1 2",
      "1 3",
      "4",
      "2 1",
      "1 1",
      "2 1",
      "2 2",
    });
    Output({
      "5",
      "7",
      "1",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "7",
      "3 6 4 8 1 9 2",
      "1 2",
      "1 3",
      "2 4",
      "2 5",
      "3 6",
      "3 7",
      "7",
      "2 7",
      "1 5",
      "2 4",
      "1 1",
      "1 4",
      "2 3",
      "2 1",
    });
    Output({
      "4",
      "7",
      "14",
      "25",
    });
  }

  void BeforeTestCase() {
    A.clear(); U.clear(); V.clear();
    T.clear(); X.clear();
  }

  void AfterTestCase() {
    vector<int> order(N);
    iota(order.begin(), order.end(), 1);
    rnd.shuffle(order.begin(), order.end());

    vector<int> tA(N);
    for (int i = 0; i < N; ++i) tA[order[i] - 1] = A[i];
    A = tA;

    for (int i = 0; i < N - 1; ++i) {
      U[i] = order[U[i]];
      V[i] = order[V[i]];
      if (rnd.nextInt(2)) swap(U[i], V[i]);
    }

    Q = T.size();
    for (int i = 0; i < Q; ++i) {
      X[i] = order[X[i]];
    }
  }

  void TestGroup1() {
    Subtasks({1});

    // All possible trees
    CASE(N = MAXN; randomTree(N); A = randomArray(N); randomOps(MAXQ - 1); addAnyQuery());
    CASE(N = MAXN; chainTree(N); A = randomArray(N); randomOps(MAXQ - 1); addAnyQuery());
    CASE(N = MAXN; starTree(N); A = randomArray(N); randomOps(MAXQ - 1); addAnyQuery());
    CASE(N = MAXN; knary(N, 500); A = randomArray(N); randomOps(MAXQ - 1); addAnyQuery());
    CASE(N = MAXN; halving(N); A = randomArray(N); randomOps(MAXQ - 1); addAnyQuery());
    CASE(N = MAXN; claw(N); A = randomArray(N); randomOps(MAXQ - 1); addAnyQuery());

    // Star Graphs
    // lot of operations on root
    CASE(N = MAXN; starTree(N); A = randomArray(N); randomOpsRange(MAXQ - 1, 0, 0); addAnyQuery());
    // lot of operations on root, all A is maxed
    CASE(N = MAXN; starTree(N); A = vector<int>(N, MAXA - 1); randomOpsRange(MAXQ - 1, 0, 0); addAnyQuery());
    // lot of queries on root
    CASE(N = MAXN; starTree(N); A = randomArray(N); randomOpsRange(MAXQ - 1, 0, 0, 1, 50000); addAnyQuery());
    // lot of updates on root
    CASE(N = MAXN; starTree(N); A = randomArray(N); randomOpsRange(MAXQ - 1, 0, 0, 50000, 1); addAnyQuery());
    // all updates on leaves, all queries on root
    CASE(N = MAXN; starTree(N); A = randomArray(N); randomOpsRange(MAXQ / 2 - 1, 0, 0, 0, 1); randomOpsRange(MAXQ / 2 - 1, 1, N - 1, 1, 0); shuffleOps(); addAnyQuery());
    // all updates on root, all queries on leaves
    CASE(N = MAXN; starTree(N); A = randomArray(N); randomOpsRange(MAXQ / 2 - 1, 0, 0, 1, 0); randomOpsRange(MAXQ / 2 - 1, 1, N - 1, 0, 1); shuffleOps(); addAnyQuery());

    // Various k-ary trees, and all ops on non-leaves
    CASE(N = MAXN; knary(N, 400); A = randomArray(N); randomOpsRange(MAXQ - 1, 0, N / 400); addAnyQuery());
    CASE(N = MAXN; knary(N, 500); A = randomArray(N); randomOpsRange(MAXQ - 1, 0, N / 500); addAnyQuery());
    CASE(N = MAXN; knary(N, 300); A = randomArray(N); randomOpsRange(MAXQ - 1, 0, N / 300); addAnyQuery());
    CASE(N = MAXN; knary(N, 600); A = randomArray(N); randomOpsRange(MAXQ - 1, 0, N / 600); addAnyQuery());
    CASE(N = MAXN; knary(N, 200); A = randomArray(N); randomOpsRange(MAXQ - 1, 0, N / 200); addAnyQuery());

    // Misc cases
    // two nodes with degree N/2, and lot of updates between the two nodes
    CASE(N = MAXN; knary(N, N / 2); A = randomArray(N); randomOpsRange(MAXQ/2 - 100, 0, 0); randomOpsRange(MAXQ/2 - 100, 1, 1); randomOpsRange(10, 0, 1, 0, 1); shuffleOps(); randomOpsRange(100, 0, N - 1, 0, 1));
    // claw graph, and ops are more concentrated on root
    CASE(N = MAXN; claw(N); A = randomArray(N); randomOpsRange(MAXQ/2, 0, 0); randomOpsRange(MAXQ/2 - 1, 1, N - 1); shuffleOps(); addQuery(0));
    // claw graph, but lot of updates on grandsons of root, and queries on root
    CASE(N = MAXN; claw(N); A = randomArray(N); T = vector<int>(N - N/2, 1); X = vector<int>(N - N/2); iota(X.begin(), X.end(), N/2); randomOpsRange(N/2 - 10, 0, 0, 0, 1); shuffleOps(); addAnyQuery());
    // lot of updates
    CASE(N = MAXN - 1; randomTree(N); A = randomArray(N); randomOpsRange(MAXQ - 1, 0, N - 1, 1, 0); addAnyQuery());
    // all queries
    CASE(N = MAXN - 10; randomTree(N); A = randomArray(N); randomOpsRange(MAXQ - 1, 0, N - 1, 0, 1); addAnyQuery());
    // all 0s
    CASE(N = MAXN; randomTree(N); A = randomArray(N); randomOps(MAXQ - 1); addAnyQuery());
  }

  //////////////////
  // Tree helpers //
  //////////////////

  void randomTree(int N) {
    for (int i = 1; i < N; ++i) {
      U.push_back(rnd.nextInt(i));
      V.push_back(i);
    }
  }

  void starTree(int N) {
    U.assign(N - 1, 0);
    V.resize(N - 1);
    iota(V.begin(), V.end(), 1);
  }

  void chainTree(int N) {
    for (int i = 1; i < N; ++i) {
      U.push_back(i - 1);
      V.push_back(i);
    }
  }

  void knary(int N, int K) {
    for (int i = 1; i < N; ++i) {
      U.push_back(i / K);
      V.push_back(i);
    }
  }

  // number of nodes is not exactly n
  void halving(int n) {
    int u = 0, v = 1;
    N = 1;
    for (int two = n / 2; two > 1; two >>= 1) {
      for (int i = 0; i < two; ++i) {
        U.push_back(u);
        V.push_back(v++);
        ++N;
      }
      ++u;
    }
  }

  void claw(int N) {
    for (int i = 1; i < N / 2; ++i) {
      U.push_back(0);
      V.push_back(i);
    }
    for (int i = N / 2; i < N; ++i) {
      U.push_back(rnd.nextInt(1, i - 1));
      V.push_back(i);
    }
  }

  ///////////////////
  // Array helpers //
  ///////////////////

  vector<int> randomArray(int n, int lo=0, int hi=MAXA-1) {
    vector<int> A(n);
    for (int &a : A) a = rnd.nextInt(lo, hi);
    return A;
  }

  ///////////////////
  // Query helpers //
  ///////////////////

  void randomOps(int q, int w1=1, int w2=1) {
    for (int i = 0; i < q; ++i) {
      T.push_back(rnd.nextInt(w1 + w2) < w1 ? 1 : 2);
      X.push_back(rnd.nextInt(N));
    }
  }

  void randomOpsRange(int q, int l, int r, int w1=1, int w2=1) {
    for (int i = 0; i < q; ++i) {
      T.push_back(rnd.nextInt(w1 + w2) < w1 ? 1 : 2);
      X.push_back(rnd.nextInt(l, r));
    }
  }

  void shuffleOps() {
    vector<int> order(T.size());
    iota(order.begin(), order.end(), 0);
    rnd.shuffle(order.begin(), order.end());

    vector<int> nT(T.size()), nX(X.size());
    for (int i = 0; i < T.size(); ++i) {
      nT[order[i]] = T[i];
      nX[order[i]] = X[i];
    }
    T = nT; X = nX;
  }

  inline void addOp(int t, int x) { T.push_back(t); X.push_back(x); }
  inline void addUpdate(int x) { addOp(1, x); }
  inline void addQuery(int x) { addOp(2, x); }
  inline void addAnyUpdate() { addOp(1, rnd.nextInt(N)); }
  inline void addAnyQuery() { addOp(2, rnd.nextInt(N)); }
};
