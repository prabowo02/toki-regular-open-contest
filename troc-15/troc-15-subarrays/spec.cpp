#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;
const int MAXN = 200000;
const int MAXA = 200000;

#define pb push_back

class ProblemSpec : public BaseProblemSpec {
protected:
  int N;
  vector <int> A;
  string ANS;
  void InputFormat() {
    LINE(N);
    LINE(A % SIZE(N));
  }

  void OutputFormat(){
    LINE(ANS);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(128);
  }

  void Constraints() {
    CONS((1 <= N) && (N <= MAXN));
    CONS(eachElementBetween(A,1,MAXA));
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
      "3 6 9 6 3"
    });
    Output({
      "YES"
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "8",
      "4 3 3 2 4 3 2 1"
    });
    Output({
      "NO"
    });
  }
  
  void BeforeTestCase(){
    A.clear();
  }

  void TestGroup1(){
    Subtasks({1});
    CASE(N = 2; A = {MAXA, MAXA});
    CASE(N = 5; A = {1, 1, 2, 1, 2});
    CASE(N = 10; halfA());
    CASE(N = 4; A = {1, 2, 1, 2});
    CASE(N = 6; A = {1, 2, 3, 3, 2, 1});
    CASE(N = 8; A = {4, 3, 2, 4, 3, 1, 2, 1});
    CASE(N = 8; A = {4, 3, 2, 4, 3, 1, 4, 1});
    CASE(N = 6; A = {4, 3, 2, 4, 3, 1});
    CASE(N = 6; A = {1, 3, 1, 2, 3, 2});
    CASE(N = 10; A = {21464, 67249, 42373, 67249, 62454, 42373, 74872, 74872, 21464, 42373});
    CASE(N = 1000; makeUniqueA(900));
    CASE(N = 1000; makeUniqueA(501));
    CASE(N = 1000; makeUniqueA(499));
    CASE(N = MAXN; makeRandomA());
    CASE(N = MAXN; halfA());
    CASE(N = MAXN; makeUniqueA(MAXN/2));
    CASE(N = MAXN; makeUniqueA(MAXN/3));
    CASE(specialTC1());
    CASE(specialTC2());
    CASE(specialTC3());
    CASE(N = 5; A = {1, 2, 1, 2, 3});
  }

private:
  
  void makeRandomA(int lo = 1, int hi = MAXA){
    A.resize(N);
    for(int &cur : A) cur = rnd.nextInt(lo, hi);
  }

  /**
   * Make A with (cnt) unique element
   * @param cnt Numbers of unique element
   */
  void makeUniqueA(int cnt = -1){
    assert(1 <= cnt && cnt <= N);
    
    // Take cnt unique element
    A.resize(MAXA);
    iota(A.begin(), A.end(), 1);
    rnd.shuffle(A.begin(), A.end());
    A.erase(A.begin()+cnt, A.end());
    
    // Pick the rest
    vector <int> extra(N-cnt);
    for(int &cur : extra) cur = A[rnd.nextInt(cnt)];
    A.insert(A.end(), extra.begin(), extra.end());

    // Shuffle A
    rnd.shuffle(A.begin(), A.end());
  }

  void makeDecreasingA(int lo = 1, int hi = MAXA){
    makeRandomA(lo, hi);
    sort(A.rbegin(),A.rend());
  }

  void makeIncreasingA(int lo = 1, int hi = MAXA){
    makeRandomA(lo, hi);
    sort(A.begin(),A.end());
  }

  void halfA(){
    A.resize(N);
    for(int i = 0;i < N;i++) A[i] = (i%(N/2))+1;
  }

  void specialTC1(){
    N = MAXN;
    assert(N%2 == 0);
    for(int i = MAXN/2+1;i >= 2;i--){
      A.pb(i+1); A.pb(i - 1);
    }
  }

  void specialTC2(){
    N = MAXN;
    assert(N%2 == 0);
    for(int i = MAXN/2;i >= 1;i--){
      A.pb(i); A.pb(i+1);
    }
  }

  void specialTC3(){
    N = MAXN;
    assert(N%2 == 0);
    for(int i = 1;i <= MAXN/2;i++){
      A.pb(i+1); A.pb(i);
    }
  }
};