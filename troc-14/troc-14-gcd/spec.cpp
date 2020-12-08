#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 101;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  vector<int> A;

  int len;
  string ans;

  void InputFormat() {
    LINE(N);
    LINE(A % SIZE(N));
  }

  void OutputFormat1() {
    LINE(len);
    LINE(ans);
  }

  void OutputFormat2() {
    // Output 0
    LINE(len);
    EMPTY_LINE();
  }

  void StyleConfig() {
    CustomScorer();
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(isPermutation(A));
  }

  void Subtask1() {
    Points(100);
  }

 private:
  bool eachElementBetween(const vector<int> &A, int lo, int hi) {
    return all_of(A.begin(), A.end(), [&lo, &hi](int x) { 
      return lo <= x && x <= hi;
    });
  }

  bool isPermutation(vector<int> A) {
    sort(A.begin(), A.end());
    for (int i = 0; i < A.size(); ++i) if (A[i] != i+1) return false;
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "3",
      "1 2 3",
    });
    Output({
      "5",
      "LGRRG",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "1",
      "1",
    });
    Output({
      "0",
      "",
    });
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 2; A = {1, 2});
    CASE(N = 2; A = {2, 1});
    CASE(N = 3; A = {2, 1, 3});
    CASE(N = 98; A = sortedPermutation(N));
    CASE(N = 99; A = sortedPermutation(N); reverse(A.begin(), A.end()));
    CASE(N = 100; A = randomPermutation(N));
    CASE(N = 101; A = randomPermutation(N));
  }

 private:
  vector<int> sortedPermutation(int n) {
    vector<int> ret(n);
    iota(ret.begin(), ret.end(), 1);
    return ret;
  }

  vector<int> randomPermutation(int n) {
    vector<int> ret = sortedPermutation(n);
    rnd.shuffle(ret.begin(), ret.end());
    return ret;
  }
};
