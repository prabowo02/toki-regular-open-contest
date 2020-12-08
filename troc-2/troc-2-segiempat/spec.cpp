#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace std;
using namespace tcframe;

const int MAX_N = 100;
const int MAX_M = 100;

const int MAX_A = 100;
const int MAX_B = 100;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, M;
    int A, B;
    
    int ans;

    void InputFormat() {
        LINE(N, M);
        LINE(A, B);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }
    
    void Constraints() {
      CONS(Between(N, 1, MAX_N));
      CONS(Between(M, 1, MAX_M));
      CONS(Between(A, 1, MAX_A));
      CONS(Between(B, 1, MAX_B));
    }

    void Subtask1() {
  }
private:
  bool Between(int x,int l,int r) {
    return (l <= x && x <= r);
  }
  bool AllBetween(vector<int> &V ,int l, int r) {
    for (int data : V) if (!Between(data,l,r)) return false; return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
        "2 5",
        "1 2"
    });
    Output({
        "5"
    });
  }

  void TestGroup1() {
    Subtasks({1});
    
    RandomTC();
    ManualTC();
  }
private:
  void RandomTC() {
    CASE(N = rnd.nextInt(1, MAX_N), M = rnd.nextInt(1, MAX_M), A = rnd.nextInt(1, N), B = rnd.nextInt(1, M));
    CASE(N = rnd.nextInt(1, MAX_N), M = rnd.nextInt(1, MAX_M), A = rnd.nextInt(1, N), B = rnd.nextInt(1, M));
    CASE(N = rnd.nextInt(1, MAX_N), M = rnd.nextInt(1, MAX_M), A = rnd.nextInt(1, M), B = rnd.nextInt(1, N));
    CASE(N = rnd.nextInt(1, MAX_N), M = rnd.nextInt(1, MAX_M), A = rnd.nextInt(1, M), B = rnd.nextInt(1, N));
  }
  void ManualTC(){
    CASE(N = 1, M = 1, A = 1, B = 1);
    CASE(N = 100, M = 100, A = 1, B = 1);
    CASE(N = 100, M = 1, A = 2, B = 100);
    CASE(N = 100, M = 1, A = 1, B = 100);
    CASE(N = 3, M = 3, A = 1, B = 2);
    CASE(N = 2, M = 2, A = 1, B = 3);
    CASE(N = 65, M = 78, A = 26, B = 32);
    CASE(N = 40, M = 25, A = 27, B = 37);
    CASE(N = 97, M = 95, A = 2, B = 3);
    CASE(N = 98, M = 96, A = 8, B = 7);
    CASE(N = 87, M = 10, A = 3, B = 6);
  }

};
