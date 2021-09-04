#include <bits/stdc++.h>

#include <tcframe/spec.hpp>
#include <tcrand/tree.hpp>

using namespace std;
using namespace tcrand;
using namespace tcframe;

const int MAXN = 1000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  vector<int> P;

  int ans;

  void InputFormat() {
    LINE(N);
    LINE(P % SIZE(N - 1));
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(4);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(2 <= N && N <= MAXN);
    CONS(isTree(P));
  }

  void Subtask1() {
    Points(100);
  }

 private:
  bool isTree(const vector<int> &P) {
    for (int i = 0; i < P.size(); ++i) {
      if (!(1 <= P[i] && P[i] < (i + 2))) {
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
        "3",
        "1 1",
    });
    Output({
        "100",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
        "5",
        "1 2 2 3",
    });
    Output({
        "1584",
    });
  }

  void SampleTestCase3() {
    Subtasks({1});
    Input({
        "9",
        "1 2 1 3 2 4 3 2",
    });
    Output({
        "92408",
    });
  }

  void BeforeTestCase() {
    N = ans = 0;
    P.clear();
  }

  void AfterTestCase() {
    shuffleTree();
    for (int i = 0; i < N - 1; i++) {
      P[i] += 1;
    }
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 2; pathGraph(N));
    CASE(N = 4; pathGraph(N));
    CASE(N = 4; starGraph(N));

    CASE(N = 7; randomTree(N));
    CASE(N = 14; randomTree(N));
    CASE(N = 20; randomTree(N));

    CASE(N = MAXN; pathGraph(N));
    CASE(N = MAXN; starGraph(N));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN); pathGraph(N));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN); starGraph(N));

    CASE(N = MAXN; broomGraph(N));
    CASE(N = MAXN; broomGraph(N, N / 4 * 3));

    CASE(N = MAXN; caterpillarGraph(N));

    CASE(N = MAXN; pathRandomTree(N));
    CASE(N = MAXN; pathRandomTree(N, N / 2 + 2));
    CASE(N = MAXN; pathRandomTree(N, N / 4 * 3));

    CASE(N = 511; binaryTree(N));
    CASE(N = MAXN; binaryTree(N));
    CASE(N = MAXN; randomBinaryTree(N));
    CASE(N = MAXN; longBroomGraph(N));

    CASE(N = rnd.nextInt(MAXN - 50, MAXN); makeTreeDep(100));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN); makeTreeDep(250));

    CASE(N = rnd.nextInt(MAXN - 50, MAXN); makeTreeLeaf(100));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN); makeTreeLeaf(250));

    CASE(N = rnd.nextInt(MAXN - 50, MAXN); makeTreeDeg(sqrt(N) - 5, sqrt(N) + 5));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN); makeTreeDeg(sqrt(N) - 5, sqrt(N) + 10));
    CASE(N = rnd.nextInt(MAXN - 50, MAXN); makeTreeDeg(sqrt(N) - 10, sqrt(N) + 15));

    CASE(N = MAXN; randomTree(N));
    CASE(N = MAXN; randomTree(N));
    CASE(N = MAXN; randomTree(N));
  }

 private:
  void pathGraph(int N) {
    P.assign(N - 1, 0);
    iota(P.begin(), P.end(), 0);
  }

  void starGraph(int N) {
    P.assign(N - 1, 0);
  }

  void broomGraph(int N, int height = -1) {
    if (height == -1) height = N / 2;
    for (int i = 1; i < height; ++i) {
      P.push_back(i - 1);
    }
    for (int i = height; i < N; ++i) {
      P.push_back(height - 1);
    }
  }

  void caterpillarGraph(int N) {
    int body = N - N / 4;
    for (int i = 1; i < body; ++i) {
      P.push_back(i - 1);
    }

    // feet
    for (int i = body; i < N; ++i) {
      P.push_back(rnd.nextInt(0, P.size()));
    }
  }

  void pathRandomTree(int N, int pathLength = -1) {
    if (pathLength == -1) pathLength = N / 2;
    for (int i = 1; i < pathLength; ++i) {
      P.push_back(i - 1);
    }
    for (int i = pathLength; i < N; ++i) {
      P.push_back(rnd.nextInt(pathLength - 1, i - 1));
    }
  }

  void binaryTree(int N) {
    for (int i = 1; i < N; ++i) {
      P.push_back(((i + 1) >> 1) - 1);
    }
  }

  void randomBinaryTree(int N) {
    vector<int> degree(N + 1, 0);
    P.push_back(0);
    P.push_back(0);
    degree[0] = 2;

    for (int i = 3; i < N; ++i) {
      int p;
      do {
        p = rnd.nextInt(0, i - 1);
      } while (degree[p] == 2);

      P.push_back(p);
      ++degree[p];
    }
  }

  void longBroomGraph(int N, int deg = 10) {
    assert(N >= deg * 2);
    for (int i = 1; i < deg; ++i) {
      P.push_back(i - 1);
    }

    for (int i = 0; i < deg; ++i) {
      P.push_back(deg - 1);
    }

    for (int i = deg * 2; i < N; ++i) {
      P.push_back(i - deg);
    }
  }

  void makeTreeLeaf(int leafCount) {
    vector<int> U, V;
    tie(U, V) = TreeRandomizer().node_count(N).index_base(0).root(rnd.nextInt(0, N - 1)).leaf_count(leafCount).next().edges();
    P = transformTree(U, V);
    shuffleTree();
  }

  void makeTreeDep(int depth) {
    vector<int> U, V;
    tie(U, V) = TreeRandomizer().node_count(N).index_base(0).root(rnd.nextInt(0, N - 1)).depth(depth).next().edges();
    P = transformTree(U, V);
    shuffleTree();
  }

  void randomTree(int N) {
    vector<int> U, V;
    tie(U, V) = TreeRandomizer().node_count(N).index_base(0).next().edges();
    P = transformTree(U, V);
    shuffleTree();
  }

  void makeTreeDeg(int loDeg, int hiDeg) {
    vector<int> U, V;
    tie(U, V) = TreeRandomizer().node_count(N).index_base(0).root(rnd.nextInt(0, N - 1)).child_count(loDeg, hiDeg).next().edges();
    P = transformTree(U, V);
    shuffleTree();
  }

  vector<int> transformTree(vector<int> U, vector<int> V) {
    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
      adj[U[i]].push_back(V[i]);
      adj[V[i]].push_back(U[i]);
    }
    vector<int> ord;
    vector<int> que;
    vector<int> vis(N);
    int root = rnd.nextInt(N);
    vis[root] = 1;
    que.push_back(root);
    while (!que.empty()) {
      int r = rnd.nextInt(0, int(que.size()) - 1);
      int u = que[r];
      ord.push_back(u);
      swap(que[r], que.back());
      que.pop_back();
      for (auto v : adj[u]) {
        if (!vis[v]) {
          vis[v] = 1;
          que.push_back(v);
        }
      }
    }
    vector<int> pos(N);
    for (int i = 0; i < N; i++) {
      pos[ord[i]] = i;
    }
    vector<int> p(N - 1);
    for (int i = 0; i < N - 1; i++) {
      p[max(pos[U[i]], pos[V[i]]) - 1] = min(pos[U[i]], pos[V[i]]);
    }
    return p;
  }

  void shuffleTree() {
    vector<int> U, V;
    for (int i = 0; i < N - 1; i++) {
      U.push_back(P[i]);
      V.push_back(i + 1);
    }
    P = transformTree(U, V);
  }
};
