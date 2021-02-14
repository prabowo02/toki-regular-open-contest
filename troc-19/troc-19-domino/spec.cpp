#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAX = 100;
const int MOD = 998244353;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M;
  int ans;

  void InputFormat() {
    LINE(N, M);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAX);
    CONS(1 <= M && M <= MAX);
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
      "1 1",
    });
    Output({
      "1",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "2 2",
    });
    Output({
      "8",
    });
  }

  void SampleTestCase3() {
    Subtasks({1});
    Input({
      "12 73",
    });
    Output({
      "75544062",
    });
  }

  void TestGroup1() {
    Subtasks({1});
    CASE(N = 1;   M = 100);
    CASE(N = 100; M = 1  );
    CASE(N = 100; M = 100);
    CASE(N = 10;  M = 36 );
    CASE(N = 48;  M = 63 );
    CASE(N = 99;  M = 91 );
    CASE(N = 77;  M = 85 );
    CASE(N = 23;  M = 23 );
    CASE(N = 55;  M = 95 );
    CASE(N = 69;  M = 42 );
  }
};
