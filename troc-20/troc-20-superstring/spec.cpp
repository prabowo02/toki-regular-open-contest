#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 100000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  int answer;

  void InputFormat() {
    LINE(N);
  }

  void OutputFormat() {
    LINE(answer);
  }

  void GradingConfig() {
    TimeLimit(5);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
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
      "3",
    });
    Output({
      "499122177",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "5",
    });
    Output({
      "873463810",
    });
  }

  void BeforeTestCase() {
    N = 0;
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 1);
    CASE(N = 2);
    // CASE(N = 3); // sample
    CASE(N = 4);
    // CASE(N = 5); // sample
    CASE(N = 6);
    CASE(N = 7);
    CASE(N = 8);
    CASE(N = 9);

    CASE(N = rnd.nextInt(10, 50));
    CASE(N = rnd.nextInt(10, 50));

    CASE(N = rnd.nextInt(100, 500));
    CASE(N = rnd.nextInt(100, 500));

    CASE(N = rnd.nextInt(1000, 5000));
    CASE(N = rnd.nextInt(1000, 5000));

    CASE(N = rnd.nextInt(10000, 50000));
    CASE(N = rnd.nextInt(10000, 50000));

    CASE(N = rnd.nextInt(80000, 100000));
    CASE(N = rnd.nextInt(80000, 100000));

    CASE(N = 90909);
    CASE(N = 99999);
    CASE(N = 100000);
  }
};
