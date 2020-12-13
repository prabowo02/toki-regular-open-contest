#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 100000;
const int MAXA = 1000000000;
const int LOGA = 30;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  vector<int> A;

  int ans;

  void InputFormat() {
    LINE(N);
    LINE(A % SIZE(N));
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
    CONS(all_of(A.begin(), A.end(), [&](int a) { return 1 <= a && a <= MAXA; }));
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Input({
      "3",
      "1 2 3",
    });
    Output({
      "162",
    });
  }

  void SampleTestCase2() {
    Input({
      "4",
      "1 5 4 2",
    });
    Output({
      "1470000",
    });
  }

  void TestGroup1() {
    CASE(N = MAXN; A = vector<int>(N, MAXA));
    CASE(N = MAXN; A = vector<int>(N, (1 << LOGA-1) - 1));
    CASE(N = MAXN; A = vector<int>(N, 1));
    CASE(N = MAXN; A = randomArray(N));
    CASE(N = MAXN; A = randomBits(N));

    CASE(N = rnd.nextInt(MAXN - 10, MAXN); A = periodBits(N));
    CASE(N = rnd.nextInt(MAXN - 10, MAXN); A = periodBits(N, 2));
    CASE(N = rnd.nextInt(MAXN - 10, MAXN); A = farawayBits(N));
    CASE(N = rnd.nextInt(MAXN - 10, MAXN); A = noisyOrBits(N));
    CASE(N = rnd.nextInt(MAXN - 10, MAXN); A = noisyOrBits(N, 1000));

    CASE(N = MAXN; A = increasingBits(N));
    CASE(N = MAXN; A = concaveBits(N));
  }

  vector<int> randomArray(int n, int lo=1, int hi=MAXA) {
    vector<int> ret(n);
    for (int i = 0; i < n; ++i) ret[i] = rnd.nextInt(lo, hi);
    return ret;
  }

  vector<int> randomBits(int n, int lo=0, int hi=LOGA-1) {
    vector<int> ret(n);
    for (int i = 0; i < n; ++i) ret[i] = 1 << rnd.nextInt(lo, hi);
    return ret;
  }

  vector<int> periodBits(int n, int period=LOGA) {
    vector<int> ret(n);
    for (int i = 0; i < n; ++i) ret[i] = 1 << (i % period);
    return ret;
  }

  vector<int> farawayBits(int n) {
    vector<int> ret(n);
    ret[0] = ret.back() = (1 << LOGA-1) - 2;
    for (int i = 1; i < n-1; ++i) ret[i] = 1;
    return ret;
  }

  vector<int> noisyOrBits(int n, int noise=100) {
    vector<int> ret(n, 1);
    for (int i = 0; i < noise; ++i) {
      ret[rnd.nextInt(n)] |= 1 << rnd.nextInt(1, LOGA-1);
    }
    return ret;
  }

  vector<int> increasingBits(int n, int maxbit=LOGA) {
    vector<int> ret(n);
    for (int i = 0; i < n; ++i) ret[i] = 1 << rnd.nextInt(maxbit);
    sort(ret.begin(), ret.end());
    return ret;
  }

  vector<int> concaveBits(int n, int maxbit=LOGA) {
    vector<int> ret = increasingBits(n/2, maxbit);
    vector<int> tmp = increasingBits(n - n/2, maxbit);
    while (tmp.size()) ret.push_back(tmp.back()), tmp.pop_back();
    return ret;
  }
};
