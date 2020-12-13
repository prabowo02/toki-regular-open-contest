#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 2000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, K;
  vector<int> T, A;

  int ans;

  void InputFormat() {
    LINE(N, K);
    LINES(T, A) % SIZE(K);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= K && K <= N && N <= MAXN);
    CONS(all_of(T.begin(), T.end(), [](int t) { return 0 <= t && t <= 1; }));
    CONS(strictlyIncreasing(N, A));
  }

  bool strictlyIncreasing(int N, const vector<int> &A) {
    if (A[0] < 1) return false;
    for (int i = 1; i < A.size(); ++i) if (A[i-1] >= A[i]) return false;
    if (A.back() > N) return false;
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Input({
      "4 2",
      "1 1",
      "1 3",
    });
    Output({
      "8",
    });
  }

  void SampleTestCase2() {
    Input({
      "5 3",
      "1 1",
      "0 3",
      "1 5",
    });
    Output({
      "8",
    });
  }

  void SampleTestCase3() {
    Input({
      "1 1",
      "0 1",
    });
    Output({
      "1",
    });
  }

  void TestGroup1() {
    CASE(N = 10; K = 3; T = randomBits(K); A = choose(N, K));
    CASE(N = 10; K = 5; T = randomBits(K); A = choose(N, K));
    CASE(N = 10; K = 7; T = randomBits(K); A = choose(N, K));

    CASE(N = MAXN; K = rnd.nextInt(1, N); T = randomBits(K); A = choose(N, K));
    CASE(N = MAXN; K = N; T = randomBits(K); A = choose(N, K));
    CASE(N = MAXN; K = 1; T = randomBits(K); A = choose(N, K));
    CASE(N = MAXN; K = 1; T = randomBits(K); A = {1});
    CASE(N = MAXN; K = 1; T = randomBits(K); A = {N});

    CASE(N = rnd.nextInt(MAXN - 10, MAXN); K = rnd.nextInt(1, N); T = vector<int>(K, 0); A = choose(N, K));
    CASE(N = rnd.nextInt(MAXN - 10, MAXN); K = rnd.nextInt(1, N); T = vector<int>(K, 1); A = choose(N, K));
    CASE(N = rnd.nextInt(MAXN - 10, MAXN); K = rnd.nextInt(1, N); T = vector<int>(K, 0); A = choose(N, K); addBitNoise(T));
    CASE(N = rnd.nextInt(MAXN - 10, MAXN); K = rnd.nextInt(1, N); T = vector<int>(K, 1); A = choose(N, K); addBitNoise(T));

    CASE(N = rnd.nextInt(MAXN - 10, MAXN); K = rnd.nextInt(1, N); T = randomBits(K); A = vector<int>(K); iota(A.begin(), A.end(), 1));
    CASE(N = rnd.nextInt(MAXN - 10, MAXN); K = rnd.nextInt(1, N); T = randomBits(K); A = vector<int>(K); iota(A.begin(), A.end(), N - K + 1));
  }

  vector<int> randomBits(int len) {
    vector<int> ret(len);
    for (int &u : ret) u = rnd.nextInt(2);
    return ret;
  }

  vector<int> choose(int n, int k) {
    vector<int> ret(n);
    iota(ret.begin(), ret.end(), 1);
    rnd.shuffle(ret.begin(), ret.end());
    ret.resize(k);
    sort(ret.begin(), ret.end());
    return ret;
  }

  void addBitNoise(vector<int> &t, int noise=10) {
    for (int i = 0; i < noise; ++i) {
      t[rnd.nextInt(t.size())] ^= 1;
    }
  }
};
