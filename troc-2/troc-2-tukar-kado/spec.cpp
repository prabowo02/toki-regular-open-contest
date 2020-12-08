#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAX_N = 2000;
const int MAX_X = 2000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  vector<int> X;
  int ANS;

  void InputFormat() { 
    LINE(N);
    LINE(X % SIZE(N)); 
  }

  void OutputFormat() {
    LINE(ANS);
  }

  void Constraints() {
    CONS(2 <= N && N <= MAX_N);
    CONS(eachElementBetween(X, 0, MAX_X));
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

    Input({"4", "1 1 2 2"});
    
    Output({"6"});
  }

  void BeforeTestCase() {
    X.clear();
  }

  void AfterTestCase() {
    rolling();
  }

  void TestGroup1() {
    Subtasks({1});

    // invalid
    CASE(N = 2, X = {4, 5});
    CASE(N = rnd.nextInt(3, MAX_N), invalidOddSum());
    CASE(N = rnd.nextInt(3, MAX_N), invalidCase(0));
    CASE(N = rnd.nextInt(3, MAX_N), invalidCase(rnd.nextInt(MAX_X/2)));

    CASE(N = MAX_N, invalidCase(0));
    CASE(N = MAX_N, invalidCase(rnd.nextInt(MAX_X/2)));

    // valid
    CASE(N = 2, X.assign(N, rnd.nextInt(1, MAX_X)));

    CASE(N = rnd.nextInt(2, N), X.assign(N, 0));

    CASE(N = rnd.nextInt(1, MAX_N/2) * 2, X.assign(N, rnd.nextInt(MAX_X/2) * 2 + 1));
    CASE(N = rnd.nextInt(1, MAX_N/2 - 1) * 2 + 1, X.assign(N, rnd.nextInt(MAX_X/2) * 2 + 1));
    CASE(N = rnd.nextInt(1, MAX_N/2 - 1) * 2 + 1, X.assign(N, rnd.nextInt(MAX_X/2) * 2));

    CASE(N = rnd.nextInt(MAX_N/2, MAX_N), validCase(0, rnd.nextInt(1, MAX_X)));

    for (int i = 0; i < 2; ++i) {
      int lo = rnd.nextInt(1, MAX_X-1);
      int hi = rnd.nextInt(lo+1, MAX_X);
      CASE(N = rnd.nextInt(MAX_N/2, MAX_N), validCase(lo, hi));
    }

    CASE(N = MAX_N, X.assign(N, MAX_X));
    CASE(N = MAX_N-1, X.assign(N, MAX_X));
    CASE(N = MAX_N, validCase(0, MAX_X));

    for (int i = 0; i < 4; ++i) {
      int lo = rnd.nextInt(MAX_X);
      int hi = MAX_X;
      CASE(N = MAX_N - (i & 1), validCase(lo, hi));
    }
  }

 private:
  void invalidOddSum() {
    int hi = rnd.nextInt(1, MAX_X-1);
    int lo = rnd.nextInt(hi);
    validCase(lo, hi);
    ++X[rnd.nextInt(N)];
  }

  void invalidCase(int lo) {
    assert(N > 2);
    int hi = rnd.nextInt(lo, MAX_X/2);
    hi = max(hi, lo);
    validCase(lo, hi);
    int found = false, counter = rnd.nextInt(10);
    while (!found || counter-- > 0) {
      int l = rnd.nextInt(N/2), r = rnd.nextInt(N/2);
      while (l == r)
        rnd.nextInt(N/2);
      if (l > r)
        swap(l, r);
      l *= 2, r *= 2;
      int sum_even = 0, sum_odd = 0;
      for (int i = l; i <= r; ++i) {
        if (i & 1)
          sum_odd += X[i];
        else
          sum_even += X[i];
      }
      int cnt = (r-l) / 2;
      int need = sum_even - sum_odd + 1;
      if (need & 1)
        ++need;
      if (sum_odd > sum_even)
        continue;
      if (need > cnt * MAX_X - sum_odd)
        continue;
      while (need > 0) {
        int id = l + rnd.nextInt(cnt) * 2 + 1;
        assert(l < id && id < r);
        if (X[id] == MAX_X) continue;
        int add = rnd.nextInt(1, min(MAX_X - X[id], need));
        X[id] += add;
        need -= add;
      }
      found = true;
    }
  }

  void validCase(int lo, int hi) {
    X.assign(N, lo);
    int num_min = rnd.nextInt(N/2);
    set<int> not_mins;
    if (N & lo & 1) {
      int id = rnd.nextInt(N);
      ++X[id];
      not_mins.insert(id);
    }
    while (not_mins.size() < N - num_min) {
      int id = rnd.nextInt(N);
      not_mins.insert(id);
      not_mins.insert((id+1) % N);
    }
    for (int i = 0; i < N; ++i) {
      int next = (i+1) % N;
      if (not_mins.count(i) && not_mins.count(next)) {
        int add = rnd.nextInt(hi - max(X[i], X[next]) + 1);
        X[i] += add;
        X[next] += add;
      }
    }
    for (int i = 0; i < N; ++i)
      if (X[i] == hi)
        return;
    while (true) {
      int id = rnd.nextInt(N);
      int next = (id + 1) % N;
      if (not_mins.count(id) && not_mins.count(next)) {
        int add = hi - max(X[id], X[next]);
        X[id] += add;
        X[next] += add;
        break;
      }
    }
  }

  void rolling() {
    int shift = rnd.nextInt(N);
    vector<int> tmp(N);
    for (int i = 0; i < N; ++i)
      tmp[(i+shift) % N] = X[i];
    for (int i = 0; i < N; ++i)
      X[i] = tmp[i];
  }
};
