#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

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

vector<int> arr;
int n, q;
AbsSolver solver;

void read() {
  scanf("%d %d", &n, &q);
  for (int i = 0 ; i < n ; i++) {
    int x; scanf("%d", &x);
    arr.push_back(x);
  }
}

void work() {
  solver = AbsSolver(arr);

  for (int i = 0 ; i < q ; i++) {
    int opt; scanf("%d", &opt);

    if (opt == 1) {
      int idx, val;
      scanf("%d %d", &idx, &val);

      solver.changeVal(idx, val);
    } else {
      printf("%d\n", solver.query());
    }
  }
}

int main() {
  read();
  work();
  return 0;
}