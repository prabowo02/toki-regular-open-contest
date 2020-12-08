#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 1e5;
const long long MAXA = 1e18;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  vector<long long> A;

  long long ans;

  void InputFormat() {
    LINE(N);
    LINE(A % SIZE(N));
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
      TimeLimit(1);
      MemoryLimit(64);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(eachElementBetween(A, 0, MAXA));
  }

  void Subtask1() {
    Points(100);
  }

   private:
  bool eachElementBetween(const vector<long long> &A, long long down, long long up) {
    for(long long a : A) if (a < down || a > up) return false;
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
        "5",
        "1 2 3 4 5",
    });
    Output({
        "7",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "1",
      "1",
    });
    Output({
      "1",
    });
  }

  void BeforeTestCase() {
    A.clear();
  }

  void TestGroup1() {
    Subtasks({1});
    //max case and min case
    CASE(N = 100000, A = vector<long long>(N, MAXA));
    CASE(N = 100000, A = vector<long long>(N, 0LL));
    CASE(N = 100000, A = vector<long long>(N, (1LL << 59) - 1));
    CASE(N = 99999, A = vector<long long>(N, (1LL << 59) - 1));
    //random case
    CASE(N = 99999, randomize(MAXA / 10, MAXA));//random big
    CASE(N = 97879, randomize(0, MAXA));//random all range
    CASE(N = 97586, randomize(0, 1000000));//random small
    //random, harus cek karakter terakhir
    CASE(N = 100000, randomize(0, (1LL << 56) - 1), A[0] = 360287970189640680LL, A[999] = 144116188075855872LL, A[N - 1] = 216172782114783808LL);
    //every bit only 1 active
    CASE(N = 60, randomize(0, 0), one_bit(0, 59, 0), acak());
    //every bit > 32 only 1 active
    CASE(N = 98789, randomize(0, (1LL << 32) - 1), one_bit(33, 59, 0), acak());
    //every bit > 40 only 2 active
    CASE(N = 92345, randomize(0, (1LL << 41) - 1), one_bit(40, 59, 0), one_bit(40, 59, 100), acak());
    //1 number biggest and smollest
    CASE(N = 1, A = {MAXA});
    CASE(N = 1, A = {0});
  }

   private:
  void randomize(long long mn, long long mx) {
    A.resize(N);
    for(int i = 0; i < N; i++) {
      A[i] = rnd.nextLongLong(mn, mx);
    }
  }
  void one_bit(int sm, int bg, int idx) {
    for(int i = sm; i <= bg; i++, idx++) {
      A[idx] = (1LL << i);
    }
  }
  void acak() {
    rnd.shuffle(A.begin(), A.end());
  }
}; 
