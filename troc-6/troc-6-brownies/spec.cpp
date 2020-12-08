#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAX_L = 30000;
const int MAX_N = 100;

class ProblemSpec : public BaseProblemSpec {
 protected:

  int N, L;
  vector<int> A;
  int ANS;

  void InputFormat() {
    LINE(N, L);
    LINE(A % SIZE(N));
  }

  void OutputFormat() {
    LINE(ANS);
  }

  void Constraints() {
    CONS(2 <= L && L <= MAX_L);
    CONS(2 <= N && N <= min(L, 100));
    CONS(eachElementsBetween(A, 1, L));
    CONS(accumulate(A.begin(), A.end(), 0) == L);
  }

  void Subtask1() {
  }

 private:
  bool eachElementsBetween(vector<int> v, int lo, int hi) {
    return all_of(v.begin(), v.end(), [&](int x) {
      return lo <= x && x <= hi;
    });
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:

  void SampleTestCase1() {
    Subtasks({1});

    Input({
      "3 7",
      "3 2 2"
    });

    Output({"9"});
  }

  void AfterTestCase() {
    rnd.shuffle(A.begin(), A.end());
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 2, L = 2,
         A = {1, 1});
    CASE(N = 2, L = MAX_L,
         A = {15000, 15000});
    
    CASE(N = MAX_N, L = MAX_L,
         A = randomDistributeArray(N, L));
    CASE(N = MAX_N, L = MAX_L,
         A = randomDistributeArrayWithMajority(N, L));
    CASE(N = MAX_N, L = MAX_L,
         A = randomWithLargeArray(N, L));
    
    // small ones
    for (int i = 0 ; i < 3 ; i++) {
      CASE(L = rnd.nextInt(2, 300), 
           N = rnd.nextInt(2, min(L, MAX_N)),
           A = randomDistributeArray(N, L));
      CASE(L = rnd.nextInt(2, 300), 
           N = rnd.nextInt(2, min(L, MAX_N)),
           A = randomDistributeArrayWithMajority(N, L));
      CASE(L = rnd.nextInt(2, 300), 
           N = rnd.nextInt(2, min(L, MAX_N)),
           A = randomWithLargeArray(N, L));
      CASE(L = rnd.nextInt(2, 300), 
           N = rnd.nextInt(2, min(L, MAX_N)),
           A = randomWithLargeArray(N, L, 50));
    }

    // large ones
    for (int i = 0 ; i < 3 ; i++) {
      CASE(L = rnd.nextInt(MAX_L * 4 / 5, MAX_L), 
           N = rnd.nextInt(2, MAX_N),
           A = randomDistributeArray(N, L));
      CASE(L = rnd.nextInt(MAX_L * 4 / 5, MAX_L),
           N = rnd.nextInt(MAX_N * 4 / 5, MAX_N),
           A = randomDistributeArray(N, L));

      CASE(L = rnd.nextInt(MAX_L * 4 / 5, MAX_L),
           N = rnd.nextInt(2, MAX_N),
           A = randomDistributeArrayWithMajority(N, L));
      CASE(L = rnd.nextInt(MAX_L * 4 / 5, MAX_L),
           N = rnd.nextInt(MAX_N * 4 / 5, MAX_N),
           A = randomDistributeArrayWithMajority(N, L));
      
      CASE(L = rnd.nextInt(MAX_L * 4 / 5, MAX_L), 
           N = rnd.nextInt(2, MAX_N),
           A = randomWithLargeArray(N, L));
      CASE(L = rnd.nextInt(MAX_L * 4 / 5, MAX_L),
           N = rnd.nextInt(MAX_N * 4 / 5, MAX_N),
           A = randomWithLargeArray(N, L));
      CASE(L = rnd.nextInt(MAX_L * 4 / 5, MAX_L), 
           N = rnd.nextInt(MAX_N * 4 / 5, MAX_N),
           A = randomWithLargeArray(N, L, 200));
      CASE(L = rnd.nextInt(MAX_L * 4 / 5, MAX_L),
           N = rnd.nextInt(MAX_N * 4 / 5, MAX_N),
           A = randomWithLargeArray(N, L, 600));
    }
  }

 private:
  vector<int> randomDistributeArray(int n, int l) {
    vector<int> ret(n, 1);
    l -= n;

    for (int i = 0 ; i < l ; i++) {
      ret[rnd.nextInt(n)]++;
    }

    return ret;
  }

  vector<int> randomDistributeArrayWithMajority(int n, int l) {
    vector<int> ret(n, 1);
    l -= n;

    int major = rnd.nextInt(n);
    int sz = rnd.nextInt(l / 2, l);
    ret[major] += sz;
    l -= sz;

    for (int i = 0; i < l; i++) {
      ret[rnd.nextInt(n)]++;
    }

    return ret;
  }

  vector<int> randomWithLargeArray(int n, int l, int limit = -1) {
    if (limit == -1) limit = l;
    vector<int> ret(n, 0);

    for (int i = 0 ; i < n ; i++) {
      int lim = min(limit, l - (n - i - 1));
      int use = rnd.nextInt(1, lim);
      ret[i] = use;
      l -= use;
    }

    for (int i = 0; i < l ; i++) {
      ret[rnd.nextInt(n)]++;
    }

    return ret;
  }
};
