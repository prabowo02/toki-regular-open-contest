#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

// 2MAXN - 3 <= MAXM
const int MAXN = 1e5;
const int MAXM = 2e5;
const int MAXC = 1e9;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M;
  vector<int> W;
  vector<int> X;
  vector<int> Y;
  vector<int> Z;

  int ans;

  void InputFormat() {
    LINE(N, M);
    LINE(W % SIZE(N));
    LINES(X, Y, Z) % SIZE(M);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(5);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(3 <= N && N <= MAXN);
    CONS(0 <= M && M <= MAXM);

    CONS(Compare(vector<int>(N, 1), W, [&](int x, int y) { return x <= y; }));
    CONS(Compare(W, vector<int>(N, MAXC), [&](int x, int y) { return x <= y; }));

    CONS(Compare(vector<int>(M, 1), X, [&](int x, int y) { return x <= y; }));
    CONS(Compare(X, Y, [&](int x, int y) { return x < y; }));
    CONS(Compare(Y, vector<int>(M, N), [&](int x, int y) { return x <= y; }));

    CONS(Compare(vector<int>(M, 1), Z, [&](int x, int y) { return x <= y; }));
    CONS(Compare(Z, vector<int>(M, MAXC), [&](int x, int y) { return x <= y; }));
    
    CONS(NotIntersect(X, Y));
  }

  void Subtask1() {
    Points(100);
  }

 private:
  template <typename Comparator>
  bool Compare(const vector<int> &lo, const vector<int> &hi, const Comparator &cmp) {
    if (lo.size() != hi.size()) {
      return false;
    }
    for (int i = 0; i < (int) lo.size(); i++) {
      if (!cmp(lo[i], hi[i])) {
        return false;
      }
    }
    return true;
  };

  bool NotIntersect(vector<int> L, vector<int> R) {
    [&]() { // Check Unique
      set<pair<int, int>> s;
      for (int i = 0; i < (int) L.size(); i++) {
        s.insert({L[i], R[i]});
      }
      if (s.size() != L.size()) {
        return false;
      }
    }();

    [&]() { // Coordinate Compression
      vector<int> coord;
      for (int i = 0; i < (int) L.size(); i++) {
        coord.emplace_back(L[i]);
        coord.emplace_back(R[i]);
      }
      sort(begin(coord), end(coord));
      coord.resize(unique(begin(coord), end(coord)) - begin(coord));
      for (int i = 0; i < (int) L.size(); i++) {
        L[i] = lower_bound(begin(coord), end(coord), L[i]) - begin(coord);
        R[i] = lower_bound(begin(coord), end(coord), R[i]) - begin(coord);
      }
    }();

    if (L.empty()) {
      return true;
    }

    // If intersect, then there exist L[i] < L[j] < R[i] < R[j]
    // Create a segment tree, tree[L[i]] = maximum R[i]
    // If intersect, then there exist RangeMaxQuery[L[i] + 1...R[i] - 1] > R[i]

    int sz = max(*max_element(begin(L), end(L)), *max_element(begin(R), end(R))) + 1;
    vector<int> tree(2 * sz, -1);
    for (int i = 0; i < (int) L.size(); i++) {
      tree[L[i] + sz] = max(tree[L[i] + sz], R[i]);
    }
    for (int i = sz - 1; i > 0; i--) {
      tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
    }
    const auto RangeMaxQuery = [&](int l, int r) {
      int res = -1;
      for (l += sz, r += sz + 1; l < r; l /= 2, r /= 2) {
        if (l & 1) res = max(res, tree[l++]);
        if (r & 1) res = max(res, tree[--r]);
      }
      return res;
    };

    for (int i = 0; i < (int) L.size(); i++) {
      if (RangeMaxQuery(L[i] + 1, R[i] - 1) > R[i]) {
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
      "6 2",
      "1 2 3 4 5 6",
      "1 3 7",
      "4 6 8",
    });
    Output({
      "85",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "3 3",
      "2 2 2",
      "1 2 1",
      "2 3 1",
      "1 3 1",
    });
    Output({
      "3",
    });
  }
  
  void BeforeTestCase() {
    N = 0;
    M = 0;
    W.clear();
    X.clear();
    Y.clear();
    Z.clear();
  }

  void AfterTestCase() {
    vector<int> order(M);
    iota(begin(order), end(order), 0);
    rnd.shuffle(begin(order), end(order));

    vector<int> nX(M), nY(M), nZ(M);
    for (int i = 0; i < M; i++) {
      nX[order[i]] = X[i];
      nY[order[i]] = Y[i];
      nZ[order[i]] = Z[i];
    }

    X = nX;
    Y = nY;
    Z = nZ;

    int shift = rnd.nextInt(N);
    for (int i = 0; i < M; i++) {
      X[i] = (X[i] + shift) % N + 1;
      Y[i] = (Y[i] + shift) % N + 1;
      if (X[i] > Y[i]) {
        swap(X[i], Y[i]);
      }
    }
  }

  void TestGroup1() {
    Subtasks({1});

    // N = 3
    CASE(N = 3; M = 0; W = RandomVector(N, 1, 1000); Z = RandomVector(M, 1, 1000); RandomGraph(); RedundantEdges(1, 1000));
    CASE(N = 3; M = 0; W = RandomVector(N, 1, MAXC); Z = RandomVector(M, 1, MAXC); RandomGraph(); RedundantEdges(1, MAXC));

    // No Railways
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = 0; W = RandomVector(N, 1, 1000); Z = RandomVector(M, 1, 1000); RandomGraph());
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = 0; W = RandomVector(N, 1, MAXC); Z = RandomVector(M, 1, MAXC); RandomGraph());

    // Short Railways
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); W = RandomVector(N, 1, 1000); ShortRailways(1000); RedundantEdges(3, 1000));
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); W = RandomVector(N, 1, MAXC); ShortRailways(MAXC); RedundantEdges(3, MAXC));

    // Maximum Test
    CASE(N = MAXN; M = N - 3; W = RandomVector(N, 1, 1000); Z = RandomVector(M, 1, 1000); RandomGraph(); RedundantEdges(1, 1000));
    CASE(N = MAXN; M = N - 3; W = RandomVector(N, 1, MAXC); Z = RandomVector(M, 1, MAXC); RandomGraph(); RedundantEdges(1, MAXC));

    // Triangle Fractal
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); W = RandomVector(N, 1, 1000); Z = RandomVector(M, 1, 1000); TriangleFractal(); RedundantEdges(3, 1000));
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); W = RandomVector(N, 1, MAXC); Z = RandomVector(M, 1, MAXC); TriangleFractal(); RedundantEdges(3, MAXC));

    // One Focus
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); W = RandomVector(N, 1, 1000); FocusPoints(1, 1000); RedundantEdges(3, 1000));
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); W = RandomVector(N, 1, MAXC); FocusPoints(1, MAXC); RedundantEdges(3, MAXC));

    // Multiple Foci
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); W = RandomVector(N, 1, 1000); FocusPoints(rnd.nextInt(1, 100), 1000); RedundantEdges(3, 1000));
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); W = RandomVector(N, 1, MAXC); FocusPoints(rnd.nextInt(1, 100), MAXC); RedundantEdges(3, MAXC));

    // Cheap Roads
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = rnd.nextInt(100, 500); W = RandomVector(N, 1, 1000); Z = RandomVector(M, 1, MAXC); RandomGraph(); RedundantEdges(3, 1000));
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = rnd.nextInt(0, N - 3); W = RandomVector(N, 1, 1000); Z = RandomVector(M, 1, MAXC); RandomGraph(); RedundantEdges(3, MAXC));

    // Cheap Railways
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = rnd.nextInt(100, 500); W = RandomVector(N, 1, MAXC); Z = RandomVector(M, 1, 1000); RandomGraph(); RedundantEdges(3, 1000));
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = rnd.nextInt(0, N - 3); W = RandomVector(N, 1, MAXC); Z = RandomVector(M, 1, 1000); RandomGraph(); RedundantEdges(3, MAXC));

    // Random Graph
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = rnd.nextInt(0, N - 3); W = RandomVector(N, 1, 1000); Z = RandomVector(M, 1, 1000); RandomGraph(); RedundantEdges(3, 1000));
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = rnd.nextInt(0, N - 3); W = RandomVector(N, 1, MAXC); Z = RandomVector(M, 1, MAXC); RandomGraph(); RedundantEdges(3, MAXC));

    // Cost is a Power of Two
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = rnd.nextInt(100, 500); W = PowerOfTwoVector(N); Z = PowerOfTwoVector(M); RandomGraph(); RedundantEdges(3, 1000));
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = rnd.nextInt(0, N - 3); W = PowerOfTwoVector(N); Z = PowerOfTwoVector(M); RandomGraph(); RedundantEdges(3, MAXC));

    // Maximum Cost
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = rnd.nextInt(100, 500); W = RandomVector(N, MAXC, MAXC); Z = RandomVector(M, MAXC, MAXC); RandomGraph(); RedundantEdges(3, MAXC));
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = rnd.nextInt(0, N - 3); W = RandomVector(N, MAXC, MAXC); Z = RandomVector(M, MAXC, MAXC); RandomGraph(); RedundantEdges(3, MAXC));
    
    // Maximum Test Maximum Cost
    CASE(N = MAXN; M = N - 3; W = RandomVector(N, MAXC, MAXC); Z = RandomVector(M, MAXC, MAXC); RandomGraph(); RedundantEdges(1, MAXC));
  }

 private:
  vector<int> RandomVector(int sz, int lo, int hi) {
    vector<int> res(sz);
    for (int i = 0; i < sz; i++) {
      res[i] = rnd.nextInt(lo, hi);
    }
    return res;
  }

  vector<int> PowerOfTwoVector(int sz) {
    int lo = 0, hi = 29;
    vector<int> res(sz);
    for (int i = 0; i < sz; i++) {
      res[i] = 1 << rnd.nextInt(lo, hi);
    }
    return res;
  }

  void RedundantEdges(int denominator, int maxcost) {
    for (int i = 0; i < N; i++) {
      if (rnd.nextInt(denominator) == 0) {
        M += 1;
        X.emplace_back((i + 0) % N);
        Y.emplace_back((i + 1) % N);
        Z.emplace_back(rnd.nextInt(1, maxcost));
      }
    }
  }

  void RandomGraph() {
    vector<int> all(N);
    iota(begin(all), end(all), 0);
    set<pair<int, vector<int>>> circles;
    circles.emplace(rnd.nextInt(MAXC), all);

    while (X.size() < M) {
      int r = rnd.nextInt(0, prev(end(circles))->first);
      auto it = circles.lower_bound({r, {}});
      vector<int> comp = it->second;
      circles.erase(it);

      if (comp.size() <= 3) {
        continue;
      }

      int u = rnd.nextInt(comp.size());
      int v = rnd.nextInt(comp.size());
      while (min(abs(u - v), int(comp.size()) - abs(u - v)) <= 1) {
        u = rnd.nextInt(comp.size());
        v = rnd.nextInt(comp.size());
      }
      if (u > v) {
        swap(u, v);
      }

      assert(u < v);
      X.emplace_back(comp[u]);
      Y.emplace_back(comp[v]);

      vector<int> c1, c2;
      for (int i = 0; i < (int) comp.size(); i++) {
        if (u <= i && i <= v) {
          c1.emplace_back(comp[i]);
        }
        if (i <= u || v <= i) {
          c2.emplace_back(comp[i]);
        }
      }

      circles.emplace(rnd.nextInt(MAXC), c1);
      circles.emplace(rnd.nextInt(MAXC), c2);
    }
  }

  void ShortRailways(int maxcost) {
    int current = 0;
    while (current < N) {
      int len = rnd.nextInt(1, 4);
      if (current + len <= N) {
        if (len > 1) {
          M += 1;
          X.emplace_back(current);
          Y.emplace_back((current + len) % N);
          Z.emplace_back(rnd.nextInt(1, maxcost));
        }
        current += len;
      }
    }
  }

  void TriangleFractal() {
    vector<int> all(N);
    iota(begin(all), end(all), 0);
    queue<vector<int>> circles;
    circles.emplace(all);

    while (X.size() < M) {
      vector<int> comp = circles.front();
      circles.pop();

      if (comp.size() <= 3) {
        continue;
      }

      if (comp.size() <= 8) {
        int u = rnd.nextInt(comp.size());
        int v = rnd.nextInt(comp.size());
        while (min(abs(u - v), int(comp.size()) - abs(u - v)) <= 1) {
          u = rnd.nextInt(comp.size());
          v = rnd.nextInt(comp.size());
        }
        if (u > v) {
          swap(u, v);
        }

        assert(u < v);
        X.emplace_back(comp[u]);
        Y.emplace_back(comp[v]);

        vector<int> c1, c2;
        for (int i = 0; i < (int) comp.size(); i++) {
          if (u <= i && i <= v) {
            c1.emplace_back(comp[i]);
          }
          if (i <= u || v <= i) {
            c2.emplace_back(comp[i]);
          }
        }

        circles.emplace(c1);
        circles.emplace(c2);
        continue;
      }

      int rot = rnd.nextInt(comp.size());
      rotate(begin(comp), begin(comp) + rot, end(comp));

      int sz = comp.size() / 3;
      vector<int> c1, c2, c3;
      for (int i = 0; i < (int) comp.size(); i++) {
        if (i <= sz) {
          c1.emplace_back(comp[i]);
        } 
        if (sz <= i && i <= sz + sz) {
          c2.emplace_back(comp[i]);
        }
        if (sz + sz <= i) {
          c3.emplace_back(comp[i]);
        }
      }
      c3.emplace_back(comp[0]);

      if (X.size() < M) {
        X.emplace_back(comp[0 * sz]);
        Y.emplace_back(comp[1 * sz]);
      }
      if (X.size() < M) {
        X.emplace_back(comp[1 * sz]);
        Y.emplace_back(comp[2 * sz]);
      }
      if (X.size() < M) {
        X.emplace_back(comp[0 * sz]);
        Y.emplace_back(comp[2 * sz]);
      }

      circles.emplace(c1);
      circles.emplace(c2);
      circles.emplace(c3);
    }
  }

  void FocusPoints(int num, int maxcost) {
    vector<int> focus(N);
    iota(begin(focus), end(focus), 0);
    rnd.shuffle(begin(focus), end(focus));
    focus.resize(num);

    sort(begin(focus), end(focus));
    for (int i = 0; i < (int) focus.size(); i++) {
      int u = focus[i];
      int v = focus[(i + 1) % focus.size()];
      vector<int> between;
      if (u < v) {
        for (int j = u + 1; j < v; j++) {
          between.emplace_back(j);
        }
      } else {
        for (int j = u + 1; j < N; j++) {
          between.emplace_back(j);
        }
        for (int j = 0; j < v; j++) {
          between.emplace_back(j);
        }
      }

      int piv = rnd.nextInt(0, between.size());
      for (int j = 0; j < piv; j++) {
        if (min(abs(u - between[j]), N - abs(u - between[j])) > 1) {
          M += 1;
          X.emplace_back(u);
          Y.emplace_back(between[j]);
          Z.emplace_back(rnd.nextInt(1, maxcost));
        }
      }
      for (int j = piv; j < (int) between.size(); j++) {
        if (min(abs(v - between[j]), N - abs(v - between[j])) > 1) {
          M += 1;
          X.emplace_back(v);
          Y.emplace_back(between[j]);
          Z.emplace_back(rnd.nextInt(1, maxcost));
        }
      }
    }
  }
};
