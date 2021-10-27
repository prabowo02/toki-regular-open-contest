#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  string ans;

  void InputFormat() {
    LINE(N);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(64);
  }

  void Constraints() {
    CONS(1 <= N && N <= 100);
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Input({
      "16",
    });
    Output({
      "YES",
    });
  }

  void SampleTestCase2() {
    Input({
      "45",
    });
    Output({
      "NO",
    });
  }

  void TestGroup1() {
    CASE(N = 1);
    CASE(N = 5);
    CASE(N = 12);
    CASE(N = 27);
    CASE(N = 32);
    CASE(N = 77);
    CASE(N = 81);
    CASE(N = 99);
    CASE(N = 100);
  }
};
