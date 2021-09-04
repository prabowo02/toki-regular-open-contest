#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 100;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  string S;

  void InputFormat() {
    LINE(N);
  }
  void OutputFormat() {
    LINE(S);
  }
  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(64);
  }
  void Constraints() {
    CONS(1 <= N && N <= MAXN);
  }
  void StyleConfig() {
    CustomScorer();
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
        "2",
    });
    Output({
        "aa",
    });
  }
  void SampleTestCase2() {
    Subtasks({1});
    Input({
        "3",
    });
    Output({
        "ioi",
    });
  }
  void TestGroup1() {
    Subtasks({1});
    CASE(N = 1);
    // CASE(N = 2); Sample 1
    // CASE(N = 3); Sample 2
    CASE(N = 4);
    CASE(N = 5);
    CASE(N = 6);
    CASE(N = 7);
    CASE(N = 8);
    CASE(N = 9);
    CASE(N = 10);
    CASE(N = 11);
    CASE(N = 12);
    CASE(N = 23);
    CASE(N = 46);
    CASE(N = 69);
    CASE(N = 99);
    CASE(N = 100);
  }
};
