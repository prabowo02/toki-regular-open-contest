#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MX = 100;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int A, B, C;
  string ANS;

  void InputFormat() { LINE(A, B, C); }

  void OutputFormat() { LINE(ANS); }

  void Constraints() {
    CONS(1 <= A && A <= MX);
    CONS(1 <= B && B <= MX);
    CONS(1 <= C && C <= MX);
    CONS(hasSolution(A, B, C));
  }

  void Subtask1() {}

 private:
  bool hasSolution(int A, int B, int C) {
    bool dp[A+1][B+1][C+1];
    dp[0][0][0] = 1;

    for(int i = 0 ; i <= A ; i++)
      for(int j = 0 ; j <= B ; j++)
        for(int k = 0 ; k <= C ; k++) {
          if(i == 0 && j == 0 && k == 0) continue;
          dp[i][j][k] = 0;

          if(i >= 1 && j >= 2 && k >= 4) dp[i][j][k] |= dp[i-1][j-2][k-4];
          if(i >= 1 && j >= 4 && k >= 2) dp[i][j][k] |= dp[i-1][j-4][k-2];
          if(i >= 2 && j >= 1 && k >= 4) dp[i][j][k] |= dp[i-2][j-1][k-4];
          if(i >= 2 && j >= 4 && k >= 1) dp[i][j][k] |= dp[i-2][j-4][k-1];
          if(i >= 4 && j >= 1 && k >= 2) dp[i][j][k] |= dp[i-4][j-1][k-2];
          if(i >= 4 && j >= 2 && k >= 1) dp[i][j][k] |= dp[i-4][j-2][k-1];
        }
    
    return dp[A][B][C];
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({"12 6 3"});
    Output({"YA"});
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({"22 13 7"});
    Output({"TIDAK"});
  }

  void TestGroup1() {
    Subtasks({1});

    init();

    CASE(A = 1, B = 2, C = 4);
    CASE(A = 1, B = 4, C = 2);
    CASE(A = 2, B = 1, C = 4);
    CASE(A = 2, B = 4, C = 1);
    CASE(A = 4, B = 1, C = 2);
    CASE(A = 4, B = 2, C = 1);

    for(int i = 0 ; i < 3 ; i++)
      CASE(noAnswerMaxDivisible4Twice());
    for(int i = 0 ; i < 3 ; i++)
      CASE(yesAnswer());
      
    for(int i = 0 ; i < 3 ; i++)
      CASE(noAnswerMaxDivisible4());
    for(int i = 0 ; i < 3 ; i++)
      CASE(yesAnswer());
      
    for(int i = 0 ; i < 3 ; i++)
      CASE(noAnswerSimple());
    for(int i = 0 ; i < 3 ; i++)
      CASE(yesAnswer());

    for(int i = 0 ; i < 5 ; i++)
      CASE(randomAnswer());
  }

 private:
  bool dp[MX+1][MX+1][MX+1];

  void init() {
    dp[0][0][0] = 1;

    for(int i = 0 ; i <= MX ; i++)
      for(int j = 0 ; j <= MX ; j++)
        for(int k = 0 ; k <= MX ; k++) {
          if(i == 0 && j == 0 && k == 0) continue;
          dp[i][j][k] = 0;

          if(i >= 1 && j >= 2 && k >= 4) dp[i][j][k] |= dp[i-1][j-2][k-4];
          if(i >= 1 && j >= 4 && k >= 2) dp[i][j][k] |= dp[i-1][j-4][k-2];
          if(i >= 2 && j >= 1 && k >= 4) dp[i][j][k] |= dp[i-2][j-1][k-4];
          if(i >= 2 && j >= 4 && k >= 1) dp[i][j][k] |= dp[i-2][j-4][k-1];
          if(i >= 4 && j >= 1 && k >= 2) dp[i][j][k] |= dp[i-4][j-1][k-2];
          if(i >= 4 && j >= 2 && k >= 1) dp[i][j][k] |= dp[i-4][j-2][k-1];
        }
  }

  void getRandomSatisfy(function<bool(int, int, int)> f) {
    vector<pair<int, pair<int, int>>> v;

    for (int i = 1; i <= MX; i++)
      for (int j = 1; j <= MX; j++)
        for (int k = 1; k <= MX; k++)
          if (f(i, j, k)) v.push_back({i, {j, k}});

    int idx = rnd.nextInt(v.size());

    A = v[idx].first;
    B = v[idx].second.first;
    C = v[idx].second.second;
  }

  void randomAnswer() {
    function<bool(int, int, int)> f = [&](int i, int j, int k) {
      return dp[i][j][k];
    };

    getRandomSatisfy(f);
  }

  void yesAnswer() {
    function<bool(int, int, int)> f = [&](int i, int j, int k) {
      int mx = max(i, max(j, k));
      int sum = i + j + k;

      return dp[i][j][k] && mx == sum / 7 * 4;
    };
    
    getRandomSatisfy(f);
  }

  void noAnswerSimple() {
    function<bool(int, int, int)> f = [&](int i, int j, int k) {
      int mx = max(i, max(j, k));
      int sum = i + j + k;

      return dp[i][j][k] && mx != sum / 7 * 4;
    };

    getRandomSatisfy(f);
  }

  void noAnswerMaxDivisible4() {
    function<bool(int, int, int)> f = [&](int i, int j, int k) {
      int mx = max(i, max(j, k));
      int sum = i + j + k;

      return dp[i][j][k] && mx != sum / 7 * 4 && mx % 4 == 0;
    };

    getRandomSatisfy(f);
  }

  void noAnswerMaxDivisible4Twice() {
    function<bool(int, int, int)> f = [&](int i, int j, int k) {
      int mx = max(i, max(j, k));
      int mn = min(i, min(j, k));
      int sum = i + j + k;
      int mid = sum - mx - mn;

      return dp[i][j][k] && mx != sum / 7 * 4 && mx % 4 == 0 && mx >= mid * 2;
    };

    getRandomSatisfy(f);
  }
};
