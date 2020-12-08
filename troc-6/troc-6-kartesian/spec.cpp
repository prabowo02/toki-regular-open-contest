#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MN_N = 1;
const int MX_N = 100;
const int MN_C = -25;
const int MX_C = 25;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, X, Y;
  int A, B, C, D;
  int IMPOSSIBLE;

  void InputFormat() { 
    LINE(N, X, Y); 
  }

  void OutputFormat1() { 
    LINE(A, B, C, D); 
  }

  void OutputFormat2() { 
    LINE(IMPOSSIBLE); 
  }

  void StyleConfig() {
    CustomScorer();
  }

  void Constraints() {
    CONS(MN_N <= N && N <= MX_N);
    CONS(MN_C <= X && X <= MX_C);
    CONS(MN_C <= Y && Y <= MX_C);
  }

  void Subtask1() {}

 private:
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({"17 -4 3"});
    Output({"5 3 2 7"});
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({"100 0 0"});
    Output({"0 50 0 50"});
  }

  void SampleTestCase3() {
    Subtasks({1});
    Input({"24 25 0"});
    Output({"-1"});
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 1, X = 0, Y = 0);
    CASE(N = 1, X = -25, Y = 0);
    CASE(N = 100, X = 25, Y = 25);
    CASE(N = 50, X = -25, Y = -25);

    function<bool(int, int, int)> validCase = [](int n, int x, int y) {
      return abs(x) + abs(y) <= n && n % 2 == (abs(x) + abs(y)) % 2;
    };
    function<bool(int, int, int)> exceedSumCase = [](int n, int x, int y) {
      return abs(x) + abs(y) > n && n % 2 == (abs(x) + abs(y)) % 2;
    };
    function<bool(int, int, int)> wrongParityCase = [](int n, int x, int y) {
      return abs(x) + abs(y) <= n && n % 2 != (abs(x) + abs(y)) % 2;
    };
    function<bool(int, int, int)> allWrongCase = [](int n, int x, int y) {
      return abs(x) + abs(y) > n && n % 2 != (abs(x) + abs(y)) % 2;
    };

    generateCasesThatSatisfy(validCase, 20);
    generateCasesThatSatisfy(wrongParityCase, 15);
    generateCasesThatSatisfy(validCase, 20);
    generateCasesThatSatisfy(exceedSumCase, 15);
    generateCasesThatSatisfy(validCase, 20);
    generateCasesThatSatisfy(allWrongCase, 15);
  }

 private:
  void generateCasesThatSatisfy(function<bool(int, int, int)> f, int tcCount) {
    vector<pair<int, pair<int, int>>> candidates;

    for (int n = MN_N ; n <= MX_N ; n++)
      for (int x = MN_C ; x <= MX_C ; x++)
        for (int y = MN_C ; y <= MX_C ; y++)
          if (f(n, x, y)) {
            candidates.push_back({n, {x, y}});
          }
    
    tcCount = min(tcCount, (int)candidates.size());

    rnd.shuffle(candidates.begin(), candidates.end());
    for (int i = 0 ; i < tcCount ; i++) {
      pair<int, pair<int, int>> cur = candidates[i];
      int n = cur.first;
      int x = cur.second.first;
      int y = cur.second.second;

      CASE(N = n, X = x, Y = y);
    }
  }
};
