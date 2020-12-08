#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int kMaxN = 100000;
const int kMaxA = 100000;

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
    CONS(1 <= N && N <= kMaxN);
    CONS(all_of(A.begin(), A.end(), [](int a) {
      return 1 <= a && a <= kMaxA;
    }));
  }

  void Subtask1() {
    Points(100);
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "2",
      "2 2",
    });
    Output({"8"});
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "4",
      "1 3 2 4",
    });
    Output({"1492992"});
  }

  void SampleTestCase3() {
    Subtasks({1});
    Input({
      "4",
      "6 12 60 36",
    });
    Output({"773725433"});
  }

  void BeforeTestCase() {
    A.clear();
  }

  void TestGroup1() {
    Subtasks({1});

    init();

    CASE(N = 1; A = {1});
    CASE(N = 1; A = {kMaxA});
    CASE(N = 2; A = {69, 420});
    CASE(N = 2; A = {216, 315});
    CASE(N = 4; A = {6, 7560, 2, 27720});

    CASE(N = kMaxN; A = vector<int>(N, 1));
    CASE(N = kMaxN; A = vector<int>(N, kMaxA));
    CASE(N = kMaxN; A = vector<int>(N, rnd.nextInt(1, kMaxA)));
    CASE(N = kMaxN; A = vector<int>(N, primes.back()));
    CASE(N = kMaxN; A = vector<int>(N, highlyComposites.back()));

    CASE(N = primes.size(); A = primes; rnd.shuffle(A.begin(), A.end()));
    CASE(N = highlyComposites.size(); A = highlyComposites; rnd.shuffle(A.begin(), A.end()));
    CASE(N = kMaxN; A = primesVector(N));
    CASE(N = kMaxN; A = highlyCompositesVector(N));
    CASE(N = kMaxN; A = randomVector(N));

    CASE(N = rnd.nextInt(1, kMaxN); A = randomVector(N));
    CASE(for (N = 0; (1 << N) < kMaxA; ++N) A.push_back(1 << N));
    CASE(for (N = 0; (1 << N) < kMaxA; ++N) A.push_back(1 << N); rnd.shuffle(A.begin(), A.end()));
    CASE(N = kMaxN; A = primesVector(N/2); for (int num: highlyCompositesVector(N/2)) A.push_back(num));
    CASE(N = kMaxN; A = primesVector(N/2); for (int num: highlyCompositesVector(N/2)) A.push_back(num);
         rnd.shuffle(A.begin(), A.end()));

    CASE(N = kMaxN; A = almostPrimesVector(N));
  }

  vector<int> primes, highlyComposites;
  void init() {
    vector<bool> isPrime(kMaxA + 1, true);
    for (int i = 2; i <= kMaxA; ++i) {
      if (!isPrime[i]) continue;
      primes.push_back(i);
      for (int j = i * 2; j <= kMaxA; j += i) {
        isPrime[j] = false;
      }
    }

    // https://oeis.org/A002182
    highlyComposites = {
        1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, 840, 1260,
        1680, 2520, 5040, 7560, 10080, 15120, 20160, 25200, 27720, 45360,
        50400, 55440, 83160,
    };
  }

  vector<int> randomVector(int n) {
    vector<int> ret(n);
    for (int &num: ret) {
      num = rnd.nextInt(1, kMaxA);
    }
    return ret;
  }

  vector<int> primesVector(int n) {
    vector<int> ret(n);
    for (int &num: ret) {
      num = primes[rnd.nextInt(primes.size())];
    }
    return ret;
  }

  vector<int> almostPrimesVector(int n) {
    vector<int> ret(n);
    int bound = upper_bound(primes.begin(), primes.end(), sqrt(kMaxA)) - primes.begin();
    for (int &num: ret) {
      num = primes[rnd.nextInt(bound - 10, bound - 1)] * primes[rnd.nextInt(bound - 10, bound - 1)];
    }
    return ret;
  }

  vector<int> highlyCompositesVector(int n) {
    vector<int> ret(n);
    for (int &num: ret) {
      num = highlyComposites[rnd.nextInt(highlyComposites.size())];
    }
    return ret;
  }

};
