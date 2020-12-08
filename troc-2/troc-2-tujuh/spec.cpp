#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M;
  vector<int> ANS;

  void StyleConfig() {
    CustomScorer();
  }

  void InputFormat() { 
    LINE(N);
  }

  void OutputFormat() { 
    LINE(M);
    LINE(ANS % SIZE(M)); 
  }

  void Constraints() {
    CONS(7 <= N && N <= 10000);
  }

  void Subtask1() {}

};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({"7"});
    Output({"2", "3 4"});
  }
  void TestGroup1() {
    Subtasks({1});
    CASE(N = 10);
    CASE(N = 100);
    CASE(N = 1000);
    CASE(N = 10000);
    CASE(N = 9);
    CASE(N = 433);
    CASE(N = 279);
    CASE(N = 280);
    CASE(N = 256);
    CASE(N = 2199);
    CASE(N = 5401);
    CASE(N = 2520);
    CASE(N = 2521);
    CASE(N = 2519);
    CASE(N = 5040);
    CASE(N = 5039);
    CASE(N = 5041);
    CASE(N = 9972);
    CASE(N = 9973);
    CASE(N = 9974);
    CASE(N = 9997);
    CASE(N = 9998);
    CASE(N = 9999);
    CASE(N = 8);
    CASE(N = 12);
    CASE(N = 24);
  }

};

