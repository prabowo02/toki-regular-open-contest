#include <bits/stdc++.h>
#include <tcrand/tree.hpp>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;
using namespace tcrand;

const int MAXN = 100;
const int MAXM = 100;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N, M;
  vector<vector<int>> A;
  string ANS;

  void InputFormat() {
    LINE(N, M);
    LINES(A) % SIZE(N);
  }

  void OutputFormat(){
    LINE(ANS);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS((2 <= N) && (N <= MAXN));
    CONS((2 <= M) && (M <= MAXN));
    CONS(checkValidGrid(A, N, M));
  }

  void Subtask1(){
    Points(100);
  }


private:
  bool checkValidGrid(const vector<vector<int>> &grid, int N, int M) {
    if (grid.size() != N) return false;
    for (vector<int> row : grid) {
      if (row.size() != M) return false;
      for (int cell : row) {
        if (cell != 0 && cell != 1) return false;
      }
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "2 3",
      "0 1 0",
      "1 0 1",
    });
    Output({
      "YES",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "2 2",
      "0 0",
      "0 0",
    });
    Output({
      "NO",
    });
  }

  void BeforeTestCase() {
    A.clear();
  }

  void TestGroup1() {
    Subtasks({1});

    // small testcase
    CASE(N = 2, M = 2, fixedA(1));
    CASE(N = 2, M = 2, fixedA(2));
    CASE(N = 2, M = 2, fixedA(3));
    CASE(N = 2, M = 2, fixedA(4));

    // other
    CASE(N = 99, M = 100, randomA());
    CASE(N = 100, M = 99, randomA());
    CASE(N = 99, M = 99, randomA());
    CASE(N = 100, M = 100, fixedA(N * M));
    CASE(N = 100, M = 100, fixedA(N * M - 1));
    CASE(N = 100, M = 100, fixedA(1));
    CASE(N = 100, M = 100, fixedA(0));
  }

private:
  void randomA() {
    A.resize(N);
    for (int i = 0; i < N; i++) {
      A[i].resize(M);
      for (int j = 0; j <= M; j++) {
        rnd.nextInt(2);
      }
    }
  }

  void fixedA(int cnt_one) {
    vector<int> palet(N * M);
    int index = 0;
    generate(palet.begin(), palet.end(), [&]() { return ++index > cnt_one ? 0 : 1; });
    rnd.shuffle(palet.begin(), palet.end());

    A.resize(N);
    for (int i = 0; i < N; i++) {
      A[i].resize(M);
      for (int j = 0; j <= M; j++) {
        A[i][j] = palet[i * M + j];
      }
    }
  }
};