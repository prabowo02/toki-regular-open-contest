#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAXM = 2000;

class ProblemSpec : public BaseProblemSpec {
 protected:

  int A, B, M;
  int ANS;

  void InputFormat() {
    LINE(A, B, M);
  }

  void OutputFormat() {
    LINE(ANS);
  }

  void Constraints() {
    CONS(1 <= M && M <= MAXM);
    CONS(0 <= A && A < M);
    CONS(0 <= B && B < M);
  }

  void Subtask1() {
    Points(100);
  }

 private:
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:

  void SampleTestCase1() {
    Subtasks({1});
    Input({ "0 1 5"});
    Output({"5"});
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({"4 2 6"});
    Output({"3"});
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(M = 1,
         A = 0, B = 0);
    CASE(M = MAXM,
         A = 0, B = 0);
    CASE(M = MAXM,
         A = 0, B = 1);
    CASE(M = MAXM,
         A = 1, B = 1);
    CASE(M = MAXM,
         A = 2, B = 1);

    CASE(M = 1250,
         A = 1, B = 2);

    for (int i = 0 ; i < 10 ; i++) {
      CASE(M = rnd.nextInt(1, MAXM),
           A = rnd.nextInt(M), B = rnd.nextInt(M));
      CASE(M = rnd.nextInt(1, MAXM),
           A = rnd.nextInt(M), B = rnd.nextInt(M));

      CASE(buildCaseCommonDivisor(rnd.nextInt(2, MAXM)));
      CASE(buildCaseCommonDivisor(rnd.nextInt(2, 100)));
      CASE(buildCaseCommonDivisor(rnd.nextInt(2, 10)));
    }
  }

 private:
  
  void buildCaseCommonDivisor(int divs) {
    int m = rnd.nextInt(1, MAXM / divs);
    int a = rnd.nextInt(m);
    int b = rnd.nextInt(m);

    M = m * divs;
    A = a * divs;
    B = b * divs;
  }
};
