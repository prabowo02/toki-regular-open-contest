#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

const int MAXC = 100000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int C;
  int A, B;

  void InputFormat() {
    LINE(C);
  }

  void OutputFormat() {
    LINE(A, B);
  }

  void StyleConfig() {
    CustomScorer();
  }

  void Constraints() {
    CONS(1 <= C && C <= MAXC);
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Input({
      "3"
    });
    Output({
      "11 4"
    });
  }

  void TestGroup1() {
    CASE(C = 1);
    CASE(C = 2);
    CASE(C = 3);
    CASE(C = 4);
    CASE(C = 69);
    CASE(C = 420);

    CASE(C = rnd.nextInt(1000, MAXC - 10));
    CASE(C = rnd.nextInt(1000, MAXC - 10));
    CASE(C = rnd.nextInt(1000, MAXC - 10));
    CASE(C = rnd.nextInt(1000, MAXC - 10));
    CASE(C = rnd.nextInt(1000, MAXC - 10));
    CASE(C = rnd.nextInt(1000, MAXC - 10));
    CASE(C = rnd.nextInt(1000, MAXC - 10));
    CASE(C = rnd.nextInt(1000, MAXC - 10));

    CASE(C = MAXC - 3);
    CASE(C = MAXC - 2);
    CASE(C = MAXC - 1);
    CASE(C = MAXC);

    // High composite numbers
    CASE(C = 83160);
    CASE(C = 55440);
    CASE(C = 50400);
    CASE(C = 45360);
  }
};
