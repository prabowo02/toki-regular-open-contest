#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 2e5;
const int MAXA = 1e9;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, K;
  vector<int> A;

  long long ans;

  void InputFormat() {
    LINE(N, K);
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
    CONS(1 <= K && K <= MAXN);
    CONS(eachElementBetween(A, 1, MAXA));
    CONS(isNonDecreasing(A));
  }

  void Subtask1() {
    Points(100);
  }

   private:
  bool eachElementBetween(const vector<int> &A, int down, int up) {
    for(int a : A) if (a < down || a > up) return false;
    return true;
  }

  bool isNonDecreasing(const vector<int> &A) {
    for(int i = 1; i < A.size(); i++)
      if(A[i - 1] > A[i]) return false;
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
        "5 6",
        "1 1 1 1 1",
    });
    Output({
        "0",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "4 3",
      "1 1 2 2",
    });
    Output({
      "2",
    });
  }

  void BeforeTestCase() {
    A.clear();
  }

  void TestGroup1() {
    Subtasks({1});
    //max case
    CASE(N = 198678, K = 200000, A = vector<int>(N, MAXA));
    //max operation
    CASE(N = 200000, K = 200000, A = merge(vector<int>(N / 2, 1), vector<int>(N / 2, MAXA)));
    //climb only and remove only
    CASE(N = 177013, K = 200000, A = merge(vector<int>(1, 1), vector<int>(N - 1, MAXA)));
    CASE(N = 197928, K = 200000, A = merge(vector<int>(N - 1, 1), vector<int>(1, MAXA)));
    //linear
    CASE(N = 200000, K = 164723, linear(MAXA - N, 1));//1 jump
    CASE(N = 200000, K = 200000, linear(314402, 228922));//big jump
    //linear + random
    CASE(N = 200000, K = 164723, linear(1, 999), randomize_height(10));//smol
    CASE(N = 199999, K = 199999, linear(314159, 271828), randomize_height(111102));//big
    //poly
    CASE(N = 111111, K = 164723, poly(1.0, 100000, 1.7));
    CASE(N = 100000, K = 186372, poly(1.0, 0, 1.8), flip());
    //poly + random
    CASE(N = 200000, K = 100000, poly(5.0, 0, 1.5), randomize_height(100000));
    CASE(N = 198765, K = 186372, poly(2.0, 69, 1.69), randomize_height(7777), flip());
    //high N low K
    CASE(N = 158087, K = 177, random_array(1, MAXN));
    CASE(N = 117042, K = 2345, random_array(1, 1000));
    //low N high K
    CASE(N = 260, K = 158087, random_array(1, MAXN));
    CASE(N = 1232, K = 117042, random_array(1, 1000));
    //special case
    CASE(N = 1, K = 200000, random_array(1, MAXN));
    CASE(N = 200000, K = 1, random_array(1, MAXN));
  }

   private:
  vector<int> merge(vector<int> a, vector<int> b) {
    a.insert(a.end(), b.begin(), b.end());
    return a;
  }
  void random_array(int mn, int mx) {
    A.resize(N);
    for(int i = 0; i < N; i++) {
      A[i] = rnd.nextInt(mn, mx);
    }
    sort(A.begin(), A.end());
  } 
  void randomize_height(int param) {
    for(int i = 0; i < N; i++) {
      A[i] = rnd.nextInt(max(1, A[i] - param), min(MAXA, A[i] + param));
    }
    sort(A.begin(), A.end());
  }
  void linear(int start, int jump) {
    A.resize(N);
    A[0] = start;
    for(int i = 1; i < N; i++) {
      A[i] = min(MAXA, A[i - 1] + jump);
    }
  }
  //a^y + b
  void poly(double a, int b, double y) {
    A.resize(N);
    for(int i = 0; i < N; i++) {
      A[i] = min(1e9, pow(a + i, y) + b);
    }
  }
  void flip() {
    for(int i = 0; i < N; i++) {
      A[i] = max(1, MAXA - A[i]);
    }
    sort(A.begin(), A.end());
  }
}; 
