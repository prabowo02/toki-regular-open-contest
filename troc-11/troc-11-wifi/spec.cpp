#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 100000;
const int MAXA = 1000000000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M;
  vector<int> A;

  int ans;

  void InputFormat() {
    LINE(N, M);
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
    CONS(1 <= M && M <= N && N <= MAXN);
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
      "2",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "5 3",
      "3 1 6 4 5",
    });
    Output({
      "2",
    });
  }

  void BeforeTestCase() {
    A.clear();
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 1; M = 1; A = {rnd.nextInt(1, MAXA)});
    CASE(N = 2; M = 1; A = {1, MAXA});
    CASE(N = 2; M = 2; A = {1, MAXA});

    CASE(N = rnd.nextInt(1, MAXN); N = M; randomArray(N));
    CASE(N = MAXN; M = 1; randomArray(N));
    CASE(N = MAXN; M = rnd.nextInt(2, N-1); randomArray(N));
    CASE(N = MAXN; M = rnd.nextInt(2, N-1); randomArray(N, 100, 110));

    CASE(N = MAXN; M = rnd.nextInt(1, N); sortedArray(N));
    CASE(M = MAXN; M = rnd.nextInt(1, N); sortedArray(N); reverse(A.begin(), A.end()));
    CASE(N = MAXN; M = rnd.nextInt(1, N); sortedArray(N);
         for (int i = 0; i < 5; ++i) swap(A[rnd.nextInt(N)], A[rnd.nextInt(N)]));

    CASE(N = MAXN; M = rnd.nextInt(1, N); sameElementArray(N, rnd.nextInt(1, MAXA)));
    CASE(N = MAXN; M = N; sameElementArray(N, rnd.nextInt(1, MAXA)));
    CASE(N = MAXN; M = 1; sameElementArray(N, rnd.nextInt(1, MAXA)));
    CASE(N = MAXN; M = N; sameElementArray(N, MAXA));

    CASE(N = MAXN; M = N - 10; sameElementWithNoiseArray(N, 1, 10));
    CASE(N = MAXN; M = N - 9; sameElementWithNoiseArray(N, rnd.nextInt(1, MAXA), 10));
    CASE(N = MAXN; M = N - 11; sameElementWithNoiseArray(N, MAXA, 10));
  }

 private:
  void randomArray(int N, int lo=1, int hi=MAXA) {
    for (int i = 0; i < N; ++i) {
      A.push_back(rnd.nextInt(lo, hi));
    }
  }

  void sortedArray(int N, int lo=1, int hi=MAXA) {
    randomArray(N, lo, hi);
    sort(A.begin(), A.end());
  }

  void sameElementArray(int N, int val) {
    randomArray(N, val, val);
  }

  void sameElementWithNoiseArray(int N, int val, int noise=10) {
    assert(N >= noise);
    randomArray(N - noise);
    for (int i = 0; i < noise; ++i) {
      A.push_back(rnd.nextInt(max(1, val-noise), min(MAXA, val+noise)));
    }
    rnd.shuffle(A.begin(), A.end());
  }
};
