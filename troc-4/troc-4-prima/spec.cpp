#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
 protected:

  int a, b, c;
  int ans;

  void InputFormat() {
    LINE(a, b, c);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void Constraints() {
    CONS(2 <= a && a <= 100);
    CONS(2 <= b && b <= 100);
    CONS(2 <= c && c <= 100);
    CONS(prime(a));
    CONS(prime(b));
    CONS(prime(c));
    CONS(a != b && a != c && b != c);
  }

  void StyleConfig() {
    CustomScorer();
  }

  void Subtask1() {
    Points(100);
  }

 private:
  bool prime(int x) {
    for (int i = 2; i < x; ++i) if (x % i == 0) return false;
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:

  vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

  void SampleTestCase1() {
    Subtasks({1});
    Input({ "7 13 19"});
    Output({"41"});
  }

  void TestGroup1() {
    Subtasks({1});

    for (int i = 0; i < 10; ++i) {
      CASE(buildWithMod(primes.size(), primes.size(), primes.size()));
    }
    for (int i = 3; i <= 10; ++i) {
      CASE(buildWithMod(i, i, i));
    }
    for (int i = 0; i < 10; ++i) {
      CASE(buildWithMod(3, 3, 3));
    }
    for (int i = 0; i < 10; ++i) {
      CASE(buildWithMod(4, 4, 4));
    }

    CASE(a = 3, b = 5, c = 7);
    CASE(a = 83, b = 89, c = 97);
    CASE(a = 79, b = 83, c = 89);

    for (int i = 2; i < primes.size(); ++i) {
      CASE(build(i - 2, i - 1, i));
    }

  }

 private:
  void build(int x, int y, int z) {
    a = primes[x], b = primes[y], c = primes[z];
  }

  void buildWithMod(int mod1, int mod2, int mod3) {
    int x, y, z;
    do {
      x = rnd.nextInt(mod1);
      y = rnd.nextInt(mod2);
      z = rnd.nextInt(mod3);
    } while (x == y || x == z || y == z);
    a = primes[x], b = primes[y], c = primes[z];
  }
};
