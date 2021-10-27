#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const long long MAXN = 1e5, MAXK = 1e18;

class ProblemSpec : public BaseProblemSpec {
protected:
  long long K, N;
  vector<int> u, l, r;

  void InputFormat() {
    LINE(K);
  }

  void OutputFormat() {
    LINE(N);
    LINES(u, l, r) % SIZE(N);
  }

  void StyleConfig() {
    CustomScorer();
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= K && K <= MAXK);
    CONS(isValidVecs(u, l, r));
  }
private:
  bool isValidVecs(vector<int> u, vector<int> l, vector<int> r){
    bool ret = (u.size() == l.size()) && (l.size() == r.size());
    for(int i=0; i<u.size(); i++){
      ret = ret && (1 <= u[i]) && (u[i] <= MAXN);
      ret = ret && (1 <= l[i]) && (l[i] <= MAXN);
      ret = ret && (1 <= r[i]) && (r[i] <= MAXN);
      ret = ret && (l[i] <= r[i]);
    }
    return ret;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Input({
      "2",
    });
    Output({
      "3",
      "2 2 5",
      "1 6 6",
      "6 4 5"
    });
  }

  void SampleTestCase2() {
    Input({
      "4",
    });
    Output({
      "3",
      "2 2 5",
      "1 1 6",
      "6 4 5"
    });
  }

  void TestGroup1() {
    for(int i=0; i<5; i++){
      CASE(K = rnd.nextInt(1, 1e9));
    }
    for(int i=0; i<15; i++){
      CASE(K = (long long) rnd.nextInt(0, 1e9-1) * 1e9 + rnd.nextInt(1, 1e9));
    }
    CASE(K = 1e18);
  }
};
