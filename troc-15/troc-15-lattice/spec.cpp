#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXA = 1000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  int ans;

  void InputFormat() {
    LINE(N);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXA);
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
      "7",
    });
    Output({
      "5",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "5",
    });
    Output({
      "5",
    });
  }

  void SampleTestCase3() {
    Subtasks({1});
    Input({
      "2",
    });
    Output({
      "-1",
    });
  }

  void TestGroup1() {
    Subtasks({1});
    CASE(N = 3);
    CASE(N = 9);
    CASE(N = 10);
    CASE(N = 11);
    CASE(N = 12);
    CASE(N = 69);
    CASE(N = 420);
    CASE(N = 998);
    CASE(N = 999);
    CASE(N = 1000);
  }
};
