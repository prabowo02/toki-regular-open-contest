#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

const int MAXN = 200000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M, K;
  vector<int> A;
  vector<int> B;

  long long ANS;

  void InputFormat() {
    LINE(N, M, K);
    LINE(A % SIZE(N));
    LINE(B % SIZE(M));
  }

  void OutputFormat() {
    LINE(ANS);
  }

  void Constraints() {
    CONS(1 <= K && K <= N && N <= M);
    CONS(eachElementBetween(A, 0, 1));
    CONS(eachElementBetween(B, 0, 1));
  }

  bool eachElementBetween(const vector<int> &A, int lo, int hi) {
    return all_of(A.begin(), A.end(), [&](int a) { return lo <= a && a <= hi; });
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Input({
        "3 4 2",
        "1 0 1",
        "0 1 1 0",
    });
    Output({
        "4"
    });
  }

  void TestGroup1() {
    CASE(N = 1; M = 1; K = 1; A = {1}; B = {0});
    CASE(N = 1; M = 1; K = 1; A = {0}; B = {0});
    CASE(N = 1; M = MAXN; K = 1; A = {1}; B = randomBinaryArray(M));
    CASE(N = 1; M = MAXN; K = 1; A = {1}; B = vector<int>(M, 1));

    CASE(N = MAXN; M = MAXN; K = N / 2; A = vector<int>(N, 0); B = vector<int>(M, 0));
    CASE(N = MAXN; M = MAXN; K = N / 2; A = vector<int>(N, 0); B = vector<int>(M, 1));
    CASE(N = MAXN; M = MAXN; K = N / 2; A = vector<int>(N, 1); B = vector<int>(M, 0));
    CASE(N = MAXN; M = MAXN; K = N / 2; A = vector<int>(N, 1); B = vector<int>(M, 1));

    CASE(randomSumBetween(MAXN / 4, 100, 1000));
    CASE(randomSumBetween(MAXN / 4, 100, 1000); invert(A));
    CASE(randomSumBetween(MAXN / 4, 100, 1000); invert(B));
    CASE(randomSumBetween(MAXN / 4, 100, 1000); invert(A); invert(B));

    CASE(randomSumBetween(MAXN / 4 * 3, 100, 200));
    CASE(randomSumBetween(MAXN / 4 * 3, 100, 200); invert(A));
    CASE(randomSumBetween(MAXN / 4 * 3, 100, 200); invert(B));
    CASE(randomSumBetween(MAXN / 4 * 3, 100, 200); invert(A); invert(B));

    CASE(N = MAXN; M = MAXN; K = N; A = randomBinaryArray(N); B = randomBinaryArray(M));
    CASE(N = MAXN; M = MAXN; K = N; A = randomBinaryArray(N); B = randomBinaryArray(M));
    CASE(N = MAXN; M = MAXN; K = N; A = randomBinaryArray(N); B = randomBinaryArray(M));

    CASE(N = MAXN; M = MAXN; K = N; A = vector<int>(N, 0); B = vector<int>(M, 0));
    CASE(N = MAXN; M = MAXN; K = N; A = vector<int>(N, 0); B = vector<int>(M, 1));
    CASE(N = MAXN; M = MAXN; K = N; A = vector<int>(N, 1); B = vector<int>(M, 0));
    CASE(N = MAXN; M = MAXN; K = N; A = vector<int>(N, 1); B = vector<int>(M, 1));

    CASE(N = MAXN; M = MAXN; K = 1; A = vector<int>(N, 0); B = vector<int>(M, 0));
    CASE(N = MAXN; M = MAXN; K = 1; A = vector<int>(N, 0); B = vector<int>(M, 1));
    CASE(N = MAXN; M = MAXN; K = 1; A = vector<int>(N, 1); B = vector<int>(M, 0));
    CASE(N = MAXN; M = MAXN; K = 1; A = vector<int>(N, 1); B = vector<int>(M, 1));
  }

  void randomSumBetween(int k, int lo, int hi) {
    N = rnd.nextInt(MAXN - 100, MAXN);
    M = rnd.nextInt(N, MAXN);
    K = k;
    A = subarraySumBetween(N, K, lo, hi);
    B = subarraySumBetween(M, K, lo, hi);
  }

  vector<int> subarraySumBetween(int n, int k, int lo, int hi) {
    vector<int> a(n);

    vector<int> ones(k);
    iota(ones.begin(), ones.end(), 0);
    rnd.shuffle(ones.begin(), ones.end());

    int sum = rnd.nextInt(lo, hi);
    ones.resize(sum);
    for (int i : ones) {
      a[i] = 1;
    }

    for (int i = k; i < n; ++i) {
      sum -= a[i - k];

      if (sum < lo) {
        a[i] = 1;
        ++sum;
      } else if (sum + 1 > hi) {
        a[i] = 0;
      } else {
        a[i] = rnd.nextInt(2);
        sum += a[i];
      }
    }

    return a;
  }

  vector<int> randomBinaryArray(int n) {
    vector<int> ret(n);
    for (int &a : ret) {
      a = rnd.nextInt(2);
    }
    return ret;
  }

  void invert(vector<int> &A) {
    for (int &a : A) {
      a ^= 1;
    }
  }
};
