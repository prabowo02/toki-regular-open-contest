#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAXN = 100000;
const int MAXK = 1000000000;

class ProblemSpec : public BaseProblemSpec {
 protected:

  int N, K;
  vector<int> A;
  int ANS;

  void InputFormat() {
    LINE(N, K);
    LINE(A % SIZE(N));
  }

  void OutputFormat() {
    LINE(ANS);
  }

  void Constraints() {
    CONS(2 <= N && N <= MAXN);
    CONS(1 <= K && K <= MAXK);
    CONS(isPermutation(A));
  }

  void Subtask1() {
    Points(100);
  }

 private:
  bool isPermutation(vector<int> v) {
    sort(v.begin(), v.end());
    for (int i = 0 ; i < v.size() ; i++) {
      if (v[i] != i+1) {
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
      "4 3",
      "2 3 1 4"
    });

    Output({"2"});
  }

  void SampleTestCase2() {
    Subtasks({1});

    Input({
      "4 10",
      "2 3 1 4"
    });

    Output({"-1"});
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 2, K = 1,
         A = {2, 1});
    
    CASE(N = 2, K = 2,
         A = {2, 1});
    
    CASE(N = MAXN, K = MAXK,
         A = splitHalfPermutation(N));
    CASE(N = MAXN, K = MAXK,
         A = randomPermutation(N));
    CASE(N = MAXN, K = MAXK,
         A = increasingPermutation(N));

    for (int i = 0 ; i < 5 ; i++) {
      // brutal length
      CASE(N = rnd.nextInt(MAXN / 2, MAXN), K = rnd.nextInt(1, MAXK),
           A = splitHalfPermutation(N),
           distort(A, rnd.nextInt(1, 50)));

      // random, standard
      CASE(N = rnd.nextInt(MAXN / 2, MAXN), K = rnd.nextInt(1, MAXK),
           A = randomPermutation(N));

      // should be -1
      CASE(N = rnd.nextInt(MAXN / 2, MAXN), K = rnd.nextInt(1, MAXK),
           A = increasingPermutation(N),
           distort(A, rnd.nextInt(1, 100)));

      // a bit random
      CASE(N = rnd.nextInt(MAXN / 2, MAXN), K = rnd.nextInt(1, 1e6),
           A = increasingPermutation(N),
           distort(A, rnd.nextInt(100, 10000)));
      
      // a bit random
      CASE(N = rnd.nextInt(MAXN / 2, MAXN), K = rnd.nextInt(1, MAXK),
           A = increasingPermutation(N),
           distort(A, rnd.nextInt(10000, 100000)));
      
      // exact
      CASE(N = rnd.nextInt(MAXN / 2, MAXN),
           A = increasingPermutation(N),
           exactCase(A));
    }
  }

 private:
  void exactCase(vector<int> perm) {
    vector<int> sums = getLimiterSum(perm);
    vector<int> candidates;
    int tot = 0;

    for (int x : sums) {
      tot += x;
      if (tot > MAXK) break;
      candidates.push_back(tot);
    }

    K = candidates[rnd.nextInt(candidates.size())];
  }

  vector<int> increasingPermutation(int n) {
    vector<int> ret(n);
    iota(ret.begin(), ret.end(), 1);

    return ret;
  }

  vector<int> randomPermutation(int n) {
    vector<int> ret = increasingPermutation(n);
    rnd.shuffle(ret.begin(), ret.end());

    return ret;
  }

  vector<int> splitHalfPermutation(int n) {
    vector<int> ret(n, 0);

    int i = 0;
    int val = 1;

    while (val <= n) {
      ret[i] = val;
      val += 2;
      i++;
    }

    val = 2;
    while (val <= n) {
      ret[i] = val;
      val += 2;
      i++;
    }

    return ret;
  }

  void distort(vector<int> &v, int times) {
    for (int i = 0 ; i < times ; i++) {
      int a = rnd.nextInt(v.size());
      int b = rnd.nextInt(v.size());

      swap(v[a], v[b]);
    }
  }

  vector<int> getLimiterSum(vector<int> &v) {
    int n = v.size();
    vector<int> pos(n);

    for (int i = 0 ; i < n ; i++) {
      pos[v[i]-1] = i;
    }

    vector<int> psum(n, 0);
    for (int i = 0 ; i+1 < n ; i++) {
      int a = pos[i];
      int b = pos[i+1];

      if (a > b) swap(a, b);
      psum[a]++;
      psum[b]--;
    }

    for (int i = 1 ; i < n ; i++) {
      psum[i] += psum[i-1];
    }

    sort(psum.begin(), psum.end());
    reverse(psum.begin(), psum.end());

    return psum;
  }
};
