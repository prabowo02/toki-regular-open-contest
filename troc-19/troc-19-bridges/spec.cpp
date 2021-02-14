#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAX = 40;
const int MOD = 998244353;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M;
  int A, B, C;
  int ans;

  void InputFormat() {
    LINE(N, M, A, B, C);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAX);
    CONS(1 <= M && M <= MAX);
    CONS(0 <= A && A < MOD);
    CONS(0 <= B && B < MOD);
    CONS(0 <= C && C < MOD);
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
      "3 3 0 0 1",
    });
    Output({
      "748683265",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "4 6 1 2 3",
    });
    Output({
      "613309362",
    });
  }

  void SampleTestCase3() {
    Subtasks({1});
    Input({
      "5 8 12 13 14",
    });
    Output({
      "232699642",
    });
  }

  void TestGroup1() {
    Subtasks({1});
    CASE(N = 1;   M = 1;  A = 0;                       B = 0;                       C = 0                      );
    CASE(N = 40;  M = 40; A = MOD - 1;                 B = MOD - 1;                 C = MOD - 1                );
    CASE(N = 1;   M = 1;  A = 12345678901234567 % MOD; B = 12975723985729057 % MOD; C = 12743897192347911 % MOD);
    CASE(N = 40;  M = 1;  A = 92769827589273458 % MOD; B = 29673290475927554 % MOD; C = 52620394568923745 % MOD);
    CASE(N = 1;   M = 40; A = 23769328759273582 % MOD; B = 25749823749827139 % MOD; C = 98690258092385928 % MOD);
    CASE(N = 37;  M = 11; A = 53497693487532595 % MOD; B = 23673289572375984 % MOD; C = 23954932875902854 % MOD);
    CASE(N = 12;  M = 33; A = 23974520985029930 % MOD; B = 94320912093528985 % MOD; C = 42582095802845029 % MOD);
    CASE(N = 32;  M = 25; A = 23579283475297597 % MOD; B = 23452895029849028 % MOD; C = 56803495860329850 % MOD);
    CASE(N = 36;  M = 39; A = 98127359827598725 % MOD; B = 78923752897598357 % MOD; C = 52384589239058032 % MOD);
    CASE(N = 40;  M = 40; A = 27592840850928304 % MOD; B = 52395029502859025 % MOD; C = 26429850298509284 % MOD);
  }
};
