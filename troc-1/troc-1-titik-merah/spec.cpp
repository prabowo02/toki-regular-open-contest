#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, R, V;
  vector<int> W;
  double ANS;

  void StyleConfig() {
    CustomScorer();
  }

  void InputFormat() { 
    LINE(N, R, V);
    LINE(W % SIZE(N));
  }

  void OutputFormat() { LINE(ANS); }

  void Constraints() {
    CONS(1 <= N && N <= 100);
    CONS(1 <= R && R <= 1000);
    CONS(1 <= V && V <= 1000);
    CONS(eachElementBetween(W, 1, 1000));
  }

  void Subtask1() {}

 private:
  bool eachElementBetween(const vector<int> &v, int lo, int hi) {
    return all_of(v.begin(), v.end(), [lo, hi](int x) {
      return lo <= x && x <= hi;
    });
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});

    Input({"4 20 10", "5 7 14 16"});
    Output({"6.666666667"});
  }

  void SampleTestCase2() {
    Subtasks({1});

    Input({"1 20 10", "10"});
    Output({"-1"});
  }

  void BeforeTestCase() { W.clear(); }

  void AfterTestCase() { rnd.shuffle(begin(W), end(W)); }

  void TestGroup1() {
    Subtasks({1});

    // test corner case and precision
    CASE(N = 1; R = 1; V = 1; W = {1});
    CASE(N = 1; R = 1; V = 1; W = {1000});
    CASE(N = 1; R = 1; V = 1000; W = {1});
    CASE(N = 1; R = 1; V = 999; W = {1000});
    CASE(N = 1; R = 1; V = 1000; W = {999});
    CASE(N = 1; R = 1000; V = 1000; W = {1});
    CASE(N = 1; R = 1000; V = 1000; W = {2});
    CASE(N = 4; R = 1000; V = 1000; W = {1, 2, 998, 999});

    for (int i = 0; i < 5; i++) {
      CASE(crowdedLineSweep(rnd.nextInt(1, 100)));
    }
    CASE(crowdedLineSweep(0));
    CASE(crowdedLineSweep(100));
    CASE(crowdedLineSweep(99));
    CASE(crowdedLineSweep(-100));
    CASE(crowdedLineSweep(-150));
    CASE(crowdedLineSweep(-200));
    CASE(crowdedLineSweep(100));
    CASE(crowdedLineSweep(150));
    CASE(crowdedLineSweep(200));

    for (int i = 0; i < 5; i++) {
      CASE(fullRandom());
    }
  }

 private:

  void crowdedLineSweep(int left) {
    N = 100;
    R = rnd.nextInt(1000);
    V = rnd.nextInt(300, 500);
    W.resize(N);
    for (int i = 0; i < N; i++) {
      W[i] = V - left + i;
    }
  }

  void fullRandom() {
    N = rnd.nextInt(1, 100);
    R = rnd.nextInt(1000);
    V = rnd.nextInt(1000);
    W.resize(N);
    for (int i = 0; i < N; i++) {
      W[i] = rnd.nextInt(1, 1000);
    }
  }
};

