#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 250;
const int MAXV = 70000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, L, R;
  vector<vector<int>> A;

  long long ans;

  void InputFormat() {
    LINE(N, L, R);
    GRID(A)%SIZE(N, N);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(7);
    MemoryLimit(512);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(0 <= L && L <= R && R <= MAXV);
    CONS(EachElementBetween(A, 1, MAXN));
  }

  void Subtask1() {
    Points(100);
  }

 private:
  
  bool EachElementBetween(const vector<vector<int>> &V, int Lo, int Hi) {
    for (int i = 0; i < (int) V.size(); i++) {
      for (int j = 0; j < (int) V[i].size(); j++) {
        if (Lo <= V[i][j] && V[i][j] <= Hi) continue;
        return false;
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
      "2 2 4",
      "1 2",
      "3 4",
    });
    Output({
      "10"
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "3 3 6",
      "1 2 3",
      "4 5 6",
      "7 8 9",
    });
    Output({
      "22",
    });
  }

  void SampleTestCase3() {
    Subtasks({1});
    Input({
      "2 10 50",
      "5 5",
      "5 5",
    });
    Output({
      "20",
    });
  }

  void BeforeTestCase() {
    A.clear();
  }

  void TestGroup1() {
    Subtasks({1});
    
    // N = 1
    CASE(N = 1, L = 3, R = 4, FillGrid(3));

    // L = R cases
    CASE(N = MAXN, L = rnd.nextInt(0, MAXN), R = L, RandGrid());
    CASE(N = MAXN, L = rnd.nextInt(0, MAXN), R = L, RandGrid());
    CASE(N = MAXN, L = rnd.nextInt(1, MAXN), R = L, FillGrid(L));

    // L, R <= MAXN
    CASE(N = MAXN, L = rnd.nextInt(0, MAXN), R = rnd.nextInt(L, MAXN), RandGrid());
    CASE(N = MAXN, L = rnd.nextInt(0, MAXN), R = rnd.nextInt(L, MAXN), RandGrid());
    CASE(N = MAXN, L = rnd.nextInt(0, MAXN), R = rnd.nextInt(L, MAXN), LowValueGrid());
    CASE(N = MAXN, L = rnd.nextInt(0, MAXN), R = rnd.nextInt(L, MAXN), HighValueGrid());

    // Min Max
    CASE(N = MAXN, L = 0, R = MAXV, RandGrid());
    CASE(N = MAXN, L = MAXV, R = MAXV, RandGrid());
    CASE(N = MAXN, L = 0, R = rnd.nextInt(MAXV - 5000, MAXV), FillGrid(1));
    CASE(N = MAXN, L = rnd.nextInt(0, MAXV), R = rnd.nextInt(max(L, MAXV / 20), MAXV), FillGrid(MAXN));

    // Random Cases
    CASE(N = MAXN, L = rnd.nextInt(0, MAXV), R = rnd.nextInt(L, MAXV), RandGrid());
    CASE(N = MAXN, L = rnd.nextInt(0, MAXV), R = rnd.nextInt(L, MAXV), LowValueGrid());
    CASE(N = MAXN, L = rnd.nextInt(0, MAXV), R = rnd.nextInt(L, MAXV), HighValueGrid());
  }

 private:
  void RandGrid() {
    A.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        A[i][j] = rnd.nextInt(1, MAXN);
      }
    }    
  }

  void HighValueGrid() {
    A.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        A[i][j] = rnd.nextInt(200, MAXN);
      }
    }    
  }

  void LowValueGrid() {
    A.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        A[i][j] = rnd.nextInt(1, 50);
      }
    }    
  }

  void FillGrid(int x) {
    A.assign(N, vector<int>(N, x));
  }
};
