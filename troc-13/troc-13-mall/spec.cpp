#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 100000;
const int MAXV = 1000000000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int H, N;
  vector<int> D;
  int S;
  vector<int> A, B, T, Q;
  int X;

  vector<long long> ans;

  void InputFormat() {
    LINE(H, N);
    LINE(D % SIZE(N));
    LINE(S);
    LINES(A, B, T, Q) % SIZE(N);
    LINE(X);
  }

  void OutputFormat() {
    LINES(ans) % SIZE(N);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(128);
  }

  void Constraints() {
    CONS(1 <= N && N <= H && H <= MAXV);
    CONS(1 <= X && X <= N && N <= MAXN);
    CONS(Increasing(D));

    CONS(EachElementLessEqual(vector<int>(N, 1), A));
    CONS(EachElementLessEqual(A, D));
    CONS(EachElementLessEqual(D, B));
    CONS(EachElementLessEqual(B, vector<int>(N, H)));

    CONS(1 <= S && S <= MAXV);
    CONS(EachElementBetween(T, 1, MAXV));
    CONS(EachElementBetween(Q, 0, MAXV));
  }

  void Subtask1() {
      Points(100);
  }

 private:
  bool Increasing(vector<int> a) {
    for (int i = 0; i + 1 < (int) a.size(); i++) {
      if (!(a[i] < a[i + 1])) return false;
    }
    return true;
  }

  bool EachElementBetween(vector<int> a, int lo, int hi) {
    for (int i = 0; i < (int) a.size(); i++) {
      if (!(lo <= a[i] && a[i] <= hi)) return false;
    }
    return true;
  }

  bool EachElementLessEqual(vector<int> a, vector<int> b) {
    assert(a.size() == b.size());
    for (int i = 0; i < (int) a.size(); i++) {
      if (!(a[i] <= b[i])) return false;
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "20 5",
      "1 2 5 10 19",
      "6",
      "1 7 1 1",
      "1 8 3 2",
      "5 5 4 6",
      "10 15 3 0",
      "18 20 1 1",
      "2",
    });
    Output({
      "5",
      "0",
      "10",
      "30",
      "69"
    });
  }

  void BeforeTestCase() {
    D.clear();
    A.clear();
    B.clear();
    T.clear();
    Q.clear();
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = MAXN; H = MAXV; RandomCase(MAXV, MAXV, MAXV); D[0] = A[0] = 1; D[N - 1] = B[N - 1] = H; X = N);

    CASE(N = MAXN; H = rnd.nextInt((MAXV / 10) * 9, MAXV); RandomCase(90, 90, 100));
    CASE(N = MAXN; H = rnd.nextInt((MAXV / 10) * 9, MAXV); RandomCase(900, 900, 1000));
    CASE(N = MAXN; H = rnd.nextInt((MAXV / 10) * 9, MAXV); RandomCase(90000, 90000, 100000));
    CASE(N = MAXN; H = rnd.nextInt((MAXV / 10) * 9, MAXV); RandomCase(9000000, 9000000, 10000000));
    CASE(N = MAXN; H = rnd.nextInt((MAXV / 10) * 9, MAXV); RandomCase(900000000, 900000000, 1000000000));

    CASE(N = MAXN; H = N; RandomCase(0, 1, 100));
    CASE(N = MAXN; H = N; RandomCase(0, 1, 1000));
    CASE(N = MAXN; H = N; RandomCase(0, 1, 100000));
    CASE(N = MAXN; H = N; RandomCase(0, 1, 10000000));
    CASE(N = MAXN; H = N; RandomCase(0, 1, 1000000000));

    CASE(N = MAXN; H = rnd.nextInt((MAXV / 10) * 9, MAXV); RandomCase(0, 1, 100));
    CASE(N = MAXN; H = rnd.nextInt((MAXV / 10) * 9, MAXV); RandomCase(0, 1, 1000));
    CASE(N = MAXN; H = rnd.nextInt((MAXV / 10) * 9, MAXV); RandomCase(0, 1, 100000));
    CASE(N = MAXN; H = rnd.nextInt((MAXV / 10) * 9, MAXV); RandomCase(0, 1, 10000000));
    CASE(N = MAXN; H = rnd.nextInt((MAXV / 10) * 9, MAXV); RandomCase(0, 1, 1000000000));

    CASE(N = rnd.nextInt((MAXN / 10) * 9, MAXN); H = rnd.nextInt(N + 5e1, N + 1e2); RandomCase());
    CASE(N = rnd.nextInt((MAXN / 10) * 9, MAXN); H = rnd.nextInt(N + 5e5, N + 1e6); RandomCase());
    CASE(N = rnd.nextInt((MAXN / 10) * 9, MAXN); H = rnd.nextInt(N + 5e7, N + 1e8); RandomCase());
    CASE(N = rnd.nextInt((MAXN / 10) * 9, MAXN); H = rnd.nextInt(N + 5e8, MAXV); RandomCase());
  }
  
 private:
  void RandomCase(const int MINB = 0, const int MINA = 1, const int MAX = MAXV) {
    assert(MINB >= 0);
    assert(MINA >= 1);
    assert(MAX >= MINA);
    assert(MAX >= MINB);
    assert(MAXV >= MAX);

    const vector<int> Z(N, MINB);
    const vector<int> L(N, MINA);
    const vector<int> V(N, MAX);

    S = rnd.nextInt(MINA, MAX);
    T = RandomEachElementBetween(L, V);
    Q = RandomEachElementBetween(Z, V);

    const vector<int> O(N, 1);
    const vector<int> P(N, H);

    D = RandomIncreasing(H, N); 
    A = RandomEachElementBetween(O, D);
    B = RandomEachElementBetween(D, P);
    X = rnd.nextInt(1, N);
  }

  vector<int> RandomIncreasing(int h, int n) {
    assert(n <= h);
    set<int> s;
    while (s.size() < n) {
      s.emplace(rnd.nextInt(1, h));
    }
    return vector<int>(begin(s), end(s));
  }

  vector<int> RandomEachElementBetween(vector<int> a, vector<int> b) {
    assert(a.size() == N);
    assert(b.size() == N);
    vector<int> res(N);
    for (int i = 0; i < N; i++) {
      res[i] = rnd.nextInt(a[i], b[i]);
    }
    return res;
  }
};
