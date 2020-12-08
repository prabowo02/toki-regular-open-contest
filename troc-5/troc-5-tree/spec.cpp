#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAXD = 100000;
const int MAXK = 10;

class ProblemSpec : public BaseProblemSpec {
 protected:

  int D, K;
  int ANS;

  void InputFormat() {
    LINE(D, K);
  }

  void OutputFormat() {
    LINE(ANS);
  }

  void Constraints() {
    CONS(1 <= D && D <= MAXD);
    CONS(1 <= K && K <= MAXK);
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

    Input({ "2 1"});
    Output({"2"});
  }

  void SampleTestCase2() {
    Subtasks({1});

    Input({"3 2"});
    Output({"8"});
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(D = MAXD, K = MAXK);
    for (int d = 1 ; d <= 4 ; d++)
      for (int k = 1 ; k <= (1 << (d-1))+1 ; k++)
        CASE(D = d, K = k);

    for (int i = 0 ; i < 20 ; i++) {
      CASE(D = rnd.nextInt(1, MAXD), K = rnd.nextInt(1, MAXK));
      CASE(D = rnd.nextInt(MAXD / 2, MAXD), K = rnd.nextInt(1, MAXK));
    }
  }

 private:
};
