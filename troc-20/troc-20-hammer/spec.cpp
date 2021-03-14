#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAX = 10000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int X, Y;
  string ANS;

  void InputFormat() {
    LINE(X, Y);
  }

  void OutputFormat() {
    LINE(ANS);
  }

  void Constraints() {
    CONS(1 <= X && X <= MAX);
    CONS(1 <= Y && Y <= MAX);
    CONS(X != Y);
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Input({
      "8000 7999",
    });
    Output({
      "YES",
    });
  }

  void SampleTestCase2() {
    Input({
      "1 100",
    });
    Output({
      "NO",
    });
  }

  void TestGroup1() {
    CASE(X = 2; Y = 1);
    CASE(X = 1; Y = 2);
    CASE(X = MAX - 1; Y = MAX);
    CASE(X = MAX; Y = MAX - 1);
    CASE(X = 1; Y = MAX);
    CASE(X = MAX; Y = 1);
    CASE(X = 69; Y = 420);
    CASE(X = 12; Y = 73);
    CASE(X = 228; Y = 992);
  }
};
