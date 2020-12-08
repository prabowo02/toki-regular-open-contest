#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAX_N = 2000;
const int MAX_X = 1e9;
const int MAX_Y = 1000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, P, T, V, D;
  vector<int> X, H;
  double ANS;

  void StyleConfig() {
    CustomScorer();
  }

  void InputFormat() { 
    LINE(N, P, T, V, D);
    LINE(X % SIZE(N));
    LINE(H % SIZE(N));
  }

  void OutputFormat() {
    LINE(ANS);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAX_N);
    CONS(1 <= P && P <= MAX_X);
    CONS(1 <= T && T <= MAX_Y);
    CONS(1 <= V && V <= MAX_X);
    CONS(1 <= D && D <= MAX_Y);
    CONS(X.size() == N && H.size() == N);
    CONS(eachElementBetween(X, 1, MAX_X));
    CONS(strictlyIncreasing(X));
    CONS(eachElementBetween(H, 1, MAX_Y));
  }

  void Subtask1() {
  }

 private:
  bool eachElementBetween(const vector<int> &v, int lo, int hi) {
    return all_of(v.begin(), v.end(), [lo, hi](int x) {
      return lo <= x && x <= hi;
    });
  }
  bool strictlyIncreasing(const vector<int> &v) {
    for (int i = 0; i+1 < v.size(); ++i)
      if (v[i] >= v[i+1])
        return false;
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});

    Input({"3 4 4 2 3", "2 4 10", "3 1 2"});
    Output({"33.0"});
  }

  void BeforeTestCase() {
    X.clear();
    H.clear();
  }

  void AfterTestCase() {
  }

  void TestGroup1() {
    Subtasks({1});

    // test corner case and precision
    CASE(N = 1, P = 1, T = 1, V = 1, D = 1, X = {1}, H = {2}); // ANS = 0
    CASE(N = 1, P = 1, T = 2, V = MAX_X, D = 1, X = {1}, H = {1});  // ANS = 1e-9
    CASE(N = 1, P = 2, T = 2, V = MAX_X, D = MAX_Y, X = {1}, H = {1});  // ANS = 2e-6
    CASE(N = 1, P = 1, T = 4, V = int(1e7), D = int(1e2), X = {1}, H = {1});  // ANS = 3e-5
    CASE(N = 1, P = 1, T = MAX_Y, V = MAX_X, D = MAX_Y, X = {1}, H = {1});  // ANS = 999/1e6
    CASE(N = 1, P = 1, T = MAX_Y, V = MAX_Y, D = MAX_Y, X = {1}, H = {MAX_Y-1});  // ANS = 1
    CASE(N = 2, P = MAX_X, T = MAX_Y, V = 1, D = MAX_Y, X = {1, MAX_X}, H = {1, 1}); // ANS = MAX = 999 * (2e9 - 1) * 1000

    CASE(N = MAX_N, P = MAX_X, T = MAX_Y, V = MAX_X, D = MAX_Y, randomX(), randomH());
    CASE(N = MAX_N, P = MAX_X, T = MAX_Y, V = 1, D = MAX_Y, randomX(), randomH());
    CASE(N = MAX_N, P = 1, T = MAX_Y, V = 1, D = 1, randomX(), randomH());

    // small manual
    CASE(N = 5, P = 5, T = 13, V = 7, D = 22, X = {1, 2, 3, 5, 8}, H = {3, 14, 1, 5, 9});
    CASE(N = 7, P = 13, T = 29, V = 101, D = 37, X = {1, 3, 5, 13, 73, MAX_X-3, MAX_X}, H = {3, 14, 15, 9, 26, 5, 3});

    CASE(denseDist(int(1e4)));
    CASE(denseDist(int(1e5)));
    CASE(sparseDist(int(1e6)));
    CASE(sparseDist(int(5e7)));
    CASE(sparseDist(MAX_X));

    CASE(N = rnd.nextInt(MAX_N/2, MAX_N), manyHOverT(rnd.nextInt(N/2, N)));
    CASE(N = MAX_N, manyHOverT(rnd.nextInt(N-100, N-10)));
    CASE(N = MAX_N, manyHOverT(N));

    for (int i = 0; i < 5; ++i) {
      CASE(fullRandom());
    }
  }

 private:

  void randomX(int xmax = MAX_X) {
    set<int> sx;
    while (sx.size() < N) {
      sx.insert(rnd.nextInt(1, xmax));
    }
    X.clear();
    for (int val : sx)
      X.push_back(val);
  }

  void randomH(int hmax = MAX_Y) {
    H.resize(N);
    for (int i = 0; i < N; ++i)
      H[i] = rnd.nextInt(1, hmax);
  }

  void denseDist(int span) {
    N = MAX_N;
    P = span;
    T = MAX_Y;
    V = rnd.nextInt(1, MAX_Y);
    D = rnd.nextInt(1, MAX_Y);
    randomX(span);
    randomH(T-1);
  }

  void sparseDist(int span) {
    N = MAX_N;
    int b = span/N;
    P = rnd.nextInt(1, b-1);
    T = MAX_Y;
    V = rnd.nextInt(1, MAX_X);
    D = rnd.nextInt(1, MAX_Y);
    X.resize(N);
    for (int i = 0; i < N; ++i)
      X[i] = 1 + b * i;
    randomH(T-1);
  }

  void manyHOverT(int up) {
    P = rnd.nextInt(1, MAX_X);
    T = rnd.nextInt(1, MAX_Y/2);
    V = rnd.nextInt(1, MAX_X);
    D = rnd.nextInt(1, MAX_Y);
    randomX();
    H.resize(N);
    for (int i = 0; i < up; ++i) {
      H[i] = rnd.nextInt(T+1, MAX_Y);
    }
    for (int i = up; i < N; ++i) {
      H[i] = rnd.nextInt(1, T-1);
    }
    rnd.shuffle(H.begin(), H.end());
  }

  void fullRandom() {
    N = rnd.nextInt(1, MAX_N);
    P = rnd.nextInt(1, MAX_X);
    T = rnd.nextInt(1, MAX_Y);
    V = rnd.nextInt(1, MAX_X);
    D = rnd.nextInt(1, MAX_Y);
    randomX();
    randomH();
  }
};