#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 100;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M;
  vector<int> U;
  vector<int> V;

  int answer;

  void InputFormat() {
    LINE(N, M);
    LINES(U, V) % SIZE(M);
  }

  void OutputFormat() {
    LINE(answer);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(3 <= N && N <= MAXN);
    CONS(0 <= M && M <= N + N - 3);

    CONS(Compare(vector<int>(M, 1), U, [&](int x, int y) { return x <= y; }));
    CONS(Compare(U, V, [&](int x, int y) { return x < y; }));
    CONS(Compare(V, vector<int>(M, N), [&](int x, int y) { return x <= y; }));

    CONS(NotIntersect(U, V));
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
    if (L.size() != R.size()) {
      return false;
    }
    for (int i = 0; i < int(L.size()); i++) {
      for (int j = 0; j < int(L.size()); j++) {
        if (i == j) {
          continue;
        }
        if (L[i] == L[j] && R[i] == R[j]) {
          return false;
        }
        if (L[i] < L[j] && L[j] < R[i] && R[i] < R[j]) {
          return false;
        }
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
      "6 3",
      "1 6",
      "3 5",
      "2 5",
    });
    Output({
      "6",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "3 0",
    });
    Output({
      "3",
    });
  }

  void BeforeTestCase() {
    N = 0;
    M = 0;
    U.clear();
    V.clear();
  }

  void AfterTestCase() {
    vector<int> order(M);
    iota(begin(order), end(order), 0);
    rnd.shuffle(begin(order), end(order));

    vector<int> nX(M), nY(M);
    for (int i = 0; i < M; i++) {
      nX[order[i]] = U[i];
      nY[order[i]] = V[i];
    }

    U = nX;
    V = nY;

    int shift = rnd.nextInt(N);
    for (int i = 0; i < M; i++) {
      U[i] = (U[i] + shift) % N + 1;
      V[i] = (V[i] + shift) % N + 1;
      if (U[i] > V[i]) {
        swap(U[i], V[i]);
      }
    }
  }

  void TestGroup1() {
    Subtasks({1});

    // N = 3
    CASE(N = 3; M = 0; RandomGraph(); RedundantEdges(1));
    CASE(N = 3; M = 0; RandomGraph(); RedundantEdges(1));

    // No Edges
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = 0; RandomGraph());
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = 0; RandomGraph());

    // Short Edges
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); ShortRailways(); RedundantEdges(3));
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); ShortRailways(); RedundantEdges(3));

    // Maximum Test
    CASE(N = MAXN; M = N - 3; RandomGraph(); RedundantEdges(1));
    CASE(N = MAXN; M = N - 3; RandomGraph(); RedundantEdges(1));

    // Triangle Fractal
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); TriangleFractal(); RedundantEdges(3));
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); TriangleFractal(); RedundantEdges(3));

    // One Focus
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); FocusPoints(1); RedundantEdges(3));
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); FocusPoints(1); RedundantEdges(3));

    // Multiple Foci
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); FocusPoints(rnd.nextInt(1, 50)); RedundantEdges(3));
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); FocusPoints(rnd.nextInt(1, 50)); RedundantEdges(3));

    // No Adjacent Edge
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = rnd.nextInt(N - 10, N - 3); RandomGraph(); RedundantEdges(1e9));
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = rnd.nextInt(N - 80, N - 3); RandomGraph(); RedundantEdges(1e9));

    // Small M
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = rnd.nextInt(10, 20); RandomGraph(); RedundantEdges(3));
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = rnd.nextInt(30, 50); RandomGraph(); RedundantEdges(3));

    // Random
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = rnd.nextInt(N - 10, N - 3); RandomGraph(); RedundantEdges(5));
    CASE(N = rnd.nextInt(MAXN - 9, MAXN); M = rnd.nextInt(N - 80, N - 3); RandomGraph(); RedundantEdges(5));
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

  void RedundantEdges(int denominator) {
    for (int i = 0; i < N; i++) {
      if (rnd.nextInt(denominator) == 0) {
        M += 1;
        U.emplace_back((i + 0) % N);
        V.emplace_back((i + 1) % N);
      }
    }
  }

  void RandomGraph() {
    vector<int> all(N);
    iota(begin(all), end(all), 0);
    set<pair<int, vector<int>>> circles;
    circles.emplace(rnd.nextInt(int(1e9)), all);

    while (U.size() < M) {
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
      U.emplace_back(comp[u]);
      V.emplace_back(comp[v]);

      vector<int> c1, c2;
      for (int i = 0; i < (int) comp.size(); i++) {
        if (u <= i && i <= v) {
          c1.emplace_back(comp[i]);
        }
        if (i <= u || v <= i) {
          c2.emplace_back(comp[i]);
        }
      }

      circles.emplace(rnd.nextInt(int(1e9)), c1);
      circles.emplace(rnd.nextInt(int(1e9)), c2);
    }
  }

  void ShortRailways() {
    int current = 0;
    while (current < N) {
      int len = rnd.nextInt(1, 4);
      if (current + len <= N) {
        if (len > 1) {
          M += 1;
          U.emplace_back(current);
          V.emplace_back((current + len) % N);
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

    while (U.size() < M) {
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
        U.emplace_back(comp[u]);
        V.emplace_back(comp[v]);

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

      if (U.size() < M) {
        U.emplace_back(comp[0 * sz]);
        V.emplace_back(comp[1 * sz]);
      }
      if (U.size() < M) {
        U.emplace_back(comp[1 * sz]);
        V.emplace_back(comp[2 * sz]);
      }
      if (U.size() < M) {
        U.emplace_back(comp[0 * sz]);
        V.emplace_back(comp[2 * sz]);
      }

      circles.emplace(c1);
      circles.emplace(c2);
      circles.emplace(c3);
    }
  }

  void FocusPoints(int num) {
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
          U.emplace_back(u);
          V.emplace_back(between[j]);
        }
      }
      for (int j = piv; j < (int) between.size(); j++) {
        if (min(abs(v - between[j]), N - abs(v - between[j])) > 1) {
          M += 1;
          U.emplace_back(v);
          V.emplace_back(between[j]);
        }
      }
    }
  }
};
