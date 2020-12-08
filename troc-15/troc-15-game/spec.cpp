#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;
constexpr int MAXN = 5000;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N, D, A, B;
  int ANS;
  void InputFormat() {
    LINE(N, D, A, B);
  }

  void OutputFormat(){
    LINE(ANS);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(128);
  }

  void Constraints() {
    CONS((2 <= N) && (N <= MAXN));
    CONS((1 <= D) && (D < N));
    CONS((1 <= A) && (A < N));
    CONS((1 <= B) && (B < N));
  }

  void Subtask1(){
    Points(100);
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "5 2 1 3"
    });
    Output({
      "748683265"
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "5 2 3 1"
    });
    Output({
      "124780545"
    });
  }

  void TestGroup1(){
    Subtasks({1});

    CASE(N = 2; D = 1; A = 1, B = 1);
    CASE(N = 3; D = 1; A = 1, B = 2);
    CASE(N = 3; D = 2; A = 1, B = 2);
    CASE(N = 4; D = 3; A = 1, B = 3);

    CASE(N = rnd.nextInt(200, 300); D = 40; A = 1, B = sqrt(N));
    CASE(N = rnd.nextInt(200, 300); D = 2; A = N/5, B = sqrt(N));
    CASE(N = rnd.nextInt(200, 300); D = sqrt(N); A = sqrt(N), B = N/6);

    CASE(N = MAXN; D = N/3; A = 14, B = MAXN-1);
    CASE(N = MAXN; D = sqrt(N); A = N/3, B = N/5);

    CASE(N = MAXN; D = N/2; A = 1; B = 2);
    CASE(N = MAXN; D = N-1; A = 2; B = 1);
    CASE(N = MAXN; D = rnd.nextInt(N/2, N-1); A = N-1; B = rnd.nextInt(3*N/4, N-1));

    CASE(N = rnd.nextInt(2000, MAXN/2); D = N/50; A = N/5, B = N/3);
    CASE(N = rnd.nextInt(1, MAXN/2); D = sqrt(N); A = 1, B = sqrt(N));
    CASE(N = rnd.nextInt(1, MAXN/2); D = min((int)(sqrt(N)), 30); A = N/4, B = sqrt(N));
    CASE(N = rnd.nextInt(1, MAXN/2); D = min((int)(sqrt(N)), 10); A = sqrt(N); B = N/8);
    CASE(N = rnd.nextInt(1, MAXN/2); D = min((int)(sqrt(N)), 30); A = N/3; B = N/12);
    CASE(N = rnd.nextInt(1, MAXN/2); D = int(sqrt(N)); A = N/15; B = N/4);
  }
};
