#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 100;
const int MAXA = (1 << 30) - 1;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M, K, X;
  int ans;

  void InputFormat() {
    LINE(N, M, K, X);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(2 <= N && N <= MAXN);
    CONS(2 <= M && M <= MAXN);
    CONS(1 <= K && K <= MAXA);
    CONS(__builtin_popcount(K + 1) == 1);
    CONS(0 <= X && X <= K);
  }

  void Subtask1() {
    Points(100);
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "2 2 1 1",
    });
    Output({
      "8",
    });
  }

  void TestGroup1() {
    Subtasks({1});
    CASE(N = 2; M = 3; K = 3; X = 1);
    CASE(N = 3; M = 2; K = 7; X = 0);
    CASE(N = MAXN; M = MAXN; K = MAXA; X = rnd.nextInt(0, K));
    CASE(N = MAXN/2; M = MAXN - 1; K = (1 << 10) - 1; X = rnd.nextInt(0, K));
    CASE(N = rnd.nextInt(2, MAXN); M = rnd.nextInt(2, MAXN); K = (1 << rnd.nextInt(1, 31)) - 1; X = rnd.nextInt(0, K));
    CASE(N = rnd.nextInt(2, MAXN); M = rnd.nextInt(2, MAXN); K = (1 << rnd.nextInt(1, 31)) - 1; X = rnd.nextInt(0, K));
    CASE(N = rnd.nextInt(2, MAXN); M = rnd.nextInt(2, MAXN); K = (1 << rnd.nextInt(1, 31)) - 1; X = rnd.nextInt(0, K));
    CASE(N = rnd.nextInt(2, MAXN); M = rnd.nextInt(2, MAXN); K = (1 << rnd.nextInt(1, 31)) - 1; X = rnd.nextInt(0, K));
  }
};
