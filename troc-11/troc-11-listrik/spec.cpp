#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 50000;
const int MAXA = 100000;

vector<int> primes;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M;
  vector<int> A;

  long long ans;

  void InputFormat() {
    LINE(N);
    LINE(A % SIZE(N));
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(64);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(eachElementBetween(A, 1, MAXA));
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
      "1 2 3",
    });
    Output({
      "2",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "6",
      "5 10 5 10 5 5",
    });
    Output({
      "30",
    });
  }

  void BeforeTestCase() {
    A.clear();
  }

  void TestGroup1() {
    Subtasks({1});
    findprime();
    CASE(N = MAXN; allrandom(MAXN, MAXA));
    CASE(N = MAXN; allrandom(MAXN, MAXA));
    CASE(N = MAXN; allrandom(MAXN, MAXA));
    CASE(N = MAXN; allrandom(MAXN, MAXA));
    CASE(N = MAXN; random2(MAXN, MAXA));
    CASE(N = MAXN; random2(MAXN, MAXA));
    CASE(N = MAXN; random2(MAXN, MAXA));
    CASE(N = MAXN; random2(MAXN, MAXA));
    CASE(N = MAXN; ALL(83160, MAXN - 1, 1, 1));//49999 buah 83160 (maximum factor) dengan satu
    CASE(N = MAXN; ALL(MAXA, MAXN, 0, 0));//maximum answer
    CASE(N = MAXN; ALL(1, MAXN, 0, 0));//all 1

    CASE(N = MAXN; rndprimes(MAXN));//all 50k primes
    CASE(N = primes.size(); A = primes);//distinct primes
    
    CASE(N = 30; A = {1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, 840, 1260, 1680, 2520, 5040, 7560, 10080, 15120, 20160, 25200, 27720, 45360, 50400, 55440, 83160, 99371});
    //highly composite number
    CASE(N = 1; A = {100000});
  }

 private:
  void ALL(int a1, int cnt1, int a2, int cnt2) {
    for(int i = 0; i < cnt1; i++) {
      A.push_back(a1);
    }
    for(int i = 0; i < cnt2; i++) {
      A.push_back(a2);
    }
  }
  void allrandom(int N, int MAX) {
	  for (int i = 0; i < N; i++) {
		  A.push_back(rnd.nextInt(1, MAX));
	  } 
  }
  int POW(int x, int y) {
    int res = 1;
    while(y) {
      if(y & 1) res *= x;
      x *= x;
      y >>= 1;
    }
    return res;
  }
  void random2(int N, int MAX) {
    vector<int> yes = {2, 3, 5, 7, 11}; 
    for(int i = 0; i < N; i++) {
        int tmp = 1;
        for(int f : yes) {
            tmp = tmp * POW(f, rnd.nextInt(0, (int)(log(MAX / tmp) / log(f))));
        }
        A.push_back(tmp);
    }
  }
  void findprime() {
    bitset<100005> visit = 0;
    for(int i = 2; i < MAXA; i++) {
      if(!visit[i]) primes.push_back(i);
      else continue;
      for(int j = (i << 1); j <= MAXA; j += i) {
        visit[j] = 1;
      }
    }
  }
  void rndprimes(int N) {
    for(int i = 0; i < N; i++) {
      A.push_back(primes[rnd.nextInt(0, primes.size() - 1)]);
    }
  }
};
