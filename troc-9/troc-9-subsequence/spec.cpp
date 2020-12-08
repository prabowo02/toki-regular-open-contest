#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 100000;
const int MAXA = 1000000000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, K;
  vector<int> A;

  long long ans;

  void InputFormat() {
    LINE(N, K);
    LINE(A % SIZE(N));
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(64);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(1 <= K && K <= N);
    CONS(eachElementBetween(A, 1, MAXA));
  }

  void Subtask1() {
      Points(100);
  }

 private:

  bool eachElementBetween(const vector<int> &A, int lo, int hi) {
    for (int a: A) {
      if (a < lo || a > hi) return false;
    }

    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "3 3",
      "1 2 3",
    });
    Output({
      "4",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "3 1",
      "7 8 2",
    });
    Output({
      "0",
    });
  }

  void SampleTestCase3() {
    Subtasks({1});
    Input({
      "4 2",
      "1 3 7 3",
    });
    Output({
      "6",
    });
  }

  void BeforeTestCase() {
    A.clear();
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 10; K = 5; randomArray(N));
    CASE(N = rnd.nextInt(1, MAXN); K = rnd.nextInt(1, K); randomArray(N));

    CASE(N = MAXN; K = 1; randomArray(N));
    CASE(N = MAXN; K = 2; randomArray(N));
    CASE(N = MAXN; K = 3; randomArray(N));
    CASE(N = MAXN; K = N-2; randomArray(N));
    CASE(N = MAXN; K = N-1; randomArray(N));
    CASE(N = MAXN; K = N; randomArray(N));

    CASE(N = MAXN-1; K = N-2; randomArray(N));
    CASE(N = MAXN-1; K = N-1; randomArray(N));
    CASE(N = MAXN-1; K = 3; randomArray(N));
    CASE(N = MAXN-1; K = rnd.nextInt(1, N); randomArray(N));

    CASE(N = MAXN; K = rnd.nextInt(1, N); randomArray(N));
    CASE(N = MAXN; K = rnd.nextInt(1, N); increasingArray(N));
    CASE(N = MAXN; K = rnd.nextInt(1, N); decreasingArray(N));
    CASE(N = MAXN; K = rnd.nextInt(1, N); fewDistinctArray(N));
    CASE(N = MAXN; K = rnd.nextInt(1, N); maxTest(N));

    CASE(N = MAXN; K = N; maxTest(N));
  }

 private:

  void randomArray(int N) {
    for (int i = 0; i < N; ++i) {
      A.push_back(rnd.nextInt(1, MAXA));
    }
  }

  void increasingArray(int N) {
    randomArray(N);
    sort(A.begin(), A.end());
  }

  void decreasingArray(int N) {
    increasingArray(N);
    reverse(A.begin(), A.end());
  }

  void fewDistinctArray(int N) {
    for (int i = 0; i < N; ++i) {
      A.push_back(rnd.nextInt(1, 10));
    }
  }

  void maxTest(int N) {
    for (int i = 0; i < N/2; ++i) {
      A.push_back(1);
    }
    for (int i = N/2; i < N; ++i) {
      A.push_back(MAXA);
    }
  }
};
