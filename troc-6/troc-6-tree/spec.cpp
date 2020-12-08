#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAX_N = 100000;
const int MAX_Q = 100000;
const int MAX_K = 26;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, K;
  vector<int> U, V;
  vector<char> C;
  int Q;
  vector<int> A, B;
  vector<long long> ANS;

  void InputFormat() {
    LINE(N, K);
    LINES(U, V, C) % SIZE(N-1);
    LINE(Q);
    LINES(A, B) % SIZE(Q);
  }

  void OutputFormat() {
    LINES(ANS) % SIZE(Q);
  }

  void Constraints() {
    CONS(2 <= N && N <= MAX_N);
    CONS(1 <= K && K <= MAX_K);

    CONS(eachElementsBetween(U, 1, N));
    CONS(eachElementsBetween(V, 1, N));
    CONS(eachCharactersBetween(C, 'a', 'a' + K - 1));
    CONS(isConnected(N, U, V));

    CONS(1 <= Q && Q <= MAX_Q);

    CONS(eachElementsBetween(A, 1, N));
    CONS(eachElementsBetween(B, 1, N));
    CONS(eachElementsDifferent(A, B));
  }

  void Subtask1() {
  }

 private:
  bool eachElementsBetween(vector<int> v, int lo, int hi) {
    return all_of(v.begin(), v.end(), [&](int x) {
      return lo <= x && x <= hi;
    });
  }

  bool eachCharactersBetween(vector<char> v, int lo, int hi) {
    return all_of(v.begin(), v.end(), [&](char x) {
      return lo <= x && x <= hi;
    });
  }

  bool eachElementsDifferent(vector<int> u, vector<int> v) {
    for (int i = 0 ; i < u.size() ; i++) {
      if (u[i] == v[i]) {
        return false;
      }
    }

    return true;
  }

  bool isConnected(int n, vector<int> u, vector<int> v) {
    int pset[n+1];
    iota(pset, pset + n + 1, 0);

    function<int(int)> finds = [&](int x) {
      return pset[x] == x ? x : pset[x] = finds(pset[x]);
    };
    function<void(int, int)> join = [&](int u, int v) {
      u = finds(u);
      v = finds(v);
      pset[u] = v;
    };

    for (int i = 0 ; i < u.size() ; i++) {
      join(u[i], v[i]);
    }

    for (int i = 1 ; i <= n ; i++) {
      if (finds(i) != finds(1)) {
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
      "7 3",
      "1 2 a",
      "2 3 c",
      "3 4 b",
      "3 5 b",
      "6 5 b",
      "7 6 a",
      "4",
      "1 3",
      "1 4",
      "6 1",
      "7 1"
    });
    Output({
      "0",
      "1",
      "2",
      "4"
    });
  }

  void BeforeTestCase() {
    U.clear();
    V.clear();
    C.clear();

    A.clear();
    B.clear();
  }

  void AfterTestCase() {
    renumber();
    reorder();
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 2, K = 1,
         U = {1}, V = {2}, C = {'a'},
         Q = 1,
         A = {1}, B = {2});
    CASE(N = MAX_N, K = MAX_K,
         _randomTreeWithChainBase(N, N / 2),
         randomEdgeColor(N, K),
         Q = MAX_Q,
         randomQueries(N, Q));
    CASE(N = MAX_N, K = 1,
         _randomTreeWithChainBase(N, N / 2),
         randomEdgeColor(N, K),
         Q = MAX_Q,
         randomQueries(N, Q));
    
    // easy random tree
    for (int i = 0 ; i < 2 ; i++) {
      for(auto treeGenerator : {chainTree, randomTree, randomTreeWithChainBase}) {
        for (auto edgeGenerator : {randomEdgeColor, depthEdgeColor}) {
          CASE(N = rnd.nextInt(MAX_N / 2, MAX_N), K = rnd.nextInt(MAX_K / 2, MAX_K),
               treeGenerator(N),
               edgeGenerator(N, K),
               Q = rnd.nextInt(MAX_Q / 2, MAX_Q),
               randomQueries(N, Q));
          
          CASE(N = rnd.nextInt(MAX_N / 2, MAX_N), K = rnd.nextInt(1, MAX_K),
               treeGenerator(N),
               edgeGenerator(N, K),
               Q = rnd.nextInt(MAX_Q / 2, MAX_Q),
               randomQueries(N, Q));
        }
      }
    }

    // star tree, don't need many
    for (auto edgeGenerator : {randomEdgeColor, depthEdgeColor}) {
      // likely 0
      CASE(N = rnd.nextInt(MAX_N / 2, MAX_N), K = rnd.nextInt(1, 10),
           starTree(N), edgeGenerator(N, K),
           Q = rnd.nextInt(MAX_Q / 2, MAX_Q), randomQueries(N, Q));

      for (int i = 0 ; i < 2 ; i++) {
        CASE(N = rnd.nextInt(MAX_N / 2, MAX_N), K = i+1,
             starTree(N), edgeGenerator(N, K),
             Q = rnd.nextInt(MAX_Q / 2, MAX_Q), randomQueries(N, Q));
      }
    }

    // full binary tree
    for (auto edgeGenerator : {randomEdgeColor, depthEdgeColor}) {
      for (int i = 0 ; i < 2 ; i++) {
        CASE(N = rnd.nextInt(MAX_N / 2, MAX_N), K = rnd.nextInt(1, MAX_K),
             fullBinaryTree(N), edgeGenerator(N, K),
             Q = rnd.nextInt(MAX_Q / 2, MAX_Q), randomQueries(N, Q));

        CASE(N = rnd.nextInt(MAX_N / 2, MAX_N), K = rnd.nextInt(1, MAX_K / 2),
             fullBinaryTree(N), edgeGenerator(N, K),
             Q = rnd.nextInt(MAX_Q / 2, MAX_Q), randomQueries(N, Q));
        
        CASE(N = rnd.nextInt(MAX_N / 2, MAX_N), K = rnd.nextInt(MAX_K / 2, MAX_K),
             fullBinaryTree(N), edgeGenerator(N, K),
             Q = rnd.nextInt(MAX_Q / 2, MAX_Q), randomQueries(N, Q));
      }
    }
  }

 private:
  // tree generators

  function<void(int)> chainTree = [&](int n) {
    for (int i = 2 ; i <= n ; i++) {
      U.push_back(i);
      V.push_back(i-1);
    }
  };

  function<void(int)> randomTree = [&](int n) {
    for (int i = 2 ; i <= n ; i++) {
      U.push_back(i);
      V.push_back(rnd.nextInt(1, i-1));
    }
  };

  function<void(int)> fullBinaryTree = [&](int n) {
    for (int i = 2; i <= n; i++) {
      U.push_back(i);
      V.push_back(i / 2);
    }
  };

  function<void(int)> starTree = [&](int n) {
    for (int i = 2 ; i <= n ; i++) {
      U.push_back(i);
      V.push_back(1);
    }
  };

  function<void(int, int)> _randomTreeWithChainBase = [&](int n, int base) {
    if (base == -1) base = rnd.nextInt(1, n);
    chainTree(base);
    for (int i = base+1 ; i <= n ; i++) {
      U.push_back(i);
      V.push_back(rnd.nextInt(1, i-1));
    }
  };

  function<void(int)> randomTreeWithChainBase = [&](int n) {
    _randomTreeWithChainBase(n, -1);
  };

  // edge generators
  function<void(int, int)> randomEdgeColor = [&](int n, int k) {
    for (int i = 0 ; i < n-1 ; i++) {
      C.push_back(rnd.nextInt('a', 'a' + k - 1));
    }
  };
  function<void(int, int)> depthEdgeColor = [&](int n, int k) {
    vector<int> adj[n+1];
    vector<int> depth(n+1, -1);

    for (int i = 0 ; i < U.size() ; i++) {
      adj[U[i]].push_back(V[i]);
      adj[V[i]].push_back(U[i]);
    }

    function<void(int)> dfs = [&](int x) {
      for (int nex : adj[x]) {
        if (depth[nex] != -1) continue;
        depth[nex] = depth[x] + 1;
        dfs(nex);
      }
    };

    depth[1] = 0;
    dfs(1);

    for (int i = 0 ; i < n-1 ; i++) {
      int d = min(depth[U[i]], depth[V[i]]);
      C.push_back('a' + (d % k));
    }
  };

  // query generator

  void randomQueries(int n, int q) {
    for (int i = 0 ; i < q ; i++) {
      int a = rnd.nextInt(1, n);
      int b = rnd.nextInt(1, n);

      while (a == b) {
        a = rnd.nextInt(1, n);
        b = rnd.nextInt(1, n);
      }

      A.push_back(a);
      B.push_back(b);
    }
  }

  // post-processing

  void renumber() {
    renumberNodes();
    renumberAlphabets();
  }

  void reorder() {
    reorderEdges();
    reorderQueries();
  }

  void renumberNodes() {
    vector<int> order(N+1);
    iota(order.begin(), order.end(), 0);
    rnd.shuffle(order.begin()+1, order.end());

    for (int &x : U) x = order[x];
    for (int &x : V) x = order[x];
    for (int &x : A) x = order[x];
    for (int &x : B) x = order[x];
  }

  void renumberAlphabets() {
    vector<int> order(K);
    iota(order.begin(), order.end(), 0);
    rnd.shuffle(order.begin(), order.end());

    for (char &ch : C) ch = 'a' + order[ch - 'a'];
  }

  void reorderEdges() {
    vector<int> order(N-1);
    iota(order.begin(), order.end(), 0);
    rnd.shuffle(order.begin(), order.end());

    vector<int> copyU = U, copyV = V;
    vector<char> copyC = C;

    for (int i = 0 ; i < order.size() ; i++) {
      U[i] = copyU[order[i]];
      V[i] = copyV[order[i]];
      C[i] = copyC[order[i]];

      if (rnd.nextInt(2)) swap(U[i], V[i]);
    }
  }

  void reorderQueries() {
    vector<int> order(Q);
    iota(order.begin(), order.end(), 0);
    rnd.shuffle(order.begin(), order.end());

    vector<int> copyA = A, copyB = B;

    for (int i = 0 ; i < order.size() ; i++) {
      A[i] = copyA[order[i]];
      B[i] = copyB[order[i]];

      if (rnd.nextInt(2)) swap(A[i], B[i]);
    }
  }
};
