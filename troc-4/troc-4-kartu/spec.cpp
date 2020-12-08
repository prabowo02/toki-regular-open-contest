#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
 protected:

  int n;
  double ans;

  void InputFormat() {
    LINE(n);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void Constraints() {
    CONS(1 <= n && n <= 100000);
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
    Input({"3"});
    Output({"2"});
  }

  void TestGroup1() {
    Subtasks({1});

    for (int i = 0; i < 20; ++i) {
      CASE(n = (rand() % 100000) + 1);
      CASE(n = i + 1);
      CASE(n = 100000 - i);
    }
  }
};
