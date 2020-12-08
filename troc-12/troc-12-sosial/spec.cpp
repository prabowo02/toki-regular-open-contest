#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 30;
const int MAXA = 1000000000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  vector<long long> A;

  long long ans;

  void InputFormat() {
    LINE(N);
    LINE(A % SIZE(N + 1));
  }

  void OutputFormat() {
    LINE(ans);
  }

  void Constraints() {
    CONS(0 <= N && N <= MAXN);
    CONS(eachElementBetween(A, 0, MAXA));
  }

  void Subtask1() {
    Points(100);
  }

 private:
  bool eachElementBetween(const vector<long long> &A, int down, int up) {
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
        "4 2 0 2",
    });
    Output({
        "3",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "1",
      "3 0",
    });
    Output({
      "-1",
    });
  }
  
  void BeforeTestCase() {
    A.clear();
  }

  void TestGroup1() {
    Subtasks({1});
    //corner case
    CASE(N = 30, getall(MAXA));
    CASE(N = 30, getall(0));
    //case yes
    CASE(getyes(30));
    CASE(getyes(30));
    CASE(getyes(30));
    CASE(getyes(30));
    CASE(getyes(30));
    CASE(getyes(30));
    //case no
    CASE(getno(30));
    CASE(getno(30));
    CASE(getno(30));
    //selain 2^N '0'
    CASE(only(30, 30));
    //max yes
    CASE(N = 30, getall(MAXA), A[0] -= 73741824);
    CASE(N = 0, A = {rnd.nextInt(0, MAXA)});
  }

 private:
  void only(int sz, int loc) {
    A.resize(sz + 1);
    for(int i = 0; i <= sz; i++) {
      A[i] = 0;
    }
    A[loc] = rnd.nextInt(1, MAXA);
  }
  void getall(int val) {
    A.resize(31);
    for(int i = 0; i <= 30; i++) {
      A[i] = val;
    }
  }
  void getyes(int sz) {
    A.resize(sz + 1);
    long long val = 0, tmp;
    long long sum = 0, MOD = (1LL << sz);
    for(int i = 0; i <= sz; i++) {
      A[i] = rnd.nextInt(0, MAXA);
      sum = (sum + (A[i] << i)) % MOD;
    }
    for(int i = sz; i >= 0; i--) {
      tmp = sum / (1LL << i);
      sum -= min(A[i], tmp) * (1LL << i);
      A[i] = max(0LL, A[i] - tmp);
    }
  }
  void getno(int sz) {
    A.resize(sz + 1);
    long long val = 0, tmp;
    long long sum = 0, MOD = (1 << sz);
    for(int i = 0; i <= sz; i++) {
      A[i] = rnd.nextInt(0, MAXA);
      sum = (sum + (A[i] << i)) % MOD;
    }
    if(sum == 0) {
      tmp = rnd.nextInt(0, sz - 1);
      if(A[tmp] == MAXA)A[tmp]--;
      else A[tmp]++;
    }
  }
};
