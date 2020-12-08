#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 2000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  vector<int> P;
  int S, T;

  int ans;

  void InputFormat() {
    LINE(N);
    LINE(P % SIZE(N-1));
    LINE(S, T);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(64);
  }

  void Constraints() {
    CONS(2 <= N && N <= MAXN);
    CONS(isTree(P));
    CONS(1 <= S && S <= N);
    CONS(1 <= T && T <= N);
    CONS(S != T);
  }

  void Subtask1() {
    Points(100);
  }

 private:
  bool isTree(const vector<int> &P) {
    for (int i = 0; i < P.size(); ++i) {
      if (P[i] <= 0 || P[i] > i+1) return false;
    }

    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "5",
      "1 1 2 2",
      "5 3",
    });
    Output({
      "1",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "5",
      "1 2 2 2",
      "3 5",
    });
    Output({
      "2",
    });
  }

  void SampleTestCase3() {
    Subtasks({1});
    Input({
      "5",
      "1 2 3 4",
      "1 4",
    });
    Output({
      "6",
    });
  }

  void BeforeTestCase() {
    P.clear();
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 2; P = {1}; S = 1; T = 2);
    CASE(N = 2; P = {1}; S = 2; T = 1);
    CASE(N = 4; P = {1, 2, 2}; S = 1; T = 2);
    CASE(N = 4; P = {1, 2, 2}; S = 4; T = 3);
    CASE(N = 7; P = {1, 2, 3, 4, 4, 4}; S = 1; T = 2);
    CASE(N = 6; P = {1, 1, 1, 1, 1}; S = 2; T = 3);

    CASE(N = MAXN; pathGraph(N); S = 1; T = 2);
    CASE(N = rnd.nextInt(1700, MAXN); pathGraph(N); S = N-1; T = N);
    CASE(N = rnd.nextInt(1700, MAXN); pathGraph(N); S = rnd.nextInt(1, N/2); T = rnd.nextInt(N/2, N));

    CASE(N = MAXN; broomGraph(N); S = 1; T = N);
    CASE(N = MAXN; broomGraph(N); S = 1; T = 2);
    CASE(N = rnd.nextInt(1700, MAXN); broomGraph(N); S = rnd.nextInt(N/2 + 1, N-1); T = rnd.nextInt(S+1, N));
    CASE(N = MAXN; broomGraph(N, N/2 + 1); S = 1; T = 2);
    CASE(N = MAXN; broomGraph(N, N/4 * 3); S = rnd.nextInt(1, N-1); T = rnd.nextInt(S+1, N));

    CASE(N = MAXN; caterpillarGraph(N); S = rnd.nextInt(1, N-1); T = rnd.nextInt(S+1, N));
    CASE(N = MAXN; caterpillarGraph(N); S = rnd.nextInt(1, N-1); T = rnd.nextInt(S+1, N); swap(S, T));

    CASE(N = MAXN; pathRandomTree(N); S = rnd.nextInt(N/2 + 1, N); T = rnd.nextInt(1, N));
    CASE(N = MAXN; pathRandomTree(N, N/2 + 2); S = 2; T = 1);
    CASE(N = MAXN; pathRandomTree(N, N/4 * 3); S = rnd.nextInt(1, N-1); T = rnd.nextInt(S+1, N));

    CASE(N = 1023; binaryTree(N); S = 512; T = 1023);
    CASE(N = MAXN; binaryTree(N); S = 1 << (31 - __builtin_clz(N)); T = N);
    CASE(N = MAXN; randomBinaryTree(N));
    CASE(N = MAXN; longBroomGraph(N));
  }

 private:
  void pathGraph(int N) {
    P.resize(N-1);
    iota(P.begin(), P.end(), 1);
  }

  void broomGraph(int N, int height=-1) {
    if (height == -1) height = N/2;
    for (int i = 1; i < height; ++i) {
      P.push_back(i);
    }
    for (int i = height; i < N; ++i) {
      P.push_back(height);
    }
  }

  void caterpillarGraph(int N) {
    int body = N - N/4;
    for (int i = 1; i < body; ++i) {
      P.push_back(i);
    }

    // feet
    for (int i = body; i < N; ++i) {
      P.push_back(rnd.nextInt(1, P.size() + 1));
    }
  }

  void pathRandomTree(int N, int pathLength=-1) {
    if (pathLength == -1) pathLength = N/2;
    for (int i = 1; i < pathLength; ++i) {
      P.push_back(i);
    }
    for (int i = pathLength; i < N; ++i) {
      P.push_back(rnd.nextInt(pathLength, i));
    }
  }

  void binaryTree(int N) {
    for (int i = 1; i < N; ++i) {
      P.push_back(i+1>>1);
    }
  }

  void randomBinaryTree(int N) {
    vector<int> degree(N+1, 0);
    P.push_back(1); P.push_back(1);
    degree[1] = 2;
    S = 2; T = 3;

    for (int i = 3; i < N; ++i) {
      int p;
      do {
        p = rnd.nextInt(2, i);
      } while (degree[p] == 2);

      P.push_back(p);
      ++degree[p];
      if (S == p) S = i+1;
      if (T == p) T = i+1;
    }
  }

  void longBroomGraph(int N, int deg=10) {
    assert(N >= deg*2);
    for (int i = 1; i < deg; ++i) {
      P.push_back(i);
    }

    for (int i = 0; i < deg; ++i) {
      P.push_back(deg);
    }

    for (int i = deg*2; i < N; ++i) {
      P.push_back(i - deg + 1);
    }
  }
};
