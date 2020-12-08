#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 100000;
const int MAXQ = 100000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, Q;
  vector<int> U;
  vector<char> A, B;

  vector<int> op;
  vector<vector<string>> queries;

  vector<int> ans;

  void InputFormat() {
    LINE(N, Q);
    LINES(U, A, B) % SIZE(N-1);

    LINES(op, queries) % SIZE(Q);
  }

  int query_count;
  void BeforeOutputFormat() {
    query_count = 0;
    for (int i = 0; i < Q; ++i) {
      if (op[i] == 3) ++query_count;
    }
  }

  void OutputFormat() {
      LINES(ans) % SIZE(query_count);
  }

  void GradingConfig() {
      TimeLimit(1);
      MemoryLimit(64);
  }

  void Constraints() {
      CONS(1 <= N && N <= MAXN);
      CONS(1 <= Q && Q <= MAXQ);
      CONS(isTree(U));
      CONS(isElementOf(A, {'a', 'A'}));
      CONS(isElementOf(B, {'b', 'B'}));
      CONS(isElementOf(op, {1, 2, 3}));
      CONS(validQueries(queries));
  }

  void Subtask1() {
      Points(100);
  }

 private:
  bool isTree(const vector<int> &U) {
    for (int i = 0; i < N-1; ++i) {
      if (U[i] < 1 || U[i] > i+1) return false;
    }

    return true;
  }

  template<typename T>
  bool isElementOf(const vector<T> &A, const vector<T> &S) {
    for (const T &a: A) {
      bool found = false;
      for (const T &s: S) {
        if (a == s) {
          found = true;
          break;
        }
      }

      if (!found) return false;
    }
    return true;
  }

  int parseInt(const string &s) {
    try {
      return stoi(s);
    } catch(exception &e) {
      return -1;
    }
  }

  bool validQueries(const vector<vector<string>> &queries) {
    for (int i = 0; i < Q; ++i) {
      const vector<string> &query = queries[i];
      if (op[i] == 1) {
        if (query.size() != 2) return false;

        int r = parseInt(query[0]);
        if (r < 1 || r > N-1) return false;

        const string &x = query[1];
        if (x != "A" && x != "B") return false;

      } else if (op[i] == 2) {
        if (query.size() != 2) return false;

        int u = parseInt(query[0]);
        if (u < 1 || u > N) return false;

        int v = parseInt(query[1]);
        if (v < 1 || v > N) return false;

      } else if (op[i] == 3) {
        if (query.size() != 4) return false;

        int u = parseInt(query[0]);
        if (u < 1 || u > N) return false;

        const string &x = query[1];
        if (x != "A" && x != "B") return false;

        int v = parseInt(query[2]);
        if (v < 1 || v > N) return false;

        const string &y = query[3];
        if (y != "A" && y != "B") return false;
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
      "6 4",
      "1 A b",
      "2 A b",
      "2 A B",
      "1 a b",
      "5 a B",
      "3 4 B 1 B",
      "2 4 5",
      "1 4 B",
      "3 3 B 6 A",
    });
    Output({
      "6",
      "13",
    });
  }

  void BeforeTestCase() {
    U.clear(); A.clear(); B.clear();
    op.clear(); queries.clear();
  }

  void AfterTestCase() {
    for (int &u: U) ++u;
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 10; Q = 10; randomTree(N); randomLanes(N); randomQueries(N, Q));
    CASE(N = rnd.nextInt(MAXN); Q = rnd.nextInt(MAXQ); randomTree(N); randomLanes(N); randomQueries(N, Q));

    CASE(N = MAXN; Q = MAXQ; randomTree(N); randomLanes(N); randomQueries(N, Q));
    CASE(N = MAXN; Q = MAXQ; lineGraph(N); randomLanes(N); randomQueries(N, Q));
    CASE(N = MAXN; Q = MAXQ; starGraph(N); randomLanes(N); randomQueries(N, Q));
    CASE(N = MAXN; Q = MAXQ; broomGraph(N); randomLanes(N); randomQueries(N, Q));
    CASE(N = MAXN; Q = MAXQ; centipedeGraph(N); randomLanes(N); randomQueries(N, Q));

    CASE(N = MAXN; Q = MAXQ; randomTree(N); allBrokenLanes(N); randomQueries(N, Q));
    CASE(N = MAXN; Q = MAXQ; randomTree(N); allGoodLanes(N); randomQueries(N, Q));
    CASE(N = MAXN; Q = MAXQ; randomTree(N); alternatingLanes(N); randomQueries(N, Q));
    CASE(N = MAXN; Q = MAXQ; randomTree(N); allSymmetryLanes(N); randomQueries(N, Q));
    CASE(N = MAXN; Q = MAXQ; randomTree(N); fewAlternateLanes(N); randomQueries(N, Q));
    CASE(N = MAXN; Q = MAXQ; randomTree(N); fewSymmetryLanes(N); randomQueries(N, Q));

    CASE(N = MAXN; Q = MAXQ; randomTree(N); randomLanes(N); noUpdate(N, Q));
    CASE(N = MAXN; Q = MAXQ; randomTree(N); randomLanes(N); lotOfQuery1(N, Q));
    CASE(N = MAXN; Q = MAXQ; randomTree(N); randomLanes(N); lotOfQuery2(N, Q));

    CASE(N = MAXN; Q = MAXQ; lineGraph(N); alternatingLanes(N); noUpdate(N, Q));
    CASE(N = MAXN; Q = MAXQ; starGraph(N); allGoodLanes(N); randomQueries(N, Q));
  }

 private:

  void randomTree(int N) {
    for (int i = 1; i < N; ++i) {
      U.push_back(rnd.nextInt(i));
    }
  }

  void lineGraph(int N) {
    for (int i = 1; i < N; ++i) {
      U.push_back(i-1);
    }
  }

  void starGraph(int N) {
    for (int i = 1; i < N; ++i) {
      U.push_back(0);
    }
  }

  void broomGraph(int N) {
    for (int i = 1; i < N/2; ++i) {
      U.push_back(i-1);
    }

    for (int i = N/2; i < N; ++i) {
      U.push_back(N/2 - 1);
    }
  }

  void centipedeGraph(int N) {
    for (int i = 1; i < N/2; ++i) {
      U.push_back(i-1);
    }

    for (int i = N/2; i < N; ++i) {
      U.push_back(rnd.nextInt(i));
    }
  }

  void randomLanes(int N) {
    char s[2] = {'a', 'A'};
    char t[2] = {'b', 'B'};
    for (int i = 1; i < N; ++i) {
      A.push_back(s[rnd.nextInt(2)]);
      B.push_back(t[rnd.nextInt(2)]);
    }
  }

  void allBrokenLanes(int N) {
    for (int i = 1; i < N; ++i) {
      A.push_back('a');
      B.push_back('b');
    }
  }

  void allGoodLanes(int N) {
    for (int i = 1; i < N; ++i) {
      A.push_back('A');
      B.push_back('B');
    }
  }

  void alternatingLanes(int N) {
    for (int i = 1; i < N; ++i) {
      if (i & 1) {
        A.push_back('a');
        B.push_back('B');
      } else {
        A.push_back('A');
        B.push_back('b');
      }
    }
  }

  void allSymmetryLanes(int N) {
    for (int i = 1; i < N; ++i) {
      if (rnd.nextInt(2)) {
        A.push_back('a');
        B.push_back('B');
      } else {
        A.push_back('A');
        B.push_back('B');
      }
    }
  }

  void fewSymmetryLanes(int N) {
    alternatingLanes(N);
    for (int i = 0; i < 10; ++i) {
      int idx = rnd.nextInt(N-1);

      if (rnd.nextInt(2)) {
        A[idx] = 'a';
        B[idx] = 'b';
      } else {
        A[idx] = 'A';
        B[idx] = 'B';
      }
    }
  }

  void fewAlternateLanes(int N) {
    allSymmetryLanes(N);
    for (int i = 0; i < 10; ++i) {
      int idx = rnd.nextInt(N-1);

      if (rnd.nextInt(2)) {
        A[idx] = 'a';
        B[idx] = 'B';
      } else {
        A[idx] = 'A';
        B[idx] = 'b';
      }
    }
  }

  void query1(int N) {
    op.push_back(1);
    string s[2] = {"A", "B"};
    queries.push_back({
      to_string(rnd.nextInt(1, N-1)),
      s[rnd.nextInt(2)],
    });
  }

  void query2(int N) {
    op.push_back(2);
    queries.push_back({
      to_string(rnd.nextInt(1, N)),
      to_string(rnd.nextInt(1, N)),
    });
  }

  void query3(int N) {
    op.push_back(3);
    string s[2] = {"A", "B"};
    queries.push_back({
      to_string(rnd.nextInt(1, N)),
      s[rnd.nextInt(2)],
      to_string(rnd.nextInt(1, N)),
      s[rnd.nextInt(2)],
    });
  }

  void randomQueries(int N, int Q) {
    for (int i = 0; i < Q-1; ++i) {
      int q = rnd.nextInt(3);
      if (q == 0) query1(N);
      else if (q == 1) query2(N);
      else if (q == 2) query3(N);
    }
    query3(N);
  }

  void noUpdate(int N, int Q) {
    for (int i = 0; i < Q; ++i) query3(N);
  }

  void lotOfQuery1(int N, int Q) {
    for (int i = 0; i < Q-1; ++i) {
      if (i % 1000 == 999) {
        if (rnd.nextInt(2)) query2(N);
        else query3(N);
      } else {
        query1(N);
      }
    }
    query3(N);
  }

  void lotOfQuery2(int N, int Q) {
    for (int i = 0; i < Q-1; ++i) {
      if (i % 1000 == 999) {
        if (rnd.nextInt(2)) query1(N);
        else query3(N);
      } else {
        query2(N);
      }
    }
    query3(N);
  }
};
