#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 100000;
const int MAXM = 200000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M;
  vector<int> U, V;

  string ans;

  void InputFormat() {
    LINE(N, M);
    LINES(U, V) % SIZE(M);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(64);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(0 <= M && M <= MAXM);
    CONS(eachElementBetween(U, 1, N));
    CONS(eachElementBetween(V, 1, N));
  }

  void Subtask1() {
    Points(100);
  }

 private:
  bool eachElementBetween(const vector<int> &A, int lo, int hi) {
    for (int a: A) {
      if (a < lo || a > hi) return false;
    }

    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "3 3",
      "1 2",
      "2 1",
      "1 3",
    });
    Output({
      "YA",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "3 2",
      "1 2",
      "3 2",
    });
    Output({
      "TIDAK",
    });
  }

  bool needOrdering;
  void BeforeTestCase() {
    needOrdering = true;
    U.clear(); V.clear();
  }

  void AfterTestCase() {
    if (needOrdering) {
      vector<int> order(N);
      iota(order.begin(), order.end(), 1);
      rnd.shuffle(order.begin(), order.end());

      for (int i = 0; i < M; ++i) {
        U[i] = order[U[i]];
        V[i] = order[V[i]];
      }
    }
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 1; M = 0); // YA
    CASE(N = 1; M = 1; U = {0}; V = {0}); // YA
    CASE(N = 1; M = 2; U = {0, 0}; V = {0, 0}); // YA
    CASE(N = 2; M = 0); // TIDAK
    CASE(N = 3; M = 2; U = {1, 1}; V = {0, 2}); // TIDAK

    CASE(N = 400; CompleteGraph(N)); // YA
    CASE(N = 500; CompleteAcyclicGraph(N)); // YA
    CASE(N = 3; M = MAXM; randomDigraph(N, M)); // Almost for sure YA
    CASE(N = 200; M = MAXM; randomDigraph(N, M)); // likely YA (?)
    CASE(N = MAXN; M = MAXM; randomDigraph(N, M)); // likely TIDAK (?)

    CASE(N = MAXN; pathGraph(N)); // YA
    CASE(N = MAXN; M = MAXM; pathGraphWithExtraNonCyclicEdges(N, M)); // YA
    CASE(N = MAXN; cycleGraph(N)); // YA
    CASE(N = MAXN; LGraph(N)); // TIDAK
    CASE(N = MAXN; LGraph(N); swap(U, V)); // TIDAK

    CASE(N = MAXN - MAXN%2; forestOfCycleAndPath(N, 2, 0)); // TIDAK
    CASE(N = MAXN - MAXN%2; forestOfCycleAndPath(N, 0, 2)); // TIDAK
    CASE(N = MAXN - MAXN%2; forestOfCycleAndPath(N, 1, 1)); // TIDAK
    CASE(N = MAXN; pathGraph(N-1); U.push_back(N-3); V.push_back(N-1); ++M); // TIDAK

    AntiPikatan();
  }

 private:
  void CompleteGraph(int N) {
    M = N * (N-1);
    for (int i = 0; i < N; ++i) {
      for (int j = i+1; j < N; ++j) {
        U.push_back(i); V.push_back(j);
        U.push_back(j); V.push_back(i);
      }
    }
  }

  void CompleteAcyclicGraph(int N) {
    M = N * (N-1) / 2;
    for (int i = 0; i < N; ++i) {
      for (int j = i+1; j < N; ++j) {
        U.push_back(i); V.push_back(j);
      }
    }
  }

  void randomDigraph(int N, int M) {
    for (int i = 0; i < M; ++i) {
      U.push_back(rnd.nextInt(N));
      V.push_back(rnd.nextInt(N));
    }
  }

  void pathGraph(int N) {
    M = N - 1;
    for (int i = 1; i < N; ++i) {
      U.push_back(i-1);
      V.push_back(i);
    }
  }

  void pathGraphWithExtraNonCyclicEdges(int N, int _M) {
    assert(_M >= N-1);
    pathGraph(N);
    M = _M;
    for (int i = N-1; i < M; ++i) {
      int u = rnd.nextInt(N), v = rnd.nextInt(N);
      if (u > v) swap(u, v);

      U.push_back(u);
      V.push_back(v);
    }
  }

  void LGraph(int N) {
    assert(N >= 3);
    M = N - 1;
    U.push_back(0); V.push_back(1);
    U.push_back(0); V.push_back(2);

    for (int i = 3; i < N; ++i) {
      U.push_back(i-2);
      V.push_back(i);
    }
  }

  void cycleGraph(int N) {
    M = N;
    for (int i = 1; i < N; ++i) {
      U.push_back(i-1);
      V.push_back(i);
    }
    U.push_back(N-1); V.push_back(0);
  }

  void forestOfCycleAndPath(int N, int cycleCount, int pathCount) {
    assert(N % (cycleCount + pathCount) == 0);
    int componentSize = N / (cycleCount + pathCount);

    M = 0;
    int currentSize = 0;
    for (int i = 0; i < cycleCount + pathCount; ++i) {
      for (int u = currentSize + 1; u < currentSize + componentSize; ++u) {
        U.push_back(u-1);
        V.push_back(u);
      }

      if (i < cycleCount) {
        U.push_back(currentSize + componentSize - 1);
        V.push_back(currentSize);

        M += componentSize;
        currentSize += componentSize;
      } else {
        M += componentSize - 1;
        currentSize += componentSize;
      }
    }

    assert(currentSize == N);
  }

  void AntiPikatan() {
    CASE(N = 6; M = 6;
         U = {1, 2, 2, 4, 5, 5};
         V = {2, 3, 4, 5, 3, 6};
         needOrdering = false);

    CASE(N = 6; M = 6;
         U = {1, 2, 3, 4, 2, 4};
         V = {2, 3, 4, 5, 5, 6};
         needOrdering = false);

    CASE(N = 14; M = 15;
         U = {1, 2, 3, 4, 5, 6, 7, 8, 4, 9, 10, 11, 12, 13, 1};
         V = {2, 3, 4, 5, 6, 7, 8, 1, 9, 10, 11, 12, 3, 1, 14};
         needOrdering = false);

    CASE(N = 14; M = 15;
         U = {1, 2, 3, 4, 9, 6, 7, 8, 4, 5, 10, 11, 12, 13, 1};
         V = {2, 3, 4, 5, 6, 7, 8, 1, 9, 10, 11, 12, 3, 1, 14};
         needOrdering = false);
  }
};
