#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAXN = 100000;
const int MAXK = 100000;
const int MAX_VAL = 1000000000;

class ProblemSpec : public BaseProblemSpec {
 protected:

  int N, K;
  vector<int> A;
  int ANS;

  void InputFormat() {
    LINE(N, K);
    LINE(A % SIZE(N));
  }

  void OutputFormat() {
    LINE(ANS);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(1 <= K && K <= MAXK);
    CONS(eachElementsBetween(A, 0, MAX_VAL));
  }

  void Subtask1() {}

 private:
  bool eachElementsBetween(vector<int> &v, int lo, int hi) {
    return all_of(v.begin(), v.end(), [&](int x) {
      return lo <= x && x <= hi;
    });
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:

  void SampleTestCase1() {
    Subtasks({1});

    Input({
      "3 1",
      "7 1 2"
    });

    Output({"28"});
  }

  void SampleTestCase2() {
    Subtasks({1});

    Input({
      "3 2",
      "7 1 2"
    });

    Output({"280"});
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 1, K = 1, A = {0});
    CASE(N = 1, K = 1, A = {MAX_VAL});
    CASE(N = MAXN, K = MAXK, A = randomArray(N, MAX_VAL, MAX_VAL));

    for (int i = 0 ; i < 10 ; i++) {
      CASE(N = MAXN, K = MAXK, A = randomArray(N, 0, MAX_VAL));
      CASE(N = MAXN, K = rnd.nextInt(1, MAXK), A = randomArray(N, 0, MAX_VAL));
      CASE(N = rnd.nextInt(1, MAXN), K = MAXK, A = randomArray(N, 0, MAX_VAL));
      CASE(N = rnd.nextInt(1, MAXN), K = rnd.nextInt(1, MAXK), A = randomArray(N, 0, MAX_VAL));
    }
  }

 private:
  vector<int> randomArray(int n, int low, int hi) {
    vector<int> ret(n);
    for (int &x : ret) {
      x = rnd.nextInt(low, hi);
    }
    return ret;
  }
};
