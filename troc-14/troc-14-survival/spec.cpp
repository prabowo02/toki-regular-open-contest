#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 200000;
const int MAXVAL = 1000000000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, D;
  vector<int> T, R, C;

  int ans;

  void InputFormat() {
    LINE(N, D);
    LINES(T, R, C) % SIZE(N);
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
    CONS(N <= D && D <= MAXVAL);
    CONS(eachElementBetween(T, 1, D));
    CONS(eachElementBetween(R, 1, MAXVAL));
    CONS(eachElementBetween(C, 1, MAXVAL));
  }

  void Subtask1() {
    Points(100);
  }

 private:
  bool eachElementBetween(const vector<int> &A, int lo, int hi) {
    return all_of(A.begin(), A.end(), [&lo, &hi](int x) { 
      return lo <= x && x <= hi;
    });
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "1 5",
      "2 4 3",
    });
    Output({
      "2",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "5 20",
      "1 3 5",
      "7 10 3",
      "11 5 10",
      "12 2 10",
      "19 10 10",
    });
    Output({
      "2",
    });
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 1; D = MAXVAL; R = {1}; C = {MAXVAL}; T = {1});
    CASE(N = 1; D = MAXVAL; R = {MAXVAL/2}; C = {1000}; T = {MAXVAL/2});
    CASE(N = 1; D = 2; R = {1}; C = {1}; T = {1});
    CASE(N = 1; D = MAXVAL; R = {MAXVAL}; C = {1}; T = {MAXVAL});
    CASE(N = 1; D = 10; T = {4}; R = {4}; C = {2});
    CASE(N = 1; D = 10; T = {5}; R = {1}; C = {6});

    CASE(randomCase());
    CASE(randomCase(true));
    CASE(maxTest());
    CASE(fewAids());
    CASE(lotOfAids());

    CASE(smallThreshold());
    CASE(largeThreshold());
    CASE(stingyGovernment());
    CASE(aidEveryday());
  }

 private:
  void randomCase(bool maxN=false) {
    N = (maxN ? MAXN : rnd.nextInt(1, MAXN));
    D = (maxN ? MAXVAL : rnd.nextInt(N+1, MAXVAL));
    R = randomArray(N);
    C = randomArray(N);
    T = distinctArray(N, 1, D);
    sort(T.begin(), T.end());
  }

  void maxTest() {
    N = MAXN;
    D = MAXVAL;
    R = randomArray(N, MAXVAL, MAXVAL);
    C = randomArray(N, MAXVAL, MAXVAL);
    T = distinctArray(N, 1, D);
    sort(T.begin(), T.end());
  }

  void fewAids() {
    N = rnd.nextInt(1, MAXN);
    D = rnd.nextInt(N+1, MAXVAL);
    R = randomArray(N);
    C = randomArray(N, 1, 100);
    T = distinctArray(N, 1, D);
    sort(T.begin(), T.end());
  }

  void lotOfAids() {
    N = rnd.nextInt(1, MAXN);
    D = rnd.nextInt(N+1, MAXVAL);
    R = randomArray(N);
    C = randomArray(N, MAXVAL-100, MAXVAL);
    T = distinctArray(N, 1, D);
    sort(T.begin(), T.end());
  }

  void smallThreshold() {
    N = rnd.nextInt(1, MAXN);
    D = rnd.nextInt(N+1, MAXVAL);
    R = randomArray(N, 1, 100);
    C = randomArray(N);
    T = distinctArray(N, 1, D);
    sort(T.begin(), T.end());
  }

  void largeThreshold() {
    N = rnd.nextInt(1, MAXN);
    D = rnd.nextInt(N+1, MAXVAL);
    R = randomArray(N, MAXVAL-100, MAXVAL);
    C = randomArray(N);
    T = distinctArray(N, 1, D);
    sort(T.begin(), T.end());
  }

  void stingyGovernment() {
    N = rnd.nextInt(MAXN/2, MAXN);
    D = rnd.nextInt(MAXVAL/2, MAXVAL);
    R = randomArray(N, 1, 100);
    C = randomArray(N, 1, 100);
    T = distinctArray(N, 1, D);
    sort(T.begin(), T.end());
  }

  void aidEveryday() {
    N = MAXN;
    D = N;
    R = randomArray(N, 1, MAXVAL);
    C = randomArray(N, 1, MAXVAL);
    T = distinctArray(N, 1, D);
    sort(T.begin(), T.end());
  }

  vector<int> randomArray(int n, int lo=1, int hi=MAXVAL) {
    vector<int> ret(n);
    for (int i = 0; i < n; ++i) {
      ret[i] = rnd.nextInt(lo, hi);
    }
    return ret;
  }

  vector<int> distinctArray(int n, int lo=1, int hi=MAXVAL) {
    if (hi-lo+1 > n*2) {
      set<int> s;
      while (s.size() < n) s.insert(rnd.nextInt(lo, hi));
      return vector<int>(s.begin(), s.end());
    } else {
      vector<int> v(hi-lo+1);
      iota(v.begin(), v.end(), lo);
      rnd.shuffle(v.begin(), v.end());
      return vector<int>(v.begin(), v.begin() + n);
    }
  }
};
