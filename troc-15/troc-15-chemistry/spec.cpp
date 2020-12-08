#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 200000;
const int MAXM = 200000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, M, T;
  vector<int> X, Y, Z;
  int K;
  vector<int> S;

  int ans;

  void InputFormat() {
    LINE(N, M, T);
    LINES(X, Y, Z) % SIZE(M);
    LINE(K);
    LINE(S % SIZE(K));
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(3 <= N && N <= MAXN);
    CONS(1 <= M && M <= MAXM);
    CONS(eachElementBetween(X, 1, N));
    CONS(eachElementBetween(Y, 1, N));
    CONS(eachElementBetween(Z, 1, N));
    CONS(different(X, Y, Z));
    CONS(noCyclic(N, X, Y, Z));
    CONS(differentResults(X, Y, Z));
    CONS(1 <= K && K <= N);
    CONS(eachElementBetween(S, 1, N));
    CONS(distinct(S));
  }

  void Subtask1() {
    Points(100);
  }

 private:
  bool eachElementBetween(const vector<int> &a, int lo, int hi) {
    return all_of(a.begin(), a.end(), [lo, hi](int x) {
      return lo <= x && x <= hi;
    });
  }

  bool distinct(vector<int> S) {
    sort(S.begin(), S.end());
    return unique(S.begin(), S.end()) == S.end();
  }

  bool different(const vector<int> &X, const vector<int> &Y, const vector<int> &Z) {
    for (int i = 0; i < X.size(); ++i) {
      if (X[i] == Y[i] || X[i] == Z[i] || Y[i] == Z[i]) return false;
    }
    return true;
  }

  bool differentResults(const vector<int> &X, const vector<int> &Y, const vector<int> &Z) {
    map<pair<int, int>, int> reactions;
    for (int i = 0; i < X.size(); ++i) {
      int x = X[i], y = Y[i], z = Z[i];
      if (y < x) swap(x, y);
      if (reactions.find({x, y}) != reactions.end() && reactions[{x, y}] != z) return false;
      reactions[{x, y}] = z;
    }
    return true;
  }

  bool noCyclic(int N, const vector<int> &X, const vector<int> &Y, const vector<int> &Z) {
    vector<int> deg(N);
    vector<vector<int>> edges(N);
    for (int i = 0; i < X.size(); ++i) {
      edges[X[i] - 1].push_back(Z[i] - 1);
      edges[Y[i] - 1].push_back(Z[i] - 1);
      deg[Z[i] - 1] += 2;
    }

    queue<int> q;
    for (int i = 0; i < N; ++i) {
      if (deg[i] == 0) q.push(i);
    }

    while (q.size() > 0) {
      int u = q.front();
      q.pop();

      for (int v: edges[u]) {
        if (--deg[v] == 0) q.push(v);
      }
    }

    return all_of(deg.begin(), deg.end(), [](int u){ return u == 0; });
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "6 3 6",
      "1 2 3",
      "2 4 5",
      "2 5 6",
      "2",
      "2 4",
    });
    Output({
      "2",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "3 1 2",
      "3 1 2",
      "1",
      "2",
    });
    Output({
      "1",
    });
  }

  void SampleTestCase3() {
    Subtasks({1});
    Input({
      "10 1 5",
      "1 2 3",
      "3",
      "7 8 9",
    });
    Output({
      "-1",
    });
  }

  void BeforeTestCase() {
    X.clear(); Y.clear(); Z.clear();
    S.clear();
  }

  void AfterTestCase() {
    M = Z.size();
    K = S.size();

    // renumber
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    rnd.shuffle(perm.begin(), perm.end());
    for (int i = 0; i < M; ++i) {
      X[i] = perm[X[i]];
      Y[i] = perm[Y[i]];
      Z[i] = perm[Z[i]];
    }
    T = perm[T];
    for (int i = 0; i < K; ++i) {
      S[i] = perm[S[i]];
    }
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 5; randomTreeLike(N));
    CASE(N = 5; M = 10; K = 4; randomCase(N, M, K));
    CASE(N = MAXN; M = MAXM; K = MAXN/10; randomCase(N, M, K));
    CASE(N = MAXN/2; M = MAXM; K = MAXN/10; randomCase(N, M, K));
    CASE(N = MAXN; randomTreeLike(N));
    CASE(N = MAXN; randomTreeLike(N));
    CASE(N = MAXN - 1; linear(N));
    CASE(N = MAXN - 1; binaryTree(N));
    CASE(N = (1 << 16) - 1; binaryTree(N));
    CASE(N = MAXN; starLike(N));
    CASE(N = MAXN; chainReactions(N));
    CASE(N = MAXN; chainReactions2(N));
    CASE(N = 69420; chainReactions2(N));
  }

  void randomCase(int N, int M, int K) {
    X.resize(M), Y.resize(M), Z.resize(M);
    for (int i = 0; i < M; ++i) {
      vector<int> v(3);
      do {
        v[0] = rnd.nextInt(N), v[1] = rnd.nextInt(N), v[2] = rnd.nextInt(N);
      } while (v[0] == v[1] || v[0] == v[2] || v[1] == v[2]);

      sort(v.begin(), v.end());
      X[i] = v[0], Y[i] = v[1], Z[i] = v[2];
    }

    S = vector<int>(K);
    iota(S.begin(), S.end(), 0);
    T = rnd.nextInt(N);
  }

  void randomTreeLike(int N) {
    T = 0;
    vector<bool> inDeg(N);
    for (int i = 2; i < N; ++i) {
      int y, z;
      do {
        y = rnd.nextInt(i); z = rnd.nextInt(i);
      } while (y == z);
      if (y < z) swap(y, z);
      X.push_back(i), Y.push_back(y), Z.push_back(z);
      inDeg[z] = true;
    }

    for (int i = 0; i < N; ++i) {
      if (!inDeg[i]) S.push_back(i);
    }
  }

  void linear(int N) {
    assert(N & 1);
    T = 0;
    for (int i = 2; i < N; i += 2) {
      X.push_back(i); Y.push_back(i-1); Z.push_back(i-2);
      S.push_back(i-1);
    }
    S.push_back(N - 1);
  }

  void binaryTree(int N) {
    assert(N & 1);
    T = 0;
    for (int i = 1; i < N; i += 2) {
      X.push_back(i); Y.push_back(i+1); Z.push_back(i/2);
    }
    for (int i = N/2; i < N; ++i) S.push_back(i);
  }

  void starLike(int N) {
    T = 0;
    X.push_back(1); Y.push_back(2); Z.push_back(0);

    X.push_back(3); Y.push_back(4); Z.push_back(1);
    X.push_back(5); Y.push_back(6); Z.push_back(2);
    vector<int> leaves[2] = {{3, 4}, {5, 6}};
    for (int i = 7; i < N; ++i) {
      int l = rnd.nextInt(2);
      X.push_back(leaves[l][rnd.nextInt(leaves[l].size())]);
      Y.push_back(i);
      Z.push_back(l + 1);
      leaves[l].push_back(i);
    }

    for (int i = 3; i < N; ++i) S.push_back(i);
  }

  void chainReactions(int N) {
    T = N - 1;
    for (int i = 2; i < N; ++i) {
      X.push_back(0); Y.push_back(i-1); Z.push_back(i);
    }
    S = {0, 1};
  }

  void chainReactions2(int N) {
    T = N - 1;
    for (int i = 2; i < N; ++i) {
      X.push_back(i - 2); Y.push_back(i - 1); Z.push_back(i);
    }
    S = {0, 1};
  }
};
