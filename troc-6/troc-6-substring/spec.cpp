#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAX_LENGTH = 100000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  string S, T;
  int ANS;

  void InputFormat() {
    LINE(S);
    LINE(T);
  }

  void OutputFormat1() {
    LINE(ANS);
  }

  void Constraints() {
    CONS(1 <= S.length() && S.length() <= MAX_LENGTH);
    CONS(1 <= T.length() && T.length() <= S.length());
    CONS(allLowerCase(S));
    CONS(allLowerCase(T));
  }


  void Subtask1() {
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
      "yurariyurureri",
      "yur"
    });
    Output({
      "0"
    });
  }

  void SampleTestCase2() {
    Subtasks({1});

    Input({
      "xxxxx",
      "xxx"
    });
    Output({
      "3"
    });
  }

  void AfterTestCase() {
    vector<int> mapping(26);
    iota(mapping.begin(), mapping.end(), 0);
    rnd.shuffle(mapping.begin(), mapping.end());

    for (char &ch : S) ch = 'a' + mapping[ch - 'a'];
    for (char &ch : T) ch = 'a' + mapping[ch - 'a'];
  }

  void TestGroup1() {
    Subtasks({1});

    // case with T not unique char
    // observation check
    // trivia: with after testcase, second tc will consist of Indonesian laugh
    CASE(T = "ab", 
         S = constructRepeatingString(T, 10));
    CASE(T = "aba", 
         S = constructRepeatingString(T, 100), 
         appendRandomCharacters(S, 99));
    CASE(T = randomString(MAX_LENGTH),
         S = T);
    CASE(T = randomString(rnd.nextInt(1, MAX_LENGTH / 2)),
         S = randomString(MAX_LENGTH));
    CASE(T = randomString(rnd.nextInt(1, 1000)),
         S = constructRepeatingString(T, MAX_LENGTH / T.length()),
         appendRandomCharacters(S, MAX_LENGTH - S.length()),
         randomizeCharacterOrders(S));     

    vector<function<void(string&)>> sModifiers = {
      sortStringCharacters, randomizeCharacterOrders
    };

    // overflow of stupid multiplication
    CASE(constructString(50000, 50000, 50000),
         sortStringCharacters(S));
    // single char T
    CASE(constructString(1, 90000, 5000),
         randomizeCharacterOrders(S));
    // no other char
    CASE(constructString(100, rnd.nextInt(1, MAX_LENGTH), 0));

    // reduce stupid tcs
    for (int i = 0 ; i < 2 ; i++) {
      // S = aaaaa, T = a
      CASE(constructString(1, rnd.nextInt(1, MAX_LENGTH), 0));
      
      // S = aaaaaaaaa, T = aaa
      int lenT = rnd.nextInt(1, MAX_LENGTH);
      CASE(constructString(lenT, rnd.nextInt(lenT, MAX_LENGTH), 0));

      // S = aaaaaaaa, T = b
      CASE(constructString(1, 0, rnd.nextInt(1, MAX_LENGTH), true));
      // S = aaaaaaaaa, T = bbbb
      lenT = rnd.nextInt(1, MAX_LENGTH);
      CASE(constructString(lenT, 0, rnd.nextInt(lenT, MAX_LENGTH), true));

      for (auto modifier : sModifiers) {
        CASE(constructTrulyRandom(),
             modifier(S));
        
        CASE(constructExact(100),
             modifier(S));
        CASE(constructExact(10000),
             modifier(S));
        
        CASE(constructAlmost(100),
             modifier(S));
        CASE(constructAlmost(10000),
             modifier(S));
      }
    }

    for (int i = 0 ; i < 3 ; i++) {
      for (auto modifier : sModifiers) {
        CASE(constructPositive(100),
             modifier(S));
        CASE(constructPositive(1000),
             modifier(S));
        CASE(constructPositive(10000),
             modifier(S));
        CASE(constructPositive(MAX_LENGTH),
             modifier(S));
      }
    }
  }

 private:
  string randomString(int len) {
    string ret(len, '.');
    for (char &ch : ret) ch = (char)rnd.nextInt('a', 'z');
    return ret;
  }

  string constructRepeatingString(string s, int repeat) {
    string ret = "";
    for (int i = 0 ; i < repeat ; i++)
      ret += s;
    return ret;
  }

  void appendRandomCharacters(string &s, int cnt) {
    for (int i = 0 ; i < cnt ; i++) {
      s += (char)(rnd.nextInt('a', 'z'));
    }
  }

  void constructString(int lenT, int occInS, int otherInS, bool sameInOther = false) {
    char chT = rnd.nextInt('a', 'z');
    T = string(lenT, chT);
    S = string(occInS, chT);

    char ch = rnd.nextInt('a', 'z');
    while (ch == chT) ch = rnd.nextInt('a', 'z');
    
    for (int i = 0 ; i < otherInS ; i++) {
      if (!sameInOther) {
        ch = rnd.nextInt('a', 'z');
        while(ch == chT) ch = rnd.nextInt('a', 'z');
      }
      
      S += ch;
    }
  }

  void constructTrulyRandom() {
    int occInS = rnd.nextInt(0, MAX_LENGTH);
    int otherInS = rnd.nextInt(0, MAX_LENGTH - occInS);
    int lenT = rnd.nextInt(1, occInS + otherInS);
    constructString(lenT, occInS, otherInS);
  }

  // leftover is exactly lenT
  void constructExact(int maxLengthT) {
    int lenT = rnd.nextInt(2, maxLengthT);
    int limitOther = 0;
    while (limitOther+1 + (limitOther+1) * (lenT-1) + lenT <= MAX_LENGTH) limitOther++;
    int otherInS = rnd.nextInt(0, limitOther);
    int occInS = lenT + otherInS * (lenT-1);

    constructString(lenT, occInS, otherInS);
  }

  // leftover is exactly lenT-1
  void constructAlmost(int maxLengthT) {
    int lenT = rnd.nextInt(2, maxLengthT);
    int limitOther = 0;
    while (limitOther+1 + (limitOther+1) * (lenT-1) + lenT-1 <= MAX_LENGTH) limitOther++;
    int otherInS = rnd.nextInt(1, limitOther);
    int occInS = lenT-1 + otherInS * (lenT-1);

    constructString(lenT, occInS, otherInS);
  }

  // leftover is >= lenT
  void constructPositive(int maxLengthT) {
    int lenT = rnd.nextInt(1, maxLengthT);
    int occInS = rnd.nextInt(lenT, MAX_LENGTH);
    int limitS = 0;

    if (lenT == 1) {
      limitS = MAX_LENGTH - occInS;
    } else {
      while (occInS - (limitS + 1) * (lenT - 1) >= lenT)
        limitS++; 
    }

    int otherInS;
    if (rnd.nextInt(2))
      otherInS = rnd.nextInt(0, limitS);
    else
      otherInS = rnd.nextInt(0, min(100, limitS));

    constructString(lenT, occInS, limitS);
  }

  function<void(string&)> sortStringCharacters = [&](string &str) {
    sort(str.begin(), str.end());
  };

  function<void(string&)> randomizeCharacterOrders = [&](string &str) {
    rnd.shuffle(str.begin(), str.end());
  };
};
