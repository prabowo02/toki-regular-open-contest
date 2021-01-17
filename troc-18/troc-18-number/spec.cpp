#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAX = 100;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M;
  std::string ans;

  void InputFormat() {
    LINE(N);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void StyleConfig() {
    CustomScorer();
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
        "YES",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
        "7",
    });
    Output({
        "NO",
    });
  }

  void TestGroup1() {
    Subtasks({1});
    CASE(N = 100);
    CASE(N = 1);
    CASE(N = 2);
    CASE(N = 3);
    CASE(N = 4);
    CASE(N = 6);
    CASE(N = 11);
    CASE(N = 13);
    CASE(N = 50);
    CASE(N = 97);
  }
};