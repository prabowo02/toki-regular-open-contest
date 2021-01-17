#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAX = 100;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  std::string ans;

  void InputFormat() {
    LINE(N);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAX);
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
        "5",
    });
    Output({
        "4",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
        "4",
    });
    Output({
        "3",
    });
  }

  void TestGroup1() {
    Subtasks({1});
    CASE(N = 98);
    CASE(N = 99);
    CASE(N = 100);
    CASE(N = 3);
    CASE(N = 6);
    CASE(N = 9);
    CASE(N = 1);
    CASE(N = 7);
    CASE(N = 10);
    CASE(N = 13);
    CASE(N = 2);
    CASE(N = 8);
    CASE(N = 11);
  }
};