#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 10000;
const int MAXA = 10;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  vector<int> A, B;

  int ans;

  void InputFormat() {
    LINE(N);
    LINE(A % SIZE(N));
    LINE(B % SIZE(N));
  }

  void OutputFormat() {
    LINE(ans);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(eachElementBetween(A, 0, MAXA));
    CONS(eachElementBetween(B, 0, MAXA));
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
        "3",
        "4 5 6",
        "1 2 3",
    });
    Output({
        "15",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "6",
      "10 7 2 5 4 9",
      "4 4 0 1 6 3",
    });
    Output({
      "41",
    });
  }
  
  void BeforeTestCase() {
    A.clear();
    B.clear();
  }

  void TestGroup1() {
    Subtasks({1});
    //max case and min case
    CASE(N = 10000, A = vector<int>(N, 10), B = vector<int>(N, 10));
    CASE(N = 10000, A = vector<int>(N, 0), B = vector<int>(N, 10));
    CASE(N = 10000, A = vector<int>(N, 0), B = vector<int>(N, 0));
    //answer on the right
    CASE(N = 10000, randomize(), group_ans());
    //answer on the left
    CASE(N = 8922, randomize(), group_ans(), rotate_A(N / 2 - 1), rotate_B(N / 2 - 1));
    //answer not in the middle 
    CASE(N = 10000, randomize(), group_ans(), rotate_A(N / 4 * 3), rotate_B(N / 4 * 3));
    //answer groupped random rotation
    CASE(N = 9228, randomize(), group_ans(), rotate_A(1770), rotate_B(13));
    //random answer
    CASE(N = 8799, randomize());
    CASE(N = 7581, randomize());
    CASE(N = 9999, randomize());
    //checkerboard
    CASE(N = 10000, randomize(), checkerboard());
    //small cases
    CASE(N = 3, randomize());
  }

   private:
  void randomize() {
    A.resize(N), B.resize(N);
    for(int i = 0; i < N; i++) {
      A[i] = rnd.nextInt(0, 10);
      B[i] = rnd.nextInt(0, 10);
    }
  }
  //group semua yang bakal jadi jawaban di sebelah kanan
  void group_ans() {
    vector<int> tmp = A;
    tmp.insert(tmp.end(), B.begin(), B.end());
    sort(tmp.begin(), tmp.end());
    for(int i = 0; i < N; i++) {
      A[i] = tmp[i * 2];
      B[i] = tmp[i * 2 + 1];
    }
    //shuffle half and half
    rnd.shuffle(A.begin(), A.begin() + (N / 2 + 1));
    rnd.shuffle(B.begin(), B.begin() + (N / 2 + 1));
    rnd.shuffle(A.begin() + (N / 2 + 1), A.end());
    rnd.shuffle(B.begin() + (N / 2 + 1), B.end());
  }
  void rotate_A(int val) {
    rotate(A.begin(), A.begin() + val, A.end());
  }
  void rotate_B(int val) {
    rotate(B.begin(), B.begin() + val, B.end());
  }
  void checkerboard() {
    vector<int> tmp = A;
    tmp.insert(tmp.end(), B.begin(), B.end());
    sort(tmp.begin(), tmp.end());
    rnd.shuffle(tmp.begin(), tmp.begin() + N + 1);
    rnd.shuffle(tmp.begin() + N + 1, tmp.end());
    for(int i = 0; i < N; i++) A[i] = tmp[i];
    for(int i = N; i < N * 2; i++) B[i - N] = tmp[i];
    for(int i = 0; i < N; i += 2) {
      swap(A[i], B[i]);
    }
  }
};