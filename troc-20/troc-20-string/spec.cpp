#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 3000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  string S;
  int answer;

  void InputFormat() {
    LINE(N);
    LINE(S);
  }

  void OutputFormat() {
    LINE(answer);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(S.size() == N);
    CONS(count(begin(S), end(S), '0') + count(begin(S), end(S), '1') + count(begin(S), end(S), '?') == N);
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
      "???",
    });
    Output({
      "499122177",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "5",
      "11?00",
    });
    Output({
      "2",
    });
  }

  void SampleTestCase3() {
    Subtasks({1});
    Input({
      "5",
      "10000",
    });
    Output({
      "1",
    });
  }

  void SampleTestCase4() {
    Subtasks({1});
    Input({
      "10",
      "1?0?1?0??0",
    });
    Output({
      "187170820",
    });
  }

  void BeforeTestCase() {
    N = 0;
    S.clear();
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 1; Generate(0, 0));
    CASE(N = 1; Generate(0, 1));
    CASE(N = 1; Generate(1, 0));

    CASE(N = 2; Generate(0, 0));
    CASE(N = 4; Generate(1, 2));
    CASE(N = 6; Generate(2, 2));
    CASE(N = 7; Generate(3, 1));
    CASE(N = 8; Generate(0, 5));
    CASE(N = 9; Generate(3, 3));

    CASE(N = rnd.nextInt(2900, 3000); Generate(0, 0));
    CASE(N = rnd.nextInt(2900, 3000); Generate(0, N));
    CASE(N = rnd.nextInt(2900, 3000); Generate(N, 0));

    CASE(N = rnd.nextInt(2900, 3000); Generate(0, N / 2));
    CASE(N = rnd.nextInt(2900, 3000); Generate(N / 2, 0));
    CASE(N = rnd.nextInt(2900, 3000); Generate(N / 2, N - N / 2));

    CASE(N = rnd.nextInt(2900, 3000); Generate(N / 3, N / 3));

    CASE(N = rnd.nextInt(10, 50); Generate(rnd.nextInt(N / 3), rnd.nextInt(N / 3)));
    CASE(N = rnd.nextInt(100, 500); Generate(rnd.nextInt(N / 3), rnd.nextInt(N / 3)));
    CASE(N = rnd.nextInt(1000, 2000); Generate(rnd.nextInt(N / 3), rnd.nextInt(N / 3)));
    CASE(N = rnd.nextInt(2900, 3000); Generate(rnd.nextInt(N / 3), rnd.nextInt(N / 3)));

    CASE(N = 3000; Generate(rnd.nextInt(N / 2), rnd.nextInt(N / 2)));
    CASE(N = 3000; Generate(rnd.nextInt(N / 3), rnd.nextInt(N / 3)));
    CASE(N = 3000; Generate(rnd.nextInt(N / 2), rnd.nextInt(N / 4)));
    CASE(N = 3000; Generate(rnd.nextInt(N / 4), rnd.nextInt(N / 2)));
    CASE(N = 3000; Generate(rnd.nextInt(N / 4), rnd.nextInt(N / 4)));
  }

 private:
  void Generate(int zero, int one) {
    assert(one + zero <= N);
    for (int i = 0; i < zero; i++) S.push_back('0');
    for (int i = 0; i < one; i++) S.push_back('1');
    while (S.size() < N) S.push_back('?');
    rnd.shuffle(begin(S), end(S));
  }
};
