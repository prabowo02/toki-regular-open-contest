#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAXN = 100000;
const int MAXK = 100000;
const int MAXP = 100000;

class ProblemSpec : public BaseProblemSpec {
 protected:

  int N, K, P;
  vector<int> A;
  int ANS;
  vector<int> A_ANS;

  void InputFormat() {
    LINE(N, K, P);
    LINE(A % SIZE(N));
  }

  void OutputFormat() {
    LINE(ANS);
    LINE(A_ANS % SIZE(N));
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(0 <= K && K <= MAXK);
    CONS(1 <= P && P <= MAXP);
    CONS(eachElementBetween(A, 1, P));
  }

  void StyleConfig() {
    CustomScorer();
  }

  void Subtask1() {
    Points(100);
  }

 private:
  
  bool eachElementBetween(vector<int> &v, int lo, int hi) {
    return all_of(v.begin(), v.end(), [lo, hi](int x) {
      return lo <= x && x <= hi;
    });
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({ 
      "8 0 3",
      "1 1 2 2 2 1 3 1"
    });
    Output({
      "3",
      "1 1 2 2 2 1 3 1"
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({ 
      "8 1 3",
      "1 1 2 2 2 1 3 1"
    });
    Output({
      "2",
      "1 1 3 2 2 1 3 1"
    });
  }

  void SampleTestCase3() {
    Subtasks({1});
    Input({ 
      "8 8 3",
      "1 1 2 2 2 1 3 1"
    });
    Output({
      "1",
      "2 1 2 1 2 1 3 1"
    });
  }

  void BeforeTestCase() {
    A.clear();
  }

  void TestGroup1() {
    Subtasks({1});

    // P = 1
    // trivial

    CASE(N = 1,
         K = 0,
         P = 1,
         A = {1});
    CASE(N = MAXN,
         K = N,
         P = 1,
         A = sameArray(N, 1));
    CASE(N = MAXN,
         K = rnd.nextInt(N+1),
         P = 1,
         A = sameArray(N, 1));
    
    // P = 2

    // Ammar's cases
    CASE(N = 9, K = 0, P = 2,
         A = {1, 1, 1, 1, 1, 1, 1, 1, 1});
    CASE(N = 9, K = 1, P = 2,
         A = {1, 1, 1, 1, 1, 1, 1, 1, 1});
    CASE(N = 9, K = 2, P = 2,
         A = {1, 1, 1, 1, 1, 1, 1, 1, 1});
    CASE(N = 9, K = 3, P = 2,
         A = {1, 1, 1, 1, 1, 1, 1, 1, 1});
    CASE(N = 9, K = 4, P = 2,
         A = {1, 1, 1, 1, 1, 1, 1, 1, 1});
    CASE(N = 9, K = 5, P = 2,
         A = {1, 1, 1, 1, 1, 1, 1, 1, 1});
    CASE(N = 9, K = 9, P = 2,
         A = {1, 1, 1, 1, 1, 1, 1, 1, 1});

    CASE(N = 9, K = 1, P = 2,
         A = {1, 1, 2, 2, 1, 1, 2, 2, 2});
    CASE(N = 9, K = 1, P = 2,
         A = {1, 1, 1, 2, 2, 1, 1, 2, 2});
    CASE(N = 9, K = 1, P = 2,
         A = {1, 2, 1, 2, 1, 2, 1, 2, 1});
    CASE(N = 9, K = 1, P = 2,
         A = {1, 2, 1, 2, 1, 1, 2, 1, 2});
    
    {
      vector<int> vec = {2, 1, 1, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2};
      for (int i = 1 ; i <= 7 ; i++) {
        CASE(N = 28, K = i, P = 2,
             A = vec);
      }
    }

    {
      vector<int> vec = {1, 2, 1, 1, 1, 1, 2, 1};
      for (int i = 1 ; i <= 4 ; i++) {
        CASE(N = 8, K = i, P = 2,
             A = vec);
      }
    }

    CASE(N = 10, K = 1, P = 2,
         A = {1, 1, 2, 2, 1, 1, 1, 2, 2, 1});
    CASE(N = 11, K = 1, P = 2,
         A = {1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1});
    CASE(N = 12, K = 1, P = 2,
         A = {1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 1});
    CASE(N = 13, K = 2, P = 2,
         A = {1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 1});
    CASE(N = 14, K = 2, P = 2,
         A = {1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1});
    CASE(N = 15, K = 2, P = 2,
         A = {1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1});
    CASE(N = 16, K = 3, P = 2,
         A = {1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1});
    CASE(N = 24, K = 3, P = 2,
         A = {1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1});

    buildSpecificAndGeneralCases(2, 2);

    // P >= 3
    CASE(N = MAXN,
         K = 3,
         P = 3,
         A = sameArray(N, 2));

    CASE(N = MAXN,
         K = 10,
         P = MAXP,
         A = randomArrayWithSameLengthAtMost(N, N, P));

    // Ammar's cases    
    CASE(N = 8, K = 2, P = 3,
         A = {1, 1, 1, 2, 2, 2, 2, 2});
    CASE(N = 8, K = 2, P = 3,
         A = {1, 1, 1, 3, 3, 3, 3, 3});
    CASE(N = 27, K = 9, P = 3,
         A = {1, 1, 1, 2, 2, 2, 3, 3, 3, 1, 1, 2, 3, 3, 1, 2, 2, 3, 1, 3, 3, 2, 1, 1, 3, 2, 2});
    buildSpecificAndGeneralCases(3, MAXP);
  }

 private:
  void buildSpecificAndGeneralCases(int minP, int maxP) {
    // to trigger small answer
    CASE(N = MAXN,
         K = N / 2,
         P = rnd.nextInt(minP, maxP),
         A = randomArrayWithSameLengthAtMost(N, N / 2, P));
         
    for (int i = 0 ; i < 2 ; i++) {
      CASE(N = rnd.nextInt(MAXN / 2, MAXN),
           K = rnd.nextInt(0, N / 2),
           P = rnd.nextInt(minP, maxP),
           A = randomArrayWithSameLengthAtMost(N, 10, P));
      
      CASE(N = rnd.nextInt(MAXN / 2, MAXN),
           K = rnd.nextInt(0, N / 3),
           P = rnd.nextInt(minP, maxP),
           A = randomArrayWithSameLengthAtMost(N, 5, P));
      
      CASE(N = rnd.nextInt(MAXN / 2, MAXN),
           K = rnd.nextInt(0, N / 3),
           P = rnd.nextInt(minP, maxP),
           A = randomArrayWithSameLengthAtMost(N, 3, P));
      
      CASE(N = rnd.nextInt(MAXN / 2, MAXN),
           K = rnd.nextInt(0, 10),
           P = rnd.nextInt(minP, maxP),
           A = randomArrayWithSameLengthAtMost(N, 2, P));
    }

    for (int i = 0 ; i < 2 ; i++) {
      // small K, length bounded by max, small max length
      CASE(N = rnd.nextInt(MAXN / 2, MAXN),
           K = rnd.nextInt(0, 50),
           P = rnd.nextInt(minP, maxP),
           A = randomArrayWithSameLengthAtMost(N, rnd.nextInt(10, 100), P));
      
      // small K, length bounded by max, big max length
      CASE(N = rnd.nextInt(MAXN / 2, MAXN),
           K = rnd.nextInt(0, 50),
           P = rnd.nextInt(minP, maxP),
           A = randomArrayWithSameLengthAtMost(N, rnd.nextInt(1000, N / 3), P));
    }

    for (int i = 0 ; i < 1 ; i++) {
      // random K, length bounded by max, small max length
      CASE(N = rnd.nextInt(MAXN / 2, MAXN),
           K = rnd.nextInt(0, N),
           P = rnd.nextInt(minP, maxP),
           A = randomArrayWithSameLengthAtMost(N, rnd.nextInt(10, 100), P));
      
      // random K, length bounded by max, big max length
      CASE(N = rnd.nextInt(MAXN / 2, MAXN),
           K = rnd.nextInt(0, N),
           P = rnd.nextInt(minP, maxP),
           A = randomArrayWithSameLengthAtMost(N, rnd.nextInt(1000, N / 3), P));
    }

    for (int i = 0 ; i < 2 ; i++) {
      // medium-big K, length bounded by max, small max length
      CASE(N = rnd.nextInt(MAXN / 2, MAXN),
           K = rnd.nextInt(100, 10000),
           P = rnd.nextInt(minP, maxP),
           A = randomArrayWithSameLengthAtMost(N, rnd.nextInt(10, 100), P));
      
      // medium-big K, length bounded by max, big max length
      CASE(N = rnd.nextInt(MAXN / 2, MAXN),
           K = rnd.nextInt(100, 10000),
           P = rnd.nextInt(minP, maxP),
           A = randomArrayWithSameLengthAtMost(N, rnd.nextInt(1000, N / 3), P));
    }

    for (int i = 0 ; i < 2 ; i++) {
      // small K, length bounded by min, medium min length
      CASE(N = rnd.nextInt(MAXN / 2, MAXN),
           K = rnd.nextInt(0, 50),
           P = rnd.nextInt(minP, maxP),
           A = randomArrayWithSameLengthAtLeast(N, rnd.nextInt(100, 10000), P));
      
      // small K, length bounded by min, small min length and medium range
      CASE(N = rnd.nextInt(MAXN / 2, MAXN),
           K = rnd.nextInt(0, 50),
           P = rnd.nextInt(minP, maxP),
           A = randomArrayWithSameLengthAtLeast(N, rnd.nextInt(100, 1000), P, rnd.nextInt(1, 5000)));
    }

    for (int i = 0 ; i < 2 ; i++) {
      // random K, length bounded by min, medium min length
      CASE(N = rnd.nextInt(MAXN / 2, MAXN),
           K = rnd.nextInt(0, N),
           P = rnd.nextInt(minP, maxP),
           A = randomArrayWithSameLengthAtLeast(N, rnd.nextInt(100, 10000), P));
      
      // random K, length bounded by min, small min length and medium range
      CASE(N = rnd.nextInt(MAXN / 2, MAXN),
           K = rnd.nextInt(0, N),
           P = rnd.nextInt(minP, maxP),
           A = randomArrayWithSameLengthAtLeast(N, rnd.nextInt(100, 1000), P, rnd.nextInt(1, 5000)));
    }
  }
  
  int getDifferentColor(int lastColor, int p) {
    int ret = rnd.nextInt(1, p);
    while (ret == lastColor) {
      ret = rnd.nextInt(1, p);
    }
    return ret;
  }

  vector<int> sameArray(int n, int color) {
    return vector<int>(n, color);
  }

  vector<int> randomArrayWithSameLengthAtMost(int n, int maxLength, int p) {
    int lastColor = -1;
    vector<int> ret;

    while (ret.size() < n) {
      int spaceLeft = n - ret.size();
      int color = getDifferentColor(lastColor, p);

      int use = rnd.nextInt(1, min(maxLength, spaceLeft));

      for (int i = 0 ; i < use ; i++) {
        ret.push_back(color);
      }

      lastColor = color;
    }

    return ret;
  }

  // length in [k, k+maxDiffRange]
  // will work for p > 1
  // note that last group may violate
  vector<int> randomArrayWithSameLengthAtLeast(int n, int minLength, int p, int maxDiffRange = 100) {
    int lastColor = -1;
    vector<int> ret;

    while (ret.size() < n) {
      int spaceLeft = n - ret.size();
      int color = getDifferentColor(lastColor, p);

      int use = spaceLeft;
      if (spaceLeft >= minLength) {
        use = rnd.nextInt(minLength, min(spaceLeft, minLength + maxDiffRange));
      }

      for (int i = 0 ; i < use ; i++) {
        ret.push_back(color);
      }

      lastColor = color;
    }

    return ret;
  }
};
