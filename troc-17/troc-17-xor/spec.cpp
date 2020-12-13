#include <tcframe/spec.hpp>
using namespace tcframe;
const int N_MAX = 2e5;
const int N_MIN = 2;
const int ELM_MAX = 2000;
const int ELM_MIN = 1;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N;
  vector <int> v;
  int answer;

  void InputFormat() {
    LINE(N);
    LINE(v % SIZE(N));
  }

  void OutputFormat() {
    LINE(answer);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(N_MIN <= N && N <= N_MAX);
    CONS(withinBounds(v, N));
  }
private:
  bool withinBounds(vector <int> &v, int N) {
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
      "3",
      "2 3 5",
    });
    Output({
      "42",
    });
  }

  void SampleTestCase2() {
    Input({
      "4",
      "2 5 7 11",
    });
    Output({
      "105840",
    });
  }

  void TestGroup1() {
    CASE(N = 2, v = {1, 1});
    CASE(N = 2, v = {ELM_MIN, ELM_MAX});
    CASE(N = 4, v = {ELM_MAX, ELM_MAX - 1, ELM_MAX - 2, ELM_MAX - 3});
    CASE(N = 10, v = vectorInRangeOf(ELM_MAX - 9, ELM_MAX));

    CASE(N = 50, v = randomDistinct(50));
    CASE(N = 50, v = randomDistinct(50));

    CASE(N = 1500, v = randomDistinct(1500));
    CASE(N = 1500, v = randomDistinct(1500));

    CASE(N = 2000, v = vectorInRangeOf(1, ELM_MAX));

    CASE(N = 20000, v = randomVector(20000));
    CASE(N = 20000, v = randomVector(20000));

    CASE(N = N_MAX, v = randomVector(N_MAX));
    CASE(N = N_MAX, v = randomVector(N_MAX));

    CASE(N = N_MAX, v = vector<int>(N, rnd.nextInt(ELM_MIN, ELM_MAX)));
  }
private:
  vector <int> randomDistinct(int N) {
    vector <bool> vis(ELM_MAX + 1 , false);

    vector <int> ret;
    for (int i = 0 ; i < N ; i++) {
      while (1) {
        int cur = rnd.nextInt(1, ELM_MAX);
        if (!vis[cur]) {
          ret.push_back(cur);
          vis[cur] = 1;
          break;
        }
      }
    }

    return ret;
  }

  vector <int> randomVector(int sz) {
    vector <int> ret(sz);
    for (int i = 0 ; i < sz ; i++) {
      ret[i] = rnd.nextInt(1, ELM_MAX);
    }
    return ret;
  }

  vector <int> vectorInRangeOf(int l, int r) {
    vector <int> ret;
    for (int i = l ; i <= r ; i++) {
      ret.push_back(i);
    }
    return ret;
  }
};
