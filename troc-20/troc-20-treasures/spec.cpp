#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 100000;
const int MAXM = 200000;
const int MAXZ = 1000000000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M;
  vector<int> T, X, Y, Z;

  string ans;

  void InputFormat() {
    LINE(N, M);
    LINES(T, X, Y, Z) % SIZE(M);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(2 <= N && N <= MAXN);
    CONS(1 <= M && M <= MAXM);
    CONS(all_of(T.begin(), T.end(), [&](int u) { return 1 <= u && u <= 2; }));
    CONS(all_of(X.begin(), X.end(), [&](int u) { return 1 <= u && u <= N; }));
    CONS(all_of(Y.begin(), Y.end(), [&](int u) { return 1 <= u && u <= N; }));
    CONS(all_of(Z.begin(), Z.end(), [&](int u) { return 1 <= u && u <= MAXZ; }));
    CONS(pairwiseDifferent(X, Y));
  }

  void Subtask1() {
    Points(100);
  }

 private:
  bool pairwiseDifferent(const vector<int> &X, const vector<int> &Y) {
    for (int i = 0; i < X.size(); ++i) if (X[i] == Y[i]) return false;
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "3 6",
      "1 1 2 3",
      "2 1 2 2",
      "1 2 3 3",
      "2 2 3 2",
      "1 1 3 3",
      "2 1 3 2",
    });
    Output({
      "NO",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "4 8",
      "1 1 2 3",
      "2 1 2 2",
      "1 2 3 3",
      "2 2 3 2",
      "1 3 4 3",
      "2 3 4 2",
      "1 1 4 3",
      "2 1 4 2",
    });
    Output({
      "YES",
    });
  }

  void SampleTestCase3() {
    Subtasks({1});
    Input({
      "4 3",
      "1 1 2 4",
      "2 2 3 1",
      "1 1 3 5",
    });
    Output({
      "YES",
    });
  }

  void SampleTestCase4() {
    Subtasks({1});
    Input({
      "2 2",
      "1 1 2 10",
      "1 1 2 20",
    });
    Output({
      "NO",
    });
  }

  void BeforeTestCase() {
    T.clear(); X.clear(); Y.clear(); Z.clear();
  }

  void AfterTestCase() {
    M = T.size();

    // renumber
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    rnd.shuffle(perm.begin(), perm.end());
    for (int i = 0; i < M; ++i) {
      X[i] = perm[X[i]];
      Y[i] = perm[Y[i]];
    }
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(generateHintsFrom(randomArray(2, 1, 100), 1));
    CASE(generateHintsFrom(randomArray(2, 1, 100), 2));
    CASE(generateHintsFrom(randomArray(2, 1, 100), 3));
    CASE(generateHintsFrom(randomArray(2, 1, 100), 3); falsifyHints(1));
    CASE(generateHintsFrom(randomArray(3, 1, 100), 3); falsifyHints(5));

    int smallN = 1000, smallM = 2000;
    CASE(generateHintsFrom(randomArray(smallN), smallM));
    CASE(generateHintsFrom(randomArray(smallN), smallM); falsifyHints());

    CASE(generateHintsFrom(randomArray(MAXN / 10), MAXM));
    CASE(generateHintsFrom(randomArray(MAXN), MAXM));
    CASE(generateHintsFrom(randomArray(MAXN, 1, 100), MAXM));
    CASE(generateHintsFrom(randomArray(MAXN, 1, 1), MAXM));
    CASE(generateCompleteHintsFrom(randomArray(sqrt(MAXM))));

    CASE(generateHintsFrom(randomArray(MAXN), MAXM, 1));
    CASE(generateHintsFrom(randomArray(MAXN), MAXM, 2));

    CASE(generateHintsFrom(randomArray(MAXN / 10), MAXM); falsifyHints(3));
    CASE(generateHintsFrom(randomArray(MAXN), MAXM); falsifyHints());
    CASE(generateHintsFrom(randomArray(MAXN, 1, 100), MAXM); falsifyHints());
    CASE(generateHintsFrom(randomArray(MAXN, 1, 1), MAXM); falsifyHints());
  }

  void generateCompleteHintsFrom(vector<int> A) {
    for (int i = 0; i < A.size(); ++i) {
      for (int j = i + 1; j < A.size(); ++j) {
        T.push_back(rnd.nextInt(1, 2));
        X.push_back(i);
        Y.push_back(j);
        Z.push_back(T.back() == 1 ? max(A[i], A[j]) : min(A[i], A[j]));
      }
    }
  }

  void generateHintsFrom(vector<int> A, int _M, int fixedT=0) {
    M = _M;
    T.resize(M); X.resize(M); Y.resize(M); Z.resize(M);
    for (int i = 0; i < M; ++i) {
      T[i] = (fixedT ? fixedT : rnd.nextInt(1, 2));
      do {
        X[i] = rnd.nextInt(A.size());
        Y[i] = rnd.nextInt(A.size());
      } while (X[i] == Y[i]);
      Z[i] = (T[i] == 1 ? max(A[X[i]], A[Y[i]]) : min(A[X[i]], A[Y[i]]));
    }
  }

  vector<int> randomArray(int _N, int lo=1, int hi=MAXZ) {
    vector<int> ret(N = _N);
    for (int i = 0; i < N; ++i) {
      ret[i] = rnd.nextInt(lo, hi);
    }
    return ret;
  }

  void falsifyHints(int quantity=10) {
    for (int i = 0; i < quantity; ++i) {
      int falseType = rnd.nextInt(3);
      int idx = rnd.nextInt(M);
      if (falseType == 1) {
        Z[idx] = rnd.nextInt(1, MAXZ);
      } else if (falseType == 2) {
        Z[idx] += rnd.nextInt(-10, 10);
        Z[idx] = max(Z[idx], 1);
        Z[idx] = min(Z[idx], MAXZ);
      } else {
        T[idx] = 3 - T[idx];
      }
    }
  }
};
