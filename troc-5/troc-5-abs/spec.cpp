#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

struct AbsSolver {
  vector<int> arr;
  multiset<pair<int, int>> sortedArr;
  multiset<pair<int, pair<int, int>>> minDiffs;

  AbsSolver() {
  }

  AbsSolver(vector<int> v) {
    arr = v;
    
    for (int i = 0 ; i < arr.size() ; i++) {
      sortedArr.insert({arr[i], i});
    }

    for (int i = 0 ; i < arr.size() ; i++) {
      auto it = sortedArr.lower_bound({arr[i], i});
      it++;

      if (it != sortedArr.end()) {
        int val = (*it).first;
        int j = (*it).second;

        minDiffs.insert({val - arr[i], {i, j}});
      }
    }
  }

  void changeVal(int idx, int newVal) {
    // make 0-based
    idx--;

    // insert left-right into mindiffs
    {
      int i = -1;
      int j = -1;
      auto it = sortedArr.lower_bound({arr[idx], idx});

      if (it != sortedArr.begin()) {
        it--;
        i = (*it).second;
        it++;
      }

      it++;
      if (it != sortedArr.end()) {
        j = (*it).second;
      }
      it--;

      if (i != -1 && j != -1) {
        minDiffs.insert({abs(arr[i] - arr[j]), {i, j}});
      }
    }

    sortedArr.erase({arr[idx], idx});
    arr[idx] = newVal;
    sortedArr.insert({arr[idx], idx});

    // join with left and right
    auto it = sortedArr.lower_bound({arr[idx], idx});
    if (it != sortedArr.begin()) {
      it--;
      int i = (*it).second;
      minDiffs.insert({abs(arr[i] - arr[idx]), {i, idx}});

      it++;
    }

    it++;
    if (it != sortedArr.end()) {
      int i = (*it).second;
      minDiffs.insert({abs(arr[i] - arr[idx]), {i, idx}});
    }
    it--;
  }

  pair<int, int> extractMax() {
    return *sortedArr.rbegin();
  }

  pair<int, int> extractMin() {
    return *sortedArr.begin();
  }

  pair<int, pair<int, int>> extractMinDiff() {
    while (!minDiffs.empty()) {
      pair<int, pair<int, int>> it = *minDiffs.begin();

      int i = it.second.first;
      int j = it.second.second;

      if (abs(arr[i] - arr[j]) != it.first) {
        minDiffs.erase(minDiffs.begin());
      } else {
        return it;
      }
    }

    assert(0);
  }

  int query() {
    int mx = extractMax().first;
    int mn = extractMin().first;
    int minDiff = extractMinDiff().first;

    return mx - mn - minDiff;
  }
};

const int MAXN = 100000;
const int MAXQ = 100000;
const int MAXA = 1000000000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, Q;
  vector<int> A;
  vector<vector<int>> QUERY;
  vector<int> ANS;

  void InputFormat() {
    LINE(N, Q);
    LINE(A % SIZE(N));
    LINES(QUERY) % SIZE(Q);
  }

  void OutputFormat() {
    LINES(ANS) % SIZE(askCount(QUERY));
  }

  void Constraints() {
    CONS(3 <= N && N <= MAXN);
    CONS(1 <= Q && Q <= MAXQ);
    CONS(eachElementBetween(A, 1, MAXA));
    CONS(eachQueryValid(QUERY));
  }

  void Subtask1() {
    Points(100);
  }

 private:
  int askCount(vector<vector<int>> queries) {
    return count_if(queries.begin(), queries.end(), [](vector<int> row) {
      return row[0] == 2;
    });
  }

  bool eachElementBetween(vector<int> v, int lo, int hi) {
    return all_of(v.begin(), v.end(), [&](int x) {
      return lo <= x && x <= hi;
    });
  }

  bool eachQueryValid(vector<vector<int>> query) {
    return all_of(query.begin(), query.end(), [&](vector<int> q) {
      if (q.size() == 1) {
        if (q[0] != 2) return false;

        return true;
      } else if (q.size() == 3) {
        if (q[0] != 1) return false;
        if (q[1] < 1 || q[1] > N) return false;
        if (q[2] < 1 || q[2] > MAXA) return false;

        return true;
      } else {
        return false;
      }
    });
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:

  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "3 4",
      "3 1 10",
      "1 1 2",
      "2",
      "1 2 7",
      "2"
    });

    Output({
      "8",
      "5"
    });
  }

  AbsSolver solver;

  void BeforeTestCase() {
    A.clear();
    QUERY.clear();
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 3,
         Q = 1,
         A = {1, 2, MAXA},
         QUERY = {{2}});

    CASE(N = MAXN,
         Q = MAXQ,
         A = randomArray(N, 1, MAXA),
         generateQuery(N, Q, 0.5));
    
    CASE(N = MAXN,
         Q = MAXQ,
         A = randomArray(N, 1, MAXA),
         generateQuery(N, Q, 0, true));

    CASE(N = MAXN,
         Q = MAXQ,
         A = randomArray(N, 1, 1000),
         generateQuery(N, Q, 0.5, false, 1, 1000));
    
    CASE(N = MAXN,
         Q = MAXQ,
         A = randomArray(N, 1, 100000),
         generateQuery(N, Q, 0.5, false, 1, 100000));
    
    vector<double> chances = {0.1, 0.25, 0.5, 0.75, 0.8, 0.9};
    for (double chance : chances) {
      for (int it = 0 ; it < 2 ; it++) {
        CASE(N = rnd.nextInt(3, MAXN),
              Q = rnd.nextInt(1, MAXQ),
              A = randomArray(N, 1, MAXA),
              generateQuery(N, Q, chance));
        
        CASE(N = rnd.nextInt(MAXN / 2, MAXN),
              Q = rnd.nextInt(MAXQ / 2, MAXQ),
              A = randomArray(N, 1, MAXA),
              generateQuery(N, Q, chance));
      }

      CASE(N = rnd.nextInt(MAXN / 2, MAXN),
              Q = rnd.nextInt(MAXQ / 2, MAXQ),
              A = randomArray(N, 1, MAXA),
              generateQuery(N, Q, chance, true));

      CASE(N = rnd.nextInt(MAXN / 2, MAXN),
              Q = rnd.nextInt(MAXQ / 2, MAXQ),
              A = randomArray(N, 1, 1000),
              generateQuery(N, Q, chance, false, 1, 1000));
      
      CASE(N = rnd.nextInt(MAXN / 2, MAXN),
              Q = rnd.nextInt(MAXQ / 2, MAXQ),
              A = randomArray(N, 1, 100000),
              generateQuery(N, Q, chance, false, 1, 100000));
    }
  }

 private:
  vector<int> randomArray(int n, int lo, int hi) {
    vector<int> ret(n);
    for (int &it : ret) {
      it = rnd.nextInt(lo, hi);
    }
    return ret;
  }

  void changeVal(int idx, int val) {
    idx++;
    QUERY.push_back({1, idx, val});
    solver.changeVal(idx, val);
  }

  void askQuery() {
    QUERY.push_back({2});
  }

  void generateQuery(int n, int q, double changeChance, bool isAlternating = false, int lowAVal = -1, int hiAVal = -1) {
    if (lowAVal == -1) {
      lowAVal = 1;
    }
    if (hiAVal == -1) {
      hiAVal = MAXA;
    }

    solver = AbsSolver(A);

    for (int i = 0 ; i < q ; i++) {
      if ((isAlternating && i % 2 == 1) || (!isAlternating && rnd.nextDouble(0, 1) <= changeChance)) {
        int opt = rnd.nextInt(7);
        int idx = -1;
        int val = rnd.nextInt(lowAVal, hiAVal);

        if (opt == 0) {
          idx = rnd.nextInt(n);
        } else if (opt <= 2) {
          idx = solver.extractMax().second;
        } else if (opt <= 4) {
          idx = solver.extractMin().second;
        } else {
          idx = rnd.nextInt(2) ? solver.extractMinDiff().second.first : solver.extractMinDiff().second.second;
        }

        changeVal(idx, val);
      } else {
        askQuery();
      }
    }
  }
};
