#include <bits/stdc++.h>
#include <tcrand/tree.hpp>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;
using namespace tcrand;

const int MAXN = 100000;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N;
  vector<int> A;
  string ANS;

  void InputFormat() {
    LINE(N);
    LINE(A % SIZE(N));
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
    CONS(eachElementBetween(A, 0, 1));
  }

  void Subtask1(){
    Points(100);
  }


private:
  template <class T> 
  bool eachElementBetween(const vector<T>&V, T lo, T hi){
    for(T x : V) if(x < lo || hi < x) return false;
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "5",
      "1 0 0 0 1",
    });
    Output({
      "YES",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "7",
      "0 0 1 1 0 1 0",
    });
    Output({
      "NO",
    });
  }

  void SampleTestCase3() {
    Subtasks({1});
    Input({
      "4",
      "1 0 1 0",
    });
    Output({
      "YES",
    });
  }

  void BeforeTestCase() {
    A.clear();
  }

  void TestGroup1() {
    Subtasks({1});
    
    // small testcase
    CASE(N = 2, A = {0, 1});
    CASE(N = 3, A = {0, 1, 0});
    CASE(N = 4, A = {1, 1, 0, 1});
    CASE(N = 4, A = {0, 0, 0, 0});
    CASE(N = 4, A = {0, 1, 1, 0});
    CASE(N = 5, A = {1, 1, 1, 1, 1});
    CASE(N = 5, A = {0, 1, 0, 1, 0});
    CASE(N = 5, A = {1, 0, 1, 0, 0});
    CASE(N = 5, A = {0, 1, 1, 0, 1});
    CASE(N = 6, fixed_segment(4));
    CASE(N = 6, fixed_segment(5));
    CASE(N = 7, fixed_segment(4));
    CASE(N = 7, fixed_segment(3));
    CASE(N = 8, fixed_segment(4));

    // other
    CASE(N = 100000, randomA());
    CASE(N = 100000, fixed_segment(N));
    CASE(N = 100000, fixed_segment(4));
    CASE(N = 100000, fixed_segment(3));
    CASE(N = 100000, fixed_segment(1));
  }

private:
  void randomA() {
    A.resize(N);
    generate(A.begin(), A.end(), [&]() { return rnd.nextInt(0, 1); });
  }

  //generate an array with fixed segment count
  //first element have 50/50 chance to be 0 or 1
  void fixed_segment(int segment) {
    assert(1 <= segment && segment <= N);
    int rand_cnt = N - segment;
    A.resize(N);
    
    vector<int> palet(segment, 1);
    while (rand_cnt--) {
      palet[rnd.nextInt(0, segment - 1)]++;
    }
    
    int elem = rnd.nextInt(0, 1); 
    int pt = 0;
    for (int seg_size : palet) {
      for (int cnt = seg_size; cnt > 0; cnt--) {
        A[pt++] = elem;
      }
      elem ^= 1;
    }
  }
};