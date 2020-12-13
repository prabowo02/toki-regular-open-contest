#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 200;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M;
  string ans;

  void InputFormat() {
    LINE(N, M);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(1 <= M && M <= MAXN);
    CONS(N % 2 == 0);
    CONS(M % 2 == 0);
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Input({
      "4 4",
    });
    Output({
      "Yes",
    });
  }

  void SampleTestCase2() {
    Input({
      "6 4",
    });
    Output({
      "No",
    });
  }

  void TestGroup1() {
    CASE(N = 2; M = 2); // No
    CASE(N = 2; M = 4); // No
    CASE(N = 4; M = 2); // No
    CASE(N = 4; M = 8); // Yes
    CASE(N = 200; M = 2); // No
    CASE(N = 2; M = 200); // No
    CASE(N = 4; M = 100); // Yes
    CASE(N = 200; M = 200); // Yes
    CASE(N = rnd.nextInt(1, (int)MAXN / 2) * 2; M = rnd.nextInt(1, (int)MAXN / 2) * 2);
    CASE(N = rnd.nextInt(1, (int)MAXN / 2) * 2; M = rnd.nextInt(1, (int)MAXN / 2) * 2);
    CASE(N = rnd.nextInt(1, (int)MAXN / 2) * 2; M = rnd.nextInt(1, (int)MAXN / 2) * 2);
    CASE(N = rnd.nextInt(1, (int)MAXN / 2) * 2; M = rnd.nextInt(1, (int)MAXN / 2) * 2);
  }
};
