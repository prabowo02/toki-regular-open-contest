#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
  protected:

    int n;
    string s1, s2;
    int ans;

    void InputFormat() {
      LINE(n);
      LINE(s1);
      LINE(s2);
    }

    void OutputFormat() {
      LINE(ans);
    }

    void Constraints() {
      CONS(1 <= n && n <= 50);
      CONS(s1.length() == n);
      CONS(s2.length() == n);
      CONS(allGBK(s1));
      CONS(allGBK(s2));
    }

    void Subtask1() {
      Points(100);
    }

  private:
    bool allGBK(string s) {
      for (int i = 0; i < s.size(); ++i) {
        if(s[i] != 'G' && s[i] != 'B' && s[i] != 'K') {
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
      Input({ "3",
              "GBK",
              "BKK"});
      Output({"2"});
    }

    void TestGroup1() {
      Subtasks({1});

      for (int i = 0; i < 10; ++i) {
        CASE(buildDifferentStrings(1));
      }

      for (int i = 0; i < 10; ++i) {
        CASE(buildDifferentStrings(2));
      }

      for (int i = 0; i < 10; ++i) {
        CASE(buildDifferentStrings(5));
      }

      for (int i = 0; i < 10; ++i) {
        CASE(buildDifferentStrings(10));
      }

      for (int i = 0; i < 10; ++i) {
        CASE(buildDifferentStrings(20));
      }

      for (int i = 0; i < 10; ++i) {
        CASE(buildDifferentStrings(50));
      }

      for (int i = 0; i < 10; ++i) {
        CASE(buildSameStrings(5));
      }

      for (int i = 0; i < 10; ++i) {
        CASE(buildSameStrings(50));
      }

      for (int i = 0; i < 10; ++i) {
        CASE(buildWinningStrings(50));
      }

      for (int i = 0; i < 10; ++i) {
        CASE(buildLosingStrings(50));
      }

      for (int i = 0; i < 10; ++i) {
        CASE(buildFullStrings(50));
      }

      for (int i = 0; i < 10; ++i) {
        CASE(buildZeroStrings(50));
      }
    }

  private:
    char letters[3] = {'G', 'B', 'K'};

    string fairString(int l) {
      string s = "";
      for (int i = 0; i < l; ++i) {
        s += letters[rand() % 3];
      }
      return s;
    }

    string unfairString(int l, int j) {
      string s = "";
      for (int i = 0; i < l; ++i) {
        s += letters[(min(rand() % 10, 2) + 1 + j) % 3];
      }
      return s;
    }

    string copyString(int l, int j) {
      string s = "";
      for (int i = 0; i < l; ++i) {
        s += letters[j];
      }
      return s;
    }

    void buildDifferentStrings(int l) {
      n = l;
      s1 = fairString(l);
      s2 = fairString(l);
    }

    void buildSameStrings(int l) {
      n = l;
      string s = fairString(l);
      s1 = s;
      s2 = s;
    }

    void buildWinningStrings(int l) {
      n = l;
      int j = rand() % 3;
      int k = (j + 2) % 3;
      s1 = unfairString(l, j);
      s2 = unfairString(l, k);
    }

    void buildLosingStrings(int l) {
      n = l;
      int j = rand() % 3;
      int k = (j + 1) % 3;
      s1 = unfairString(l, j);
      s2 = unfairString(l, k);
    }

    void buildFullStrings(int l) {
      n = l;
      int j = rand() % 3;
      int k = (j + 2) % 3;
      s1 = copyString(l, j);
      s2 = copyString(l, k);
    }

    void buildZeroStrings(int l) {
      n = l;
      int j = rand() % 3;
      int k = (j + 1) % 3;
      s1 = copyString(l, j);
      s2 = copyString(l, k);
    }
};
