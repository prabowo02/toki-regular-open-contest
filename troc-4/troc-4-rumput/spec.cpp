#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAX_T = 10000;
const int MAX_N = 1000000000;
const int MAX_K = 1000000000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int T;
  vector<int> Ns, Ks;
  vector<string> ANS;

  void InputFormat() { 
    LINE(T);
    LINES(Ns, Ks) % SIZE(T); 
  }

  void OutputFormat() { 
    LINES(ANS) % SIZE(T); 
  }

  void Constraints() {
    CONS(1 <= T && T <= MAX_T);
    CONS(eachElementBetween(Ns, 1, MAX_N));
    CONS(eachElementBetween(Ks, 1, MAX_K));
  }

  void Subtask1() {}

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
      "4",
      "360 90",
      "6 1",
      "10 5",
      "5 10"
    });
    
    Output({
      "YES",
      "NO",
      "NO",
      "YES"
    });
  }

  void BeforeTestCase() {
    Ns.clear();
    Ks.clear();
  }

  void AfterTestCase() {
    // reorder();
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(allSmallCase());

    // fully random
    CASE(randomCase(MAX_T, 1, MAX_N));
    // should be fully no and corner case
    CASE(randomCase(MAX_T, 0, MAX_N));

    // will generate half random instance
    CASE(randomCase(MAX_T, 0.5, 100));
    CASE(randomCase(MAX_T, 0.5, 10000));
    CASE(randomCase(MAX_T, 0.5, 1000000));
    CASE(randomCase(MAX_T, 0.5, MAX_N));
  }

 private:
  void allSmallCase() {
    for (int n = 1 ; n <= 100 ; n++)
      for (int k = 1 ; k <= 100 ; k++) {
        Ns.push_back(n);
        Ks.push_back(k);
      }
    T = Ns.size();
  }

  bool isYesInstance(int n, int k) {
    n *= 2; k *= 2;
    int fpb = __gcd(n/2 + k, n);

    return k >= fpb;
  }

  void generateRandomInstance() {
    int n = rnd.nextInt(1, MAX_N);
    int k = rnd.nextInt(1, MAX_K);

    Ns.push_back(n);
    Ks.push_back(k);
  }

  void generateNoInstance(int limit) {
    int fpb;
    do {
      fpb = rnd.nextInt(1, limit);
    } while (fpb % 2 != 0);

    int mul = rnd.nextInt(1, limit / fpb);
    while (__gcd(mul, fpb) != 1) {
      mul /= __gcd(mul, fpb);
    }

    int n = mul * fpb;
    int half = n / 2;
    int nearest = ((half + fpb - 1) / fpb) * fpb;
    int k = nearest - half;
    
    assert(!isYesInstance(n, k));

    Ns.push_back(n);
    Ks.push_back(k);
  }

  // where k = gcd(n/2+k, n)
  void generateCornerInstance() {
    int n, k;
    do {
      k = rnd.nextInt(1, 1000000);
      n = rnd.nextInt(1, MAX_N / k) * k;
    } while (__gcd(n + 2*k, 2*n) != 2*k);

    Ns.push_back(n);
    Ks.push_back(k);
  }

  void randomCase(int t, double probsRandom, int limit) {
    T = t;
    
    for (int i = 0 ; i < t ; i++) {
      if (rnd.nextDouble(1) <= probsRandom) {
        // random instance; most likely will be "YES"
        generateRandomInstance();
      } else {
        if (rnd.nextDouble(1) <= 0.9) {
          // most of the time, deterministic "NO"
          generateNoInstance(limit);
        }
        else {
          // on rare occasion, deterministic "YES" on boundary
          generateCornerInstance();
        }
      }
    }
  }

  void reorder() {
    vector<int> order(T);
    iota(order.begin(), order.end(), 0);
    rnd.shuffle(order.begin(), order.end());

    vector<int> tmpNs = Ns, tmpKs = Ks;
    for (int i = 0 ; i < T ; i++) {
      Ns[i] = tmpNs[order[i]];
      Ks[i] = tmpKs[order[i]];
    }
  }
};
