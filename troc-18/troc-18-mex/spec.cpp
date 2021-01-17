#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 1000;
const int MAXA = 1000;

mt19937 rng(71717);

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  vector<int> A, ans;

  void InputFormat() {
    LINE(N);
    LINE(A % SIZE(N));
  }

  void OutputFormat() {
    LINE(ans % SIZE(N));
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(elementInRange(A, 1, MAXA));
    CONS(uniqueElement(A));
  }

  void StyleConfig() {
    CustomScorer();
  }

  void Subtask1() {
    Points(100);
  }

 private:
  bool elementInRange(const vector<int> &A, int mn, int mx) {
    for (int element : A) {
      if (element < mn || element > mx) return false;
    }
    return true;
  }

  bool uniqueElement(const vector<int> &A) {
    auto tmp = A;
    sort(tmp.begin(), tmp.end());
    for (int i = 1; i < tmp.size(); i++) {
      if (tmp[i] == tmp[i - 1]) return false;
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
        "2",
        "1 2",
    });
    Output({
        "2 1",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
        "1",
        "1",
    });
    Output({
        "1",
    });
  }

  void SampleTestCase3() {
    Subtasks({1});
    Input({
        "4",
        "8 6 4 2",
    });
    Output({
        "6 2 4 8",
    });
  }

  void BeforeTestCase() {
    A.clear();
  }

  void AfterTestCase() {
    shuffle(A.begin(), A.end(), rng);
  }

  void TestGroup1() {
    Subtasks({1});
    //corner case
    CASE(N = 1, A = randomElement(1, 1));
    CASE(N = 1, A = randomElement(2, 2));
    CASE(N = 1000, A = randomElement(1, 1000));
    //permutation(?)
    CASE(N = 500, A = randomElement(250, 750));
    CASE(N = 150, A = randomElement(2, 151));
    //high difference
    CASE(N = 150, A = randomElement(1, 1000, {1}));
    CASE(N = 200, A = randomElement(1, 1000, {2}));
    CASE(N = 250, A = randomElement(1, 1000, {1, 2}));
    //low difference
    CASE(N = 900, A = randomElement(1, 1000, {1, 2}));
    CASE(N = 800, A = randomElement(1, 1000, {1}));
    //permutation
    CASE(N = 749, A = randomElement(1, 749));
    CASE(N = 499, A = randomElement(1, 499));
    CASE(N = 249, A = randomElement(1, 249));
    CASE(N = 99, A = randomElement(1, 99));
  }

  bool allNEQ(const vector<int> &vec, int number) {
    return all_of(vec.begin(), vec.end(), [&](int u) { return u != number; });
  }

  vector<int> generatePermutation(int mn, int mx) {
    vector<int> result(mx - mn + 1);
    int index = mn;
    generate(result.begin(), result.end(), [&index]() { return index++; });

    shuffle(result.begin(), result.end(), rng);
    return result;
  }

  vector<int> randomElement(int mn=1, int mx=MAXA, vector<int> must_exist={}) {
    mx = max(N + mn - 1, mx); //in case vector size > maximum element
    vector<int> result = generatePermutation(mn, mx);

    for (int number : must_exist) {
      if (allNEQ(result, number))
        result.push_back(number);
    }

    result.erase(result.begin(), result.begin() + (result.size() - N));
    return result;
  }
};