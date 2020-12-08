#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 300;
const int MINA = 1;
const int MAXA = 1000000000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M;
  vector<vector<int>> A;

  int ans;

  void InputFormat() {
    LINE(N, M);
    GRID(A) % SIZE(N, M);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(1 <= M && M <= MAXN);
    CONS(eachElementBetween(A, MINA, MAXA));
  }

  void Subtask1() {
    Points(100);
  }

 private:
  bool eachElementBetween(const vector<int> &v, int lo, int hi) {
    for (int u: v) if (u < lo || u > hi) return false;
    return true;
  }

  bool eachElementBetween(const vector<vector<int>> &A, int lo, int hi) {
    for (const vector<int> &row: A) if (!eachElementBetween(row, lo, hi)) return false;
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "3 4",
      "3 2 1 6",
      "1 5 3 9",
      "3 1 4 4",
    });
    Output({
      "3",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "2 2",
      "1 1",
      "1 1",
    });
    Output({
      "1",
    });
  }

  void BeforeTestCase() {
    A.clear();
  }

  void AfterTestCase() {
    N = A.size();
    M = A[0].size();
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(randomGrid(1, 1));
    CASE(randomGrid(rnd.nextInt(1, MAXN), rnd.nextInt(1, MAXN)));
    CASE(randomGrid(MAXN, MAXN));
    CASE(randomGrid(1, MAXN));
    CASE(randomGrid(MAXN, 1));

    CASE(randomGrid(MAXN, MAXN, MAXA-1, MAXA));
    CASE(randomGrid(MAXN, MAXN, MAXA, MAXA));
    CASE(randomGrid(MAXN, MAXN, MAXA/2, MAXA/2); addNoise(100));
    CASE(randomGrid(MAXN, MAXN, MAXA/2, MAXA/2); addNoise(100, 0, 10));
    CASE(randomGrid(MAXN, MAXN, MAXA/2, MAXA/2); addNoise(100, -10, 0));

    CASE(checkerBoard(1, MAXN));
    CASE(checkerBoard(MAXN, 1, false));
    CASE(checkerBoard(MAXN-1, MAXN-1));
    CASE(checkerBoard(MAXN-1, MAXN-1, false));
    CASE(checkerBoard(MAXN, MAXN); addNoise(100));
  }

 private:
  void randomGrid(int N, int M, int lo=MINA, int hi=MAXA) {
    A = vector<vector<int>>(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        A[i][j] = rnd.nextInt(lo, hi);
      }
    }
  }

  void addNoise(int quantity=10, int lo=-5, int hi=5) {
    int n = A.size(), m = A[0].size();

    for (int i = 0; i < quantity; ++i) {
      int r = rnd.nextInt(n), c = rnd.nextInt(m);
      A[r][c] = A[r][c] + rnd.nextInt(lo, hi);
      if (A[r][c] < MINA) A[r][c] = MINA;
      if (A[r][c] > MAXA) A[r][c] = MAXA;
    }
  }

  void checkerBoard(int N, int M, bool fixed=true) {
    A = vector<vector<int>>(N, vector<int>(M));
    int small = rnd.nextInt(MINA, MAXA/2), large = rnd.nextInt(MAXA/2 + 1, MAXA);

    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        if ((i ^ j) & 1) A[i][j] = (fixed ? small : rnd.nextInt(MINA, MAXA/2 - 1));
        else A[i][j] = (fixed ? large : rnd.nextInt(MAXA/2, MAXA));
      }
    }
  }
};
