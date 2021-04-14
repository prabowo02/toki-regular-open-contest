#include <tcframe/spec.hpp>
#include <tcrand/graph.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace tcrand;
using namespace std;

const int MAXN = 100000;
const int MAXM = 200000;
const int MAXB = 17;
const int MAXW = 200000;
const int MAXT = (1 << MAXB) - 1;

vector<int> operator + (const vector<int> &U, const vector<int> &V) {
  vector<int> ret(U.size() + V.size());
  for (int i = 0; i < U.size(); ++i) ret[i] = U[i];
  for (int i = 0; i < V.size(); ++i) ret[i + U.size()] = V[i];
  return ret;
}

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M, D;
  long long ans;

  vector<int> U, V, W, T;
  vector<int> P, A;

  void InputFormat() {
    LINE(N, M, D);
    LINES(U, V, W, T) % SIZE(M);
    LINES(P, A) % SIZE(D);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(1 <= M && M <= MAXM);
    CONS(1 <= D && D <= N);
    CONS(eachElementBetween(U, 1, N));
    CONS(eachElementBetween(V, 1, N));
    CONS(noSelfLoop(U, V));
    CONS(noMultiEdge(U, V));
    CONS(eachElementBetween(W, 1, MAXW));
    CONS(eachElementBetween(T, 1, MAXT));
    CONS(eachElementBetween(P, 1, N));
    CONS(distinct(P));
    CONS(eachElementBetween(A, 1, MAXT));
  }

  bool eachElementBetween(const vector<int> &A, int lo, int hi) {
    for (int u : A) if (u < lo || u > hi) return false;
    return true;
  }

  bool noSelfLoop(const vector<int> &U, const vector<int> &V) {
    for (int i = 0; i < U.size(); ++i) if (U[i] == V[i]) return false;
    return true;
  }

  bool noMultiEdge(const vector<int> &U, const vector<int> &V) {
    vector<pair<int, int>> edges(U.size());
    for (int i = 0; i < U.size(); ++i) {
      if (U[i] < V[i]) edges[i] = make_pair(U[i], V[i]);
      else edges[i] = make_pair(V[i], U[i]);
    }
    return distinct(edges);
  }

  template<class T>
  bool distinct(vector<T> V) {
    sort(V.begin(), V.end());
    return unique(V.begin(), V.end()) == V.end();
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Input({
      "7 9 5",
      "1 2 1 1",
      "1 3 4 7",
      "2 3 4 7",
      "3 4 1 8",
      "3 5 1 8",
      "4 5 7 1",
      "5 6 2 3",
      "6 4 2 2",
      "6 7 1 3",
      "1 1",
      "2 2",
      "4 1",
      "5 2",
      "7 3",
    });
    Output({
      "11",
    });
  }

  void BeforeTestCase() {
    U.clear(); V.clear(); W.clear(); T.clear();
    P.clear(); A.clear();
  }

  void TestGroup1() {
    CASE(N = 2; M = 1; D = 2; U = {1}; V = {2}; W = {1}; T = {4}; P = {1, 2}; A = {1, 2});
    CASE(N = 2; M = 1; D = 1; U = {1}; V = {2}; W = {1}; T = {7}; P = {1}; A = {1});

    CASE(randomConnectedGraph(MAXN / 2, MAXM); randomLamps(N));
    CASE(randomDisconnectedGraph(MAXN / 2, MAXM); randomLamps(N));
    CASE(randomConnectedGraph(MAXN, MAXM); randomLamps(N));
    CASE(randomConnectedGraph(MAXN / 2 + 1, MAXM); W = vector<int>(M, MAXW); randomLamps(N));
    CASE(randomConnectedGraph(MAXN, MAXM); T = vector<int>(M, 1); randomLamps(N));
    CASE(randomConnectedGraph(MAXN, MAXM); T = randomArray(M, 1, 3); randomLamps(N / 3));
    CASE(randomConnectedGraph(MAXN / 2, MAXM); T = randomArray(M, 1, 3); randomLamps(N / 3));
    CASE(randomConnectedGraph(MAXN / 2, MAXM); randomLamps(N / 10));

    CASE(lineGraph(MAXN); T = vector<int>(M, 1); D = 2; P = {1, N}; A = {1, 1});
    CASE(lineGraph(MAXN); T = vector<int>(M, 1); randomLamps(N); A = vector<int>(N/2, 1) + vector<int>(N/2, 2));
    CASE(completeGraph(500); randomLamps(N));
    CASE(starGraph(MAXN); randomLamps(N));

    CASE(clawGraph(MAXN, MAXN/2); randomLamps(N));
    CASE(clawGraph(MAXN, sqrt(MAXN)); randomLamps(N));
    CASE(doubleEndedStar(MAXN));
    CASE(Pyqe(MAXN));
    CASE(ribbonGraph(MAXN));
  }

  vector<int> randomArray(int n, int lo, int hi) {
    vector<int> ret(n);
    for (int i = 0; i < n; ++i) ret[i] = rnd.nextInt(lo, hi);
    return ret;
  }

  vector<int> randomDistinctArray(int n, int lo, int hi) {
    vector<int> ret(hi - lo + 1);
    iota(ret.begin(), ret.end(), lo);
    rnd.shuffle(ret.begin(), ret.end());
    ret.resize(n);
    return ret;
  }

  void randomConnectedGraph(int _N, int _M) {
    N = _N; M = _M;
    GraphRandomizer graph_rand;
    tie(U, V) = graph_rand.node_count(N).edge_count(M).index_base(1).next().edges();
    W = randomArray(M, 1, MAXW);
    T = randomArray(M, 1, MAXT);
  }

  void randomDisconnectedGraph(int _N, int _M) {
    N = _N; M = _M;
    GraphRandomizer graph_rand;
    tie(U, V) = graph_rand.node_count(N).edge_count(M).component_count(2).index_base(1).next().edges();
    W = randomArray(M, 1, MAXW);
    T = randomArray(M, 1, MAXT);
  }

  void lineGraph(int _N) {
    N = _N; M = _N - 1;
    U = V = vector<int>(N - 1);
    for (int i = 1; i < N; ++i) U[i - 1] = i, V[i - 1] = i + 1;
    W = randomArray(M, 1, MAXW);
    T = vector<int>(M, MAXT);
  }

  void completeGraph(int _N) {
    N = _N;
    for (int i = 0; i < N; ++i) {
      for (int j = i + 1; j < N; ++j) {
        U.push_back(i + 1); V.push_back(j + 1);
      }
    }
    M = U.size();
    W = randomArray(M, 1, MAXW);
    T = randomArray(M, 1, MAXT);
  }

  void starGraph(int _N) {
    N = _N; M = _N - 1;
    U = V = vector<int>(M, 1);
    iota(V.begin(), V.end(), 2);
    W = randomArray(M, 1, MAXW);
    T = vector<int>(M, MAXT);
  }

  void randomLamps(int _D) {
    D = _D;
    P = randomDistinctArray(D, 1, N);
    A = randomArray(D, 1, MAXT);
  }

  void clawGraph(int _N, int deg) {
    N = _N; M = N - 1;
    U = V = vector<int>(M);
    W = randomArray(M, 1, MAXW);
    T = vector<int>(M, MAXT);
    for (int i = 1; i < N; ++i) {
      U[i - 1] = max(i - deg, 0) + 1;
      V[i - 1] = i + 1;
    }
  }

  void ribbonGraph(int _N) {
    N = _N;
    int mid = N / 2;
    for (int i = 2; i < mid; ++i) {
      U.push_back(1);
      V.push_back(i);
      W.push_back(i);
      T.push_back(MAXT);

      U.push_back(i);
      V.push_back(mid);
      W.push_back(MAXW - i*2);
      T.push_back(MAXT);
    }

    for (int i = mid + 1; i < N; ++i) {
      U.push_back(N);
      V.push_back(i);
      W.push_back(i);
      T.push_back(MAXT);

      U.push_back(i);
      V.push_back(mid);
      W.push_back(MAXW - i*2);
      T.push_back(MAXT);
    }
    M = U.size();

    D = 2;
    P = {1, N};
    A = {69, 69 ^ MAXT};
  }

  void doubleEndedStar(int _N) {
    N = _N; M = N - 1;
    int center1 = 1, center2 = 2;

    U = V = vector<int>();
    W = randomArray(M, 1, MAXW);
    T = vector<int>(M, MAXT);

    P = A = vector<int>();

    int mask = rnd.nextInt(1, MAXT - 1);

    for (int i = 2; i < N / 3; ++i) {
      U.push_back(i + 1);
      V.push_back(center1);
      P.push_back(i + 1);
      A.push_back(mask);
    }
    for (int i = N / 3; i < N / 3 * 2; ++i) {
      U.push_back(i + 1);
      V.push_back(center2);
      P.push_back(i + 1);
      A.push_back(mask ^ MAXT);
    }
    U.push_back(N / 3 * 2 + 1); V.push_back(center1);
    for (int i = N / 3 * 2 + 1; i < N; ++i) {
      U.push_back(i + 1);
      V.push_back(i);
    }
    U.push_back(center2); V.push_back(N);

    D = P.size();
  }

  void Pyqe(int _N) {
    N = _N; D = N;
    int mask = rnd.nextInt(1, MAXT);
    for (int i = 0; i < N / 2; ++i) {
      U.push_back(i + 1);
      V.push_back(N/2 + 1);
      W.push_back(MAXW - i - 1);
      T.push_back(3);

      if (i > 0) {
        U.push_back(i); V.push_back(i + 1);
        W.push_back(MAXW);
        T.push_back(MAXT);
      }

      P.push_back(i + 1);
      A.push_back(mask);
    }
    mask ^= MAXT;
    for (int i = N / 2; i < N; ++i) {
      if (i > N / 2) {
        U.push_back(i); V.push_back(i + 1);
        W.push_back(1);
        T.push_back(MAXT);
      }

      P.push_back(i + 1);
      A.push_back(mask);
    }
    M = U.size();
  }
};
