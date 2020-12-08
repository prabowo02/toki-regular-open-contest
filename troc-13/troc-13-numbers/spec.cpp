#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 200000;
int numbers[200005];

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

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(eachElementBetween(A, 1, MAXN));
  }

  void Subtask1() {
    Points(100);
  }

   private:
  bool eachElementBetween(const vector<int> &A, int down, int up) {
    for (int a: A) {
      if (a < down || a > up) return false;
    }

    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
        "5",
        "1 1 2 2 2",
    });
    Output({
        "4",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "2",
      "1 2",
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
    //corner case and case answer = 1
    CASE(N = MAXN, Get_All(MAXN, MAXN));
    CASE(N = 1, Get_All(1, 1));
    CASE(N = MAXN, Get_All(rnd.nextInt(2, MAXN - 1), MAXN));
    //case answer = N
    CASE(N = MAXN, Get_Case_N(MAXN));
    CASE(N = 42069, Get_Case_N(42069));
    CASE(N = 123456, Get_Case_N(123456));
    //case answer = N - 1
    CASE(N = 177013, Get_Case_Diff(177013, 42069));
    CASE(N = 78125, Get_Case_Diff(78125, 2));
    CASE(N = 199999, Get_Case_Diff(199999, 199998));
    CASE(N = 166320, Get_Case_Diff(166320, 83160));
    //counter code kak jt
    CASE(N = 100003, Get_All(199999, 100002), A.push_back(1));
    CASE(N = 140620, Get_Case_Diff(140619, 140619), A.push_back(A[69]), rnd.shuffle(A.begin(), A.end()));
  }

   private:
  void Get_All(int val, int sz) {
    A.resize(sz);
    for(int i = 0; i < sz; i++) {
      A[i] = val;
    }
  }
  void Get_Case_N(int sz) {
    A.resize(sz);
    for(int i = 1; i <= MAXN; i++) {
      numbers[i] = i;
    }
    rnd.shuffle(&numbers[1], &numbers[MAXN + 1]);
    for(int i = 0; i < sz; i++) {
      A[i] = numbers[i + 1];
    }
  }
  void Get_Case_Diff(int sz, int diff_cnt) {
    A.resize(sz);
    int last_num = 0, last_pos = -1;
    for(int i = 1; i <= diff_cnt; i++) {
      int num_now = rnd.nextInt(last_num + 1, MAXN - diff_cnt + i);
      int pos_now = rnd.nextInt(last_pos + 1, sz - diff_cnt + i - 1);
      if (i == diff_cnt) pos_now = sz - 1;
      for(int i = last_pos + 1; i <= pos_now; i++) {
        A[i] = num_now;
      }
      last_num = num_now;
      last_pos = pos_now;
    }
    rnd.shuffle(A.begin(), A.end());
  }
};