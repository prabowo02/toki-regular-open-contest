#include <tcframe/spec.hpp>
using namespace tcframe;
const int N_MIN = 3;
const int N_MAX = 2e5;
const int ELM_MIN = 1;
const int ELM_MAX = 2e5;

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
      "9",
      "1 2 3 1 2 3 1 2 3",
    });
    Output({
      "3"
    });
  }

  void SampleTestCase2() {
    Input({
      "9",
      "1 2 1 1 2 1 1 2 1",
    });
    Output({
      "2"
    });
  }

  void SampleTestCase3() {
    Input({
      "3",
      "10 20 30",
    });
    Output({
      "0"
    });
  }

  void TestGroup1() {
    CASE(N = 3, v = {1, 1, 1});
    CASE(N = 3, v = {ELM_MAX, ELM_MAX, ELM_MAX});
    CASE(N = 6, v = {1, 1, 2, 1, 2, 2});
    CASE(N = 6, v = {2, 1, 2, 2, 1, 1});
    CASE(N = 6, v = {1, 1, 2, 2, 1, 2});
    CASE(N = 9, v = {1, 1, 1, 2, 2, 2, 3, 3, 3});
    CASE(N = 12, v = {1, 2, 1, 2, 1, 2, 3, 3, 3, 3, 3, 3});

    CASE(N = 30, v = triple(makeInRangeOf(1, 10)));
    CASE(N = 120, v = triple(makeInRangeOf(1000, 1000 + 40 - 1)));
    CASE(N = 300, v = triple(makeInRangeOf(ELM_MAX - 100 + 1, ELM_MAX)));

    CASE(randomDeletedSuffix(100));
    CASE(N = 15000, v = triple(randomVector(5000)));

    CASE(N = 60000, v = triple(randomVector(20000)));

    CASE(N = (N_MAX / 3) * 3, v = triple(randomVector(N_MAX / 3)));

    CASE(N = (N_MAX / 3) * 3, v = triple(makeInRangeOf(1, N_MAX / 3)));

    CASE(randomDeletedSuffix(50000));

    CASE(randomDeletedSuffix(N_MAX / 3));

    CASE(extremeLeft());
    CASE(extremeRight());
    CASE(extremeMiddle());

    CASE(extremeLeft1());
    CASE(extremeMiddle1());
    CASE(extremeRight1());

    CASE(extreme2());
    CASE(extreme3());

    CASE(N = N_MAX, v = randomWithLimit(N_MAX, 10));
    CASE(N = N_MAX, v = fill(N_MAX, ELM_MAX));

    CASE(N = N_MAX, v = randomVector(N_MAX));
    CASE(N = N_MAX, v = randomVector(N_MAX));
    CASE(N = N_MAX, v = randomVector(N_MAX));
  }

private:
  void extremeLeft1() {
    vector <int> cur;
    for (int i = 0 ; i < 3 ; i++) {
      cur.push_back(2);
      cur.push_back(3);
    }
    for (int i = 6 ; i < N_MAX ; i++) {
      cur.push_back(1);
    }
    N = cur.size(), v = cur;
  }

  void extremeMiddle1() {
    vector <int> cur;
    int start = rnd.nextInt(1, N_MAX - 10);
    for (int i = 0 ; i < start ; i++) {
      cur.push_back(1);
    }
    for (int i = start ; i < start + 3 ; i++) {
      cur.push_back(2); cur.push_back(3);
    }
    for (int i = start + 6 ; i < N_MAX ; i++) {
      cur.push_back(1);
    }
    N = cur.size(), v = cur;
  }

  void extremeRight1() {
    vector <int> cur;
    for (int i = 0 ; i < N_MAX - 6 ; i++) {
      cur.push_back(1);
    }
    for (int i = 0 ; i < 3 ; i++) {
      cur.push_back(2); cur.push_back(3);
    }
    N = cur.size(), v = cur;
  }

  void extreme2() {
    vector <int> cur;
    for (int i = 0 ; i < 3 ; i++) {
      cur.push_back(1);
    }
    for (int i = 3 ; i < N_MAX ; i++) {
      cur.push_back(i - 1);
    }
    N = cur.size(), v = cur;
  }

  void extreme3() {
    vector <int> cur;
    cur.push_back(2); cur.push_back(3);
    cur.push_back(2);
    for (int i = 0 ; i < N_MAX - 6 ; i++) cur.push_back(1);
    cur.push_back(3);
    cur.push_back(3); cur.push_back(2);
    N = cur.size(), v = cur;
  }

  void extremeLeft() {
    int sz = N_MAX / 3;
    vector <int> cur = fill(sz * 3, 1);
    vector <int> extreme = triple(makeInRangeOf(1, sz / 3));
    int idx = 0;
    for (int i = 0 ; i < sz ; i++) {
      cur[i] = extreme[idx++];
    }
    N = cur.size(), v = cur;
  }

  void extremeRight() {
    int sz = N_MAX / 3;
    vector <int> cur = fill(sz * 3, 1);
    vector <int> extreme = triple(makeInRangeOf(1, sz / 3));
    int idx = 0;
    for (int i = sz * 2 ; i < sz * 3 ; i++) {
      cur[i] = extreme[idx++];
    }
    N = cur.size(), v = cur;
  }

  void extremeMiddle() {
    int sz = N_MAX / 3;
    vector <int> cur = fill(sz * 3, 1);
    vector <int> extreme = triple(makeInRangeOf(1, sz / 3));
    int idx = 0;
    for (int i = sz ; i < sz * 2 ; i++) {
      cur[i] = extreme[idx++];
    }
    N = cur.size(), v = cur;
  }

  vector <int> fill(int sz, int value) {
    vector <int> ret(sz);
    for (int i = 0 ; i < sz ; i++) {
      ret[i] = value;
    }
    return ret;
  }

  void randomDeletedSuffix(int sz) {
    vector <int> cur(sz);
    for (int i = 0 ; i < sz ; i++) {
      cur[i] = rnd.nextInt(1, ELM_MAX);
    }
    cur = triple(cur);
    int remove = rnd.nextInt(0, sz);
    while (remove--) cur.pop_back();
    N = cur.size();
    v = cur;
    return;
  }

  vector <int> triple(vector <int> v) {
    vector <int> ret = v;
    for (int x : v) {
      ret.push_back(x);
    }
    for (int x : v) {
      ret.push_back(x);
    }
    return ret;
  }

  vector <int> makeInRangeOf(int l, int r) {
    vector <int> ret;
    for (int i = l ; i <= r ; i++) {
      ret.push_back(i);
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

  vector <int> randomWithLimit(int sz, int lim) {
    vector <int> ret(sz);
    for (int i = 0 ; i < sz ; i++) {
      ret[i] = rnd.nextInt(1, lim);
    }
    return ret;
  }
};
