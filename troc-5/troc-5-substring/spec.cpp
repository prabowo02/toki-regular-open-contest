#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
 protected:
  string X, Y;
  string VERDICT;
  string ANS;

  void InputFormat() {
    LINE(X, Y);
  }

  void OutputFormat1() {
    RAW_LINE(VERDICT);
  }

  void OutputFormat2() {
    RAW_LINE(VERDICT);
    LINE(ANS);
  }

  void Constraints() {
    CONS(1 <= X.length() && X.length() <= 10);
    CONS(1 <= Y.length() && Y.length() <= 10);
    CONS(allLowerCase(X));
    CONS(allLowerCase(Y));
  }

  void StyleConfig() {
    CustomScorer();
  }

  void Subtask1() {
    Points(100);
  }

 private:
  bool allLowerCase(string x) {
    for (char ch : x) {
      if (ch < 'a' || ch > 'z') {
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
      "azure ayaz"
    });
    Output({
      "YA",
      "azurebukansaitammar"
    });
  }

  void SampleTestCase2() {
    Subtasks({1});

    Input({
      "saitammar ammar"
    });
    Output({
      "TIDAK"
    });
  }

  void TestGroup1() {
    Subtasks({1});

    for (int i = 0 ; i < 5 ; i++) {
      CASE(sameCase(rnd.nextInt(1, 10)));
    }

    for (int i = 0 ; i < 5 ; i++) {
      CASE(randomCase(rnd.nextInt(9, 10), rnd.nextInt(9, 10)));
      CASE(substringCase(rnd.nextInt(9, 10)));
      CASE(almostSubstringCase(rnd.nextInt(8, 9)));
    }

    for (int i = 0 ; i < 10 ; i++) {
      CASE(randomCase(rnd.nextInt(1, 10), rnd.nextInt(1, 10)));
      CASE(substringCase(rnd.nextInt(1, 10)));
      CASE(almostSubstringCase(rnd.nextInt(1, 9)));
    }
  }

 private:
  string randomString(int len) {
    string ret = "";
    for (int i = 0 ; i < len ; i++) {
      ret += (char)rnd.nextInt('a', 'z');
    }
    return ret;
  }

  void sameCase(int lenX) {
    X = randomString(lenX);
    Y = X;
  }

  void randomCase(int lenX, int lenY) {
    X = randomString(lenX);
    Y = randomString(lenY);
  }

  void substringCase(int lenX) {
    X = randomString(lenX);
    int st = rnd.nextInt(lenX);
    int lenY = rnd.nextInt(1, lenX - st);
    Y = X.substr(st, lenY);
  }

  void almostSubstringCase(int lenX) {
    substringCase(lenX);
    Y += (char)rnd.nextInt('a', 'z');
  }
};
