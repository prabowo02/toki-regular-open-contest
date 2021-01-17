// WARNING! This spec uses tcrand
// Source : https://github.com/afaji/tcrand
// Please do get the library before compiling, and put it in tcframe/include/tcrand
// in reference to Hocky's troc 14 1F
#include <bits/stdc++.h>
#include <tcrand/tree.hpp>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;
using namespace tcrand;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;

const int MAXN = 200000;
const int MAXQ = 200000;
const int MAXA = 200000;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N, Q;
  vector<int> U, V;
  vector<vector<int>> QUERIES;
  vector<int> ANS;

  void InputFormat() {
    LINE(N);
    // LINE(A % SIZE(N));
    LINES(U, V) % SIZE(N - 1);
    LINE(Q);
    LINES(QUERIES) % SIZE(Q);
  }

  void OutputFormat(){
    LINES(ANS) % SIZE(askCount);
  }

  void GradingConfig() {
    TimeLimit(3);
    MemoryLimit(256);
  }

  int askCount = 0;

  void BeforeOutputFormat(){
    askCount = 0;
    for (int i = 0; i < QUERIES.size(); i++){
      if (QUERIES[i][0] == 2) {
        askCount++;
      }
    }
  }

  void Constraints() {
    CONS((1 <= N) && (N <= MAXN));
    CONS((1 <= Q) && (Q <= MAXQ));
    // CONS(eachElementBetween(A, 0, MAXA));
    CONS(eachElementBetween(U, 1, N));
    CONS(eachElementBetween(V, 1, N));
    CONS(eachQueryValid(QUERIES));
    CONS(isTree(N, U, V));
  }

  void Subtask1(){
    Points(100);
  }


private:
  template <class T> 
  bool eachElementBetween(const vector<T>&V, T lo, T hi){
    for(T x : V) if(x < lo || hi < x) return false;
    return true;
  }
  
  bool validateQuery1(const vector<int> &query) {
    if (query.size() != 3) return false;
    if (query[1] < 1 || query[1] > N) return false;
    if (query[2] < 0 || query[2] > MAXA) return false;
    return true;
  }

  bool validateQuery2(const vector<int> &query) {
    if (query.size() != 2) return false;
    if (query[1] < 1 || query[1] > N) return false;
    return true;
  }

  bool eachQueryValid(const vector<vector<int>> &QUERIES) {
    bool ok = false;
    for (vector<int> query : QUERIES) {
      if (query[0] == 1) {
        if (validateQuery1(query) == false) {
          return false;
        }
      }else if (query[0] == 2) {
        ok = true;
        if (validateQuery2(query) == false) {
          return false;
        }
      }else {
        return false;
      }
    }
    return ok;
  }

  bool isTree(int N, const vector<int> &U, const vector<int> &V) {
    vector<int> par(N);
    iota(par.begin(), par.end(), 0);
    auto root = [&](int u) {
      vector<int> pars;
      while (u != par[u]) {
        pars.push_back(u);
        u = par[u];
      }
      for (int p: pars) par[p] = u;
      return u;
    };
    for (int i = 0; i < N-1; ++i) {
      if (root(U[i] - 1) == root(V[i] - 1)) return false;
      par[root(V[i] - 1)] = root(U[i] - 1);
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "6",
      "1 2",
      "1 6",
      "2 4",
      "4 3",
      "5 4",
      "7",
      "2 3",
      "1 2 7",
      "2 3",
      "2 6",
      "1 4 4",
      "2 4",
      "2 1",
    });
    Output({
      "0",
      "7",
      "0",
      "4",
      "0",
    });
  }

  void BeforeTestCase() {
    U.clear(); V.clear();
    QUERIES.clear();
  }

  void AfterTestCase() {
    rnd.shuffle(QUERIES.begin(), QUERIES.end());
  }

  void TestGroup1() {
    Subtasks({1});
    
    // random small testcase0
    CASE(N = 1; Q = 200000; makeTree(); randomA(); randomQuery(1, Q));
    CASE(N = 2; Q = 200000; makeTree(); randomA(); randomQuery(1, Q));
    CASE(N = 10; Q = 10; makeTree(); randomA(); randomQuery(Q/2, Q));
    CASE(N = 100; Q = 100; makeTree(); randomA(); randomQuery(Q/2, Q));
    CASE(N = 1000; Q = 1000; makeTree(); randomA(); randomQuery(Q/2, Q));
    
    // High Degree Testcase
    CASE(N = rnd.nextInt(MAXN-10000, MAXN); Q = MAXQ; makeTreeDeg(sqrt(N)-10, sqrt(N)+100); randomA(); randomQuery(1, Q/3));
    CASE(N = rnd.nextInt(MAXN-10000, MAXN); Q = MAXQ; makeTreeDeg(sqrt(N)-10, sqrt(N)+100); randomA(); randomQuery(Q*2/3, Q));
    CASE(N = rnd.nextInt(MAXN-10000, MAXN); Q = MAXQ; makeTreeDeg(sqrt(N)-10, sqrt(N)+100); randomA(); randomDepthBasedQuery(1, Q/3));
    CASE(N = rnd.nextInt(MAXN-10000, MAXN); Q = MAXQ; makeTreeDeg(sqrt(N)-10, sqrt(N)+100); randomA(); randomDepthBasedQuery(Q*2/3, Q));
    CASE(N = rnd.nextInt(MAXN-10000, MAXN); Q = MAXQ; makeTreeDeg(sqrt(N)-100, sqrt(N)+1000); randomA(); randomDepthBasedQuery(Q/2, Q));
    
    // Unique Tree Testcase
    CASE(N = MAXN; Q = MAXQ; makeChain(1); randomA(); randomDepthBasedQuery(1, Q));
    CASE(N = MAXN; Q = MAXQ; makeChain(0); randomA(); randomQuery(1, Q));
    CASE(N = MAXN; Q = MAXQ; makeStar(1); randomA(); randomDepthBasedQuery(1, Q));
    CASE(N = MAXN; Q = MAXQ; makeStar(0); randomA(); randomQuery(1, Q));
    CASE(N = MAXN; Q = MAXQ; makeCaterpillar(); randomA(); randomDepthBasedQuery(1, Q));
    CASE(N = MAXN; Q = MAXQ; makeCaterpillar(); randomA(); randomQuery(1, Q));

    //small amount of query or ask
    CASE(N = rnd.nextInt(MAXN-10000, MAXN); Q = MAXQ; makeTree(); randomA(); randomQuery(1, 500));
    CASE(N = rnd.nextInt(MAXN-10000, MAXN); Q = MAXQ; makeTree(); randomA(); randomQuery(Q-500, Q));
    CASE(N = rnd.nextInt(MAXN-10000, MAXN); Q = MAXQ; makeTree(); randomA(); randomDepthBasedQuery(1, 500));
    CASE(N = rnd.nextInt(MAXN-10000, MAXN); Q = MAXQ; makeTree(); randomA(); randomDepthBasedQuery(Q-500, Q));
    
    //Query and Ask only on arbitary depth
    CASE(N = MAXN; Q = MAXQ; makeTreeDep(1000); randomA(); depthBasedAsk(100000, 1, 5), depthBasedUpdate(100000, 950, 1000));
    CASE(N = MAXN; Q = MAXQ; makeTreeDep(1000); randomA(); depthBasedAsk(100000, 950, 1000), depthBasedUpdate(100000, 1, 50));
  }

private:
  void shuffleTree() {
    vector<int> idxMap(N);
    iota(idxMap.begin(), idxMap.end(), 0);
    rnd.shuffle(idxMap.begin(), idxMap.end());
    
    for (int i = 0; i < N - 1; i++){
      U[i] = idxMap[U[i]-1]+1;
      V[i] = idxMap[V[i]-1]+1;
    }
  }

  void makeTree() {
    tie(U, V) = TreeRandomizer().node_count(N).index_base(1).next().edges();
    shuffleTree();
  }

  void makeTreeDeg(int loDeg, int hiDeg, int root = 1) {
    root = (root == 0 ? rnd.nextInt(1, N) : root);
    tie(U, V) = TreeRandomizer().node_count(N).index_base(1).root(root).child_count(loDeg,hiDeg).next().edges();
  }

  void makeTreeLeaf(int leafCount, int root = 1) {
    root = (root == 0 ? rnd.nextInt(1, N) : root);
    tie(U, V) = TreeRandomizer().node_count(N).index_base(1).root(root).leaf_count(leafCount).next().edges();
  }

  void makeTreeDep(int depth, int root = 1) {
    root = (root == 0 ? rnd.nextInt(1, N) : root);
    tie(U, V) = TreeRandomizer().node_count(N).index_base(1).root(root).depth(depth).next().edges();
  }

  void makeChain(int root = 1) {
    root = (root == 0 ? rnd.nextInt(1, N) : root);
    tie(U, V) = ChainTreeRandomizer().node_count(N).root(root).index_base(1).next().edges();
  }

  void makeCaterpillar(int root = 1) {
    root = (root == 0 ? rnd.nextInt(1, N) : root);
    tie(U, V) = CaterpillarTreeRandomizer().node_count(N).root(root).index_base(1).next().edges();
  }

  void makeStar(int root = 1) {
    root = (root == 0 ? rnd.nextInt(1, N) : root);
    tie(U, V) = StarTreeRandomizer().node_count(N).root(root).index_base(1).next().edges();
  }

  void randomA(int lowA = 0, int highA = MAXA) {
    // A.resize(N);
    // generate(A.begin(), A.end(), [&]() { return rnd.nextInt(lowA, highA); });
  }

  template <class T>
  inline T pickRandom(const vector<T> &V){ return V[rnd.nextInt((int)(V.size()))]; }

  //give random value added into the number
  int giveRandomValue(int number, int digit = 100, int offset = 99) {
    return number * digit + rnd.nextInt(0, offset);
  }

  //will get every vertex with depth between given parameter sorted increasingly in pair
  vector<pair<int, int>> getVertexbyDepth(int low, int high) {
    vector<int> depth(N + 1);
    vector<pair<int, int>> result;
    vector<vector<int>> adjList(N + 1);

    for (int i = 0; i < U.size(); i++) {
      adjList[U[i]].emplace_back(V[i]);
      adjList[V[i]].emplace_back(U[i]);
    }

    function<void(int, int)> dfs = [&](int u, int par) {
      if (u == 1) {
        depth[u] = 0;
      }else {
        depth[u] = depth[par] + 1;
      }

      if (low <= depth[u] && depth[u] <= high) {
        result.emplace_back(giveRandomValue(depth[u]), u);
      }

      for (int v : adjList[u]) {
        if (v != par) {
          dfs(v, u);
        }
      }
    };
    
    dfs(1, 0);
    sort(result.begin(), result.end());
    return result;
  }


  //random ask query
  void randomAsk(int cnt) {
    while (cnt--) {
      auto query = vector<int>{2, rnd.nextInt(1, N)};
      QUERIES.emplace_back(query);
    }
  }

  //random update query
  void randomUpdate(int cnt, int mn, int mx) {
    while (cnt--) {
      auto query = vector<int>{1, rnd.nextInt(1, N), rnd.nextInt(mn, mx)};
      QUERIES.emplace_back(query);
    }
  }

  void randomQuery(int mn, int mx) {
    int jumlah = rnd.nextInt(mn, mx);
    randomAsk(jumlah);
    randomUpdate(Q - jumlah, 0, 200000);
  }


  int findIndex(long long decoded) {
    long long L = 1, R = 200000, res = 69;
    while(L <= R) {
      long long mid = (L + R) >> 1;
      if((mid + 1) * mid / 2 > decoded) {
        res = mid;
        R = mid - 1;
      }else {
        L = mid + 1;
      }
    }
    return res;
  }

  //query 2, occurence is based on the depth, higher one have the higher chance to get queried.
  void depthBasedAsk(int cnt, int low, int high) {
    auto vertexList = getVertexbyDepth(low, high);
    while (cnt--) {
      long long rng = rnd.nextLongLong(0, ((vertexList.size() + 1LL) * vertexList.size()) / 2 - 1);
      int index = findIndex(rng);
      auto query = vector<int>{2, index};
      QUERIES.emplace_back(query);
    }
  }

  //query 1, occurence is based on the depth, lower one have the higher chance to get queried.
  void depthBasedUpdate(int cnt, int low, int high) {
    auto vertexList = getVertexbyDepth(low, high);
    reverse(vertexList.begin(), vertexList.end());
    while (cnt--) {
      long long rng = rnd.nextLongLong(0, ((vertexList.size() + 1LL) * vertexList.size()) / 2 - 1);
      int index = findIndex(rng);
      auto query = vector<int>{1, index, rnd.nextInt(0, 200000)};
      QUERIES.emplace_back(query);
    }
  }

  void randomDepthBasedQuery(int mn, int mx) {
    int jumlah = rnd.nextInt(mn, mx);
    depthBasedAsk(jumlah, 1, MAXN);
    depthBasedUpdate(Q - jumlah, 1, MAXN);
  }
};