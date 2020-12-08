#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAX_N = 100000;

class ProblemSpec : public BaseProblemSpec {
 protected:

  int N, M;
  string S;
  int K;
  vector<vector<int>> ANS;

  void InputFormat() {
    LINE(N, M);
    LINE(S);
  }

  void OutputFormat() {
    LINE(K);
    LINES(ANS) % SIZE(K);
  }

  void StyleConfig() {
    CustomScorer();
  }

  void Constraints() {
    CONS(1 <= N && N <= MAX_N);
    CONS(1 <= M && M <= N);
    CONS(S.size() == N);
    CONS(eachCharactersBinary(S));
    CONS(count(S.begin(), S.end(), '1') == M);
  }

  void Subtask1() {
  }

 private:
  bool eachCharactersBinary(string s) {
    return all_of(s.begin(), s.end(), [](char ch) {
      return ch == '0' || ch == '1';
    });
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:

  void SampleTestCase1() {
    Subtasks({1});

    Input({
      "6 3",
      "100011"
    });

    Output({
      "7",
      "1 1",
      "1 4",
      "1 6",
      "1 5",
      "2",
      "1 1",
      "2"
    });
  }

  void BeforeTestCase() {
    S = "";
  }

  void AfterTestCase() {
    int sisa = max(0, N - (int)S.length());
    int front = rnd.nextInt(sisa+1);
    int back = sisa - front;

    appendRandomFront(S, front);
    appendRandomBack(S, back);

    M = count(S.begin(), S.end(), '1');
  }

  void TestGroup1() {
    Subtasks({1});

    // max case
    for (int i = 0 ; i < 2 ; i++) {
      CASE(N = MAX_N - i, S = randomBinaryString(N));
      CASE(N = MAX_N - i, S = randomTrickyString(N));
      CASE(N = MAX_N - i, S = string(N, '1'));
      CASE(N = MAX_N - i, S = string(N, '0'), S[rnd.nextInt(N)] = '1');
    }

    // all cases, but pick between reverse and not to cut down tc needed
    generateAllCases(1);
    generateAllCases(2);
    generateAllCases(3);
    generateAllCases(4);
    generateAllCases(6);
    generateAllCases(7);

    // concat all permutation, with some string appended to front/back
    CASE(S = allPermutationConcat(4, true), N = rnd.nextInt(S.size(), MAX_N));
    CASE(S = allPermutationConcat(5, true), N = rnd.nextInt(S.size(), MAX_N));
    for (int i = 0 ; i < 8 ; i++) {
      CASE(S = allPermutationConcat(rnd.nextInt(4, 12), false), 
           N = rnd.nextInt(S.size(), MAX_N));
    }

    // ammar pattern end
    CASE(N = MAX_N, S = ammarPatternEnd(N));
    CASE(N = MAX_N-1, S = ammarPatternEnd(N));

    // ammar pattern repeating 1
    for (int one = 1 ; one <= 4 ; one++)
      for (int zero = 1 ; zero <= 4 ; zero++) {
        CASE(S = ammarPatternRepeating1(rnd.nextInt(10, MAX_N), zero, one), 
             N = S.size());
        CASE(S = ammarPatternRepeating1(rnd.nextInt(10, MAX_N), zero, one), 
             N = rnd.nextInt(S.size(), MAX_N));    
      }
    
    // ammar pattern repeating 2
    for (int i = 0 ; i < 5 ; i++) {
      CASE(S = ammarPatternRepeating2(rnd.nextInt(10, MAX_N)),
           N = S.size());
      CASE(S = ammarPatternRepeating2(rnd.nextInt(10, MAX_N)),
           N = rnd.nextInt(S.size(), MAX_N));
    }

    // random
    for (int i = 0 ; i < 10 ; i++) {
      CASE(N = rnd.nextInt(1, MAX_N), S = randomBinaryString(N));
      CASE(N = rnd.nextInt(1, MAX_N), S = randomTrickyString(N));
    }
  }

 private:
  int getReversedBits(int x, int len) {
    int ret = 0;
    for (int i = 0 ; i < len ; i++) {
      if (x & (1 << i)) {
        ret |= (1 << (len - i - 1));
      }
    }
    return ret;
  }

  string getBitString(int x, int len) {
    string ret = "";

    for (int i = 0 ; i < len ; i++) {
      if (x & (1 << i))
        ret += "1";
      else
        ret += "0";
    }

    return ret;
  }

  void generateAllCases(int len) {
    for (int i = 1 ; i < (1 << len) ; i++) {
      int revI = getReversedBits(i, len);

      if (i <= revI) {
        // choose between this and its reversed order
        int use = rnd.nextInt(2) ? i : revI;
        CASE(N = len, S = getBitString(use, len));
      }
    }
  }

  string allPermutationConcat(int len, vector<int> perm) {
    string ret = "";
    for (int x : perm) {
      ret += getBitString(x, len);
    }
    return ret;
  }

  string allPermutationConcat(int len, bool isOrdered) {
    vector<int> perm(1 << len);
    iota(perm.begin(), perm.end(), 0);
    if (!isOrdered) rnd.shuffle(perm.begin(), perm.end());
    string ret = allPermutationConcat(len, perm);

    return ret;
  }

  string ammarPatternEnd(int len) {
    assert(len >= 4);
    string ret(len, '0');

    ret[0] = ret[1] = '1';
    ret[len-1] = ret[len-2] = '1';
    return ret;
  }

  string ammarPatternRepeating1(int len, int zero, int one) {
    string ret = "";
    char cur = rnd.nextInt(2);

    while (len - ret.size() >= max(zero, one)) {
      if (cur) {
        for (int i = 0 ; i < one ; i++) ret += "1";
      } else {
        for (int i = 0 ; i < zero ; i++) ret += "0";
      }

      cur = 1 - cur;
    }

    return ret;
  }

  string ammarPatternRepeating2(int len) {
    string ret = "";
    char cur = rnd.nextInt(2);

    while (len - ret.size() >= 2) {
      if (cur) {
        if (rnd.nextInt(2)) ret += "11";
        else ret += "1";
      } else {
        ret += "0";
      }

      cur = 1 - cur;
    }

    return ret;
  }

  // random stuffs

  string randomBinaryString(int len) {
    string ret(len, '0');
    for (char &ch : ret) {
      ch = (char)rnd.nextInt('0', '1');
    }
    return ret;
  }

  string randomTrickyString(int len, int probs1, int probs2, int probs3, int probsRandom) {
    if (len == 0) return "";
    string ret = "1";

    while (len - ret.size() > 4) {
      int choice = rnd.nextInt(probs1 + probs2 + probs3 + probsRandom);

      if (choice < probs1) {
        ret += "1";
      } else if (choice < probs1 + probs2) {
        ret += "01";
      } else if (choice < probs1 + probs2 + probs3) {
        ret += "001";
      } else {
        int curLen = rnd.nextInt(4, min(len - (int)ret.size(), 10));
        for (int i = 0 ; i < curLen-1 ; i++) ret += "0";
        ret += "1";
      }
    }

    ret += randomBinaryString(len - ret.size());
    return ret;
  }

  string randomTrickyString(int len) {
    int probs1 = rnd.nextInt(100, 200);
    int probs2 = rnd.nextInt(50, 100);
    int probs3 = rnd.nextInt(50, 100);
    int probsRandom = rnd.nextInt(1, 50);

    return randomTrickyString(len, probs1, probs2, probs3, probsRandom);
  }

  // post-processing

  void appendRandomFront(string &s, int len) {
    string ret = rnd.nextInt(2) ? randomBinaryString(len) : randomTrickyString(len);
    ret += s;
    s = ret;
  }

  void appendRandomBack(string &s, int len) {
    string ret = rnd.nextInt(2) ? randomBinaryString(len) : randomTrickyString(len);
    s += ret;
  }
};
