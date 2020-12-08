#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAX = 100;

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

  void Constraints() {
    CONS(2 <= N && N <= MAX);
    CONS(2 <= M && M <= MAX);
    CONS(!(N & 1) && !(M & 1));
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
        "2 4",
    });
    Output({
        "8",
    });
  }

  void TestGroup1() {
    Subtasks({1});
    CASE(N = 100, M = 100);
    CASE(N = 2, M = 100);
    CASE(N = 100, M = 2);
    CASE(N = 6, M = 90);
    CASE(N = 4, M = 20);
    CASE(N = 22, M = 8);
  }
};