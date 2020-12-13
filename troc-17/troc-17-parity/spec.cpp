#include <tcframe/spec.hpp>
using namespace tcframe;
const int N_LIM = 100;
const int ELM_MAX = 100;
const int ELM_MIN = 1;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N;
  vector <int> base, ex;
  int answer;

  void InputFormat() {
    LINE(N);
    LINE(base % SIZE(N));
    LINE(ex % SIZE(N));
  }

  void OutputFormat() {
    LINE(answer);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= N && N <= N_LIM);
    CONS(withinBounds(base , N));
    CONS(withinBounds(ex , N));
  }
private:
  bool withinBounds(vector <int> &v , int N) {
    for (int i = 0 ; i < N ; i++) {
      if (v[i] < ELM_MIN || v[i] > ELM_MAX) return 0;
    }
    return 1;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Input({
      "5",
      "2 4 6 8 2",
      "1 2 3 4 5",
    });
    Output({
      "0",
    });
  }

  void SampleTestCase2() {
    Input({
      "1",
      "11",
      "11",
    });
    Output({
      "1",
    });
  }

  void TestGroup1() {
    CASE(N = 1, base = {1}, ex = {1});
    CASE(N = 1, base = {100}, ex = {1});
    CASE(N = 1, base = {1}, ex = {100});
    CASE(N = 1, base = {99}, ex = {99});
    CASE(N = 1, base = {100}, ex = {100});
    CASE(N = 2, base = {50, 99}, ex = {99, 50});

    CASE(randomVector(10));
    CASE(randomVector(10));

    CASE(randomVector(100));
    CASE(randomVector(100));

    CASE(N = 100, base = filledVector(100, 1), ex = filledVector(100, 1));
    CASE(N = 100, base = filledVector(100, 100), ex = filledVector(100, 100));

    CASE(allOdd());
    CASE(allEven());
  }
private:
  void randomVector(int sz) {
    vector <int> mb, me;
    for (int i = 0 ; i < sz ; i++) {
      mb.push_back(rnd.nextInt(1, ELM_MAX));
      me.push_back(rnd.nextInt(1, ELM_MAX));
    }
    N = sz, base = mb, ex = me;
    return;
  }

  vector <int> filledVector(int sz, int value) {
    vector <int> ret(sz);
    for (int i = 0 ; i < sz ; i++) {
      ret[i] = value;
    }
    return ret;
  }

  int randomOdd() {
    while (1) {
      int ret = rnd.nextInt(1, ELM_MAX);
      if (ret & 1) return ret;
    }
  }

  int randomEven() {
    while (1) {
      int ret = rnd.nextInt(1, ELM_MAX);
      if (!(ret & 1)) return ret;
    }
  }

  void allOdd() {
    vector <int> mb, me;
    for (int i = 0 ; i < N_LIM ; i++) {
      mb.push_back(randomOdd());
      me.push_back(randomOdd());
    }
    N = mb.size(), base = mb, ex = me;
  }

  void allEven() {
    vector <int> mb, me;
    for (int i = 0 ; i < N_LIM ; i++) {
      mb.push_back(randomEven());
      me.push_back(randomEven());
    }
    N = mb.size(), base = mb, ex = me;
  }
};
