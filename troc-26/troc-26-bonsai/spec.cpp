#include <tcframe/runner.hpp>
#include <tcrand/tree.hpp>
#include <bits/stdc++.h>
#include "helper/treegenerator.h"
using namespace tcframe;
using namespace tcrand;
using namespace tree_generator_by_ouuan;

typedef long long lli;
typedef long long LL;
typedef pair<int, int> ii;
typedef pair<lli, lli> ll;

#define fi first
#define se second
#define pb push_back
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;

const int MAXA = 1e6;
const int MAXN = 1e5;


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<long long, null_type, less<long long>, rb_tree_tag, tree_order_statistics_node_update> pbds;
#define fbo find_by_order
#define ook order_of_key

LL expo(LL a, LL b) {
  LL ret = 1;
  while (b > 0) {
    if (b & 1) {
      if (ret >= LLONG_MAX / a) return LLONG_MAX;
      ret = (ret * a);
    }
    if (a >= LLONG_MAX / a) return LLONG_MAX;
    a = (a * a); b >>= 1;
  }
  return ret;
}


LL countComplete(int r, int n) {
  assert(expo(r, n) != LLONG_MAX);
  return (expo(r, n) - 1) / (r - 1);
}

class HalvingHelper {
 public:
  vector <int> U, V;
  vector <vector <int>> edge;
  vector <int> ans;
  tcframe::Random *rnd;
  int k;
  HalvingHelper(vector <int> _U, vector <int> _V, int _k, tcframe::Random *_rnd) {
    rnd = _rnd;
    U = _U;
    V = _V;
    k = _k;
    int n = sz(U) + 1;
    edge.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
      edge[U[i]].pb(V[i]);
      edge[V[i]].pb(U[i]);
    }
    ans.resize(n);
  }

  void dfs(int pos, int depth, int par = -1) {
    ans[pos - 1] = rnd->nextInt(1, MAXA);
    ans[pos - 1] /= expo(k, depth);

    // Add offset
    ans[pos - 1] += rnd->nextInt(1, 20);
    ans[pos - 1] -= 10;

    // Handle corners
    ans[pos - 1] = min(ans[pos - 1], MAXA);
    if (ans[pos - 1] <= 0) ans[pos - 1] = rnd->nextInt(1, 5);
    trav(nx, edge[pos]) {
      if (nx == par) continue;
      dfs(nx, depth + 1, pos);
    }
  }

  vector <int> solve() {
    dfs(1, 0);
    return ans;
  }
};

class AKBDHelper {
 public:
  int n, a, k, b, d;
  int lastIndex;
  LL akBigger;
  vector <vi> edge;
  vector <int> U, V, A;
  vector <int> AKNode;
  vector <int> BDNode;
  vector <int> collisionNode;

  void dfs(int pos, int depth, bool isAk, bool isBd, int par) {
    if (par != -1) U.pb(pos), V.pb(par);
    if (isAk && isBd) collisionNode.pb(pos);
    else if (isAk) AKNode.pb(pos);
    else BDNode.pb(pos);

    if (isAk && isBd) {
      if (depth + 1 <= d) {
        for (int i = 1; i <= a; i++) {
          // Increase depth
          lastIndex++;
          dfs(lastIndex, depth + 1, isAk, isBd, pos);
        }
        for (int i = 1; i <= b - a; i++) {
          lastIndex++;
          dfs(lastIndex, depth + 1, 0, isBd, pos);
        }
      } else if (depth + 1 <= k) {
        for (int i = 1; i <= a; i++) {
          lastIndex++;
          dfs(lastIndex, depth + 1, isAk, 0, pos);
        }
      }
    } else if (isAk) {
      if (depth + 1 <= k) {
        for (int i = 1; i <= a; i++) {
          lastIndex++;
          dfs(lastIndex, depth + 1, isAk, isBd, pos);
        }
      }
    } else {
      if (depth + 1 <= d) {
        for (int i = 1; i <= b; i++) {
          lastIndex++;
          dfs(lastIndex, depth + 1, isAk, isBd, pos);
        }
      }
    }
  }

  AKBDHelper(int _a, int _k, int _b, int _d, LL _akBigger, tcframe::Random *rnd) : a(_a), k(_k), b(_b), d(_d), akBigger(_akBigger) {
    assert(a < b);
    assert(d < k);
    LL first = countComplete(a, k);
    LL second = countComplete(b, d);
    LL collision = countComplete(a, d);
    if (first + second - collision > MAXN) {
      cout << first << " " << second << " " << collision << ": NOT OK, ";
      assert(false);
    }
    n = first + second - collision;
    A.resize(n + 1);
    lastIndex = 1;
    dfs(1, 1, 1, 1, -1);
    assert(lastIndex == n);
    // Assign weight here
    assert(sz(AKNode) == first - collision);
    assert(sz(BDNode) == second - collision);
    assert(sz(collisionNode) == collision);
    trav(cur, collisionNode) {
      A[cur] = rnd->nextInt(1, MAXA / 1000);
    }
    // LL collisionTotal = 0;
    // trav(cur, collisionNode) collisionTotal += A[cur];
    LL AKTotal = 0;
    trav(cur, AKNode) {
      A[cur] = rnd->nextInt(1, MAXA / 1000);
      AKTotal += A[cur];
    }
    LL BDTotal = 0;
    trav(cur, BDNode) {
      A[cur] = rnd->nextInt(1, MAXA / 1000);
      BDTotal += A[cur];
    }
    // cout << AKTotal << " " << BDTotal << " " << collisionTotal << endl;
    // Current diff, target is AKBigger
    LL diff = akBigger - (AKTotal - BDTotal);
    // cout << diff << endl;
    if (diff > 0) {
      // Add AK amount of diff fairly
      int curn = sz(AKNode);
      LL rem = diff % curn;
      for (int i = 0; i < curn; i++) {
        A[AKNode[i]] += diff / curn;
        if (i + 1 <= rem) A[AKNode[i]]++;
      }
    } else if (diff < 0) {
      diff = abs(diff);
      // Add BD amount of diff fairly
      int curn = sz(BDNode);
      LL rem = diff % curn;
      for (int i = 0; i < curn; i++) {
        A[BDNode[i]] += diff / curn;
        if (i + 1 <= rem) A[BDNode[i]]++;
      }
    }
    // Remove first element of A
    A.erase(A.begin());
  }
};

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  long long ANS;
  vi U, V, A, P;

  void InputFormat() {
    LINE(N);
    LINE(A % SIZE(N));
    LINE(P % SIZE(N - 1));
  }

  void OutputFormat() {
    LINE(ANS);
  }

  void GradingConfig() {
    TimeLimit(5);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(isTree(N, P));
    CONS(eachElementBetween(A, 1, MAXA));
  }

  void Subtask1() {
    Points(100);
  }

 private:
  template <class T>
  /**
   * Returns when each element of a vector is between those insides
   **/
  bool eachElementBetween(const vector<T> &X, T lo, T hi) {
    for (T x : X)
      if (x < lo || hi < x)
        return false;
    return true;
  }

 public:
  /**
   * Check whether the given graph is a tree
   **/
  bool isTree(int N, const vector<int> &P, const vector<int> &V) {
    assert(N - 1 == (int) U.size());
    assert(N - 1 == (int) V.size());
    vector<int> par(N);
    iota(par.begin(), par.end(), 0);
    auto root = [&](int u) {
      vector<int> pars;
      while (u != par[u]) {
        pars.push_back(u);
        u = par[u];
      }
      for (int p : pars) par[p] = u;
      return u;
    };
    for (int i = 0; i < N - 1; ++i) {
      // cout << U[i] << " " << V[i] << endl;
      assert(1 <= U[i] && U[i] <= N);
      assert(1 <= V[i] && V[i] <= N);
      if (root(U[i] - 1) == root(V[i] - 1)) return false;
      par[root(V[i] - 1)] = root(U[i] - 1);
    }
    return true;
  }

  bool isTree(int N, const vector<int> &P) {
    assert(P.size() == N - 1);
    for(int i = 2;i <= N;i++){
      if(!(P[i - 2] < i)) return false;
    }
    return true;
  }
};


class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  // void SampleTestCase1() {
  //   Subtasks({1});
  //   Input({
  //     "11",
  //     "3 4 2 8 7 3 6 1 4 2 4",
  //     "1 2 2 1 5 1 5 7 7 10",
  //   });
  //   Output({
  //     "15", "29", "20", "3", "3", "3", "3", "3", "3", "3", "3",
  //   });
  // }


  // void SampleTestCase2() {
  //   Subtasks({1});
  //   Input({
  //     "11",
  //     "3 20 2 20 3 8 20 2 4 1 4",
  //     "1 2 1 4 2 1 7 8 4 7",
  //   });
  //   Output({
  //     "31", "59", "63", "3", "3", "3", "3", "3", "3", "3", "3",
  //   });
  // }

  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "11",
      "3 20 20 8 4 20 3 20 2 1 35",
      "1 1 2 3 1 6 3 2 6 8",
    });
    Output({
      "242"
      // "78", "77", "63", "3", "3", "3", "3", "3", "3", "3", "3",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "8",
      "1 3 2 3 2 2 4 6",
      "1 1 1 3 2 3 4",
    });
    Output({
      "36"
      // "10", "12", "9", "1", "1", "1", "1", "1",
    });
  }

  void BeforeTestCase() {
    A.clear();
    U.clear();
    V.clear();
    P.clear();
  }

  void AfterTestCase() {
    changeToNewFormat();
  }

  void TestGroup1() {
    Subtasks({1});
    // CASE(N = 10; makeRandomTree(); shuffleTree(); makeRandomA());
    CASE(N = MAXN; makeRandomTree(); shuffleTree(); makeRandomA());
    // CASE(N = MAXN; makeRandomTree(); shuffleTree(); makeRandomA());
    // CASE(N = MAXN; makeRandomTree(); shuffleTree(); makeRandomA());


    // Chain with root at random, small N
    // CASE(N = 10; makeChain(0);  makeRandomA());
    // Chain with root at ends
    // CASE(N = highN(); makeChain(1);  makeRandomA());
    // Chain with root at random
    CASE(N = highN(); makeChain(0); shuffleTree(); makeRandomA());

    // Flower knary
    // CASE(N = 20; flowerKnaryCase(2);  makeRandomA());

    // Extreme degree
    CASE(N = highN(); makeTreeDeg(30, 50); makeAHalving(40));
    // CASE(N = highN(); makeTreeDeg(40, 100); makeAHalving(100));
    CASE(N = MAXN; makeTreeDeg(sqrt(N), sqrt(N) + 3); makeRandomA());
    CASE(N = highN(); makeTreeDeg(1000, 2000); makeAHalving());
    // CASE(N = highN(); makeTreeDeg(700, 1000); makeRandomA());
    CASE(N = highN(); makeTreeDeg(5000, 10000); makeRandomA());
    CASE(N = highN(); distinctCase(); makeAHalving());
    CASE(N = highN(); makeTreeDep(300); makeAHalving());
    CASE(N = highN(); makeTreeDep(16); makeAHalving());
    CASE(N = highN(); flowerKnaryCase(1000); makeAHalving());
    CASE(N = highN(); halvingCase(); makeAHalving());
    CASE(N = highN(); minDegreeCase(200); makeAHalving());
    CASE(N = highN(); maxDegreeCase(1000); makeAHalving());
    CASE(N = highN(); maxDegreeCase(1000); makeRandomA());


    CASE(N = highN(); maxDegreeCase(1000); makeRandomA());

    // CASE(N = 100; knaryCase(2); makeAHalving());
    CASE(N = highN(); knaryCase(20); makeAHalving(20));
    CASE(N = highN(); knaryCase(450); makeRandomA());
    CASE(N = highN(); knaryCase(2000); makeRandomA());

    // CASE(akbdTree(2, 3, 3, 2, 10));
    // CASE(akbdTree(2, 3, 3, 2, -10));
    // CASE(akbdTree(2, 6, 3, 4, 1));
    // CASE(akbdTree(2, 6, 3, 4, -1));

    CASE(akbdTree(4, 8, 8, 6, -10));
    CASE(akbdTree(2, 16, 3, 10, 10));
    CASE(akbdTree(10, 5, 30000, 2, 1));
    CASE(akbdTree(6, 7, 40000, 2, -1));
    CASE(akbdTree(5, 8, 1000, 2, -1));

    CASE(akbdTree(10, 5, 30000, 2, 1); maxA());
    CASE(akbdTree(6, 7, 40000, 2, -1); maxA());
    CASE(akbdTree(5, 8, 1000, 2, -1); maxA());

    // Tipe, root degree, decrease rate

    // CASE(N = 50; decreasingDegreeTree("root", 10, 1.2); makeRandomA());
    // CASE(N = 50; decreasingDegreeTree("random", 10, 5); makeRandomA());
    // CASE(N = 50; decreasingDegreeTree("divide", 10, 1.5); makeRandomA());
    // CASE(N = 50; decreasingDegreeTree("subtract", 10, 4); makeRandomA());
    CASE(N = highN(); decreasingDegreeTree("root", 4000, 1.2); insertNoiseUntilMAXN(); makeRandomA());
    CASE(N = highN(); decreasingDegreeTree("root", 40000, 1.1); insertNoiseUntilMAXN(); makeRandomA());
    CASE(N = highN(); decreasingDegreeTree("random", 2000, 100); insertNoiseUntilMAXN(); makeRandomA());
    CASE(N = highN(); decreasingDegreeTree("random", 5000, 69); insertNoiseUntilMAXN(); makeAHalving(2));
    CASE(N = highN(); decreasingDegreeTree("random", 30000, 10); insertNoiseUntilMAXN(); makeAHalving());
    CASE(N = highN(); decreasingDegreeTree("divide", 5000, 1.5); insertNoiseUntilMAXN(); makeRandomA());
    CASE(N = highN(); decreasingDegreeTree("divide", 50000, 2.5); insertNoiseUntilMAXN(); makeRandomA());
    CASE(N = highN(); decreasingDegreeTree("subtract", 4000, 69); insertNoiseUntilMAXN(); makeRandomA());
    CASE(N = highN(); decreasingDegreeTree("subtract", 7000, 1); insertNoiseUntilMAXN(); makeAHalving());
  }

      private:

  void changeToNewFormat() {
    pbds bfsTree;
    bfsTree.insert(1);
    vector <vector<int>> edge(N + 1);
    P.resize(N + 1, -1);
    for (int i = 0; i < N - 1; i++) {
      edge[U[i]].pb(V[i]);
      edge[V[i]].pb(U[i]);
    }
    vector <int> index(N + 1);
    int cnt = 0;
    while (sz(bfsTree)) {
      int cursize = sz(bfsTree);
      int relax = rnd.nextInt(0, cursize - 1);
      auto ptr = bfsTree.find_by_order(relax);
      int now = *ptr;
      bfsTree.erase(ptr);
      index[now] = ++cnt;
      trav(nx, edge[now]) if (nx != P[now]) {
        P[nx] = now;
        bfsTree.insert(nx);
      }
    }
    // Translate P and A accordingly
    vector <int> newP(N), newA(N);
    for (int i = 0; i < N; i++) {
      newA[index[i + 1] - 1] = A[i];
      if (i) newP[index[i + 1] - 1] = index[P[i + 1]];
    }
    newP.erase(newP.begin());
    P = newP;
    A = newA;
    // for (int i = 1; i <= N; i++) cout << index[i] << " \n"[i == N];
    // for (int i = 0; i < N; i++) cout << newA[i] << " \n"[i == N - 1];
    // for (int i = 0; i < N - 1; i++) {
    //   cout << i + 2 << " " << newP[i] << endl;
    // }
  }

  int highN() {
    return rnd.nextInt(MAXN * 9 / 10, MAXN);
  }

  void makeRandomA(int lo = 1, int hi = MAXA) {
    A.resize(N);
    trav(cur, A) cur = rnd.nextInt(lo, hi);
    return;
  }

  void makeTreeDeg(int loDeg, int hiDeg, int root = 1) {
    root = (root == 0 ? rnd.nextInt(1, N) : root);
    do {
      tie(U, V) = TreeRandomizer().node_count(N).index_base(1).root(root).child_count(loDeg, hiDeg).next().edges();
    } while (!isTree(N, U, V));
  }

  void makeRandomTree() {
    int root = rnd.nextInt(1, N);
    do {
      tie(U, V) = TreeRandomizer().node_count(N).index_base(1).root(root).next().edges();
    } while (!isTree(N, U, V));
  }

  void makeTreeLeaf(int leafCount, int root = 1) {
    root = (root == 0 ? rnd.nextInt(1, N) : root);
    do {
      tie(U, V) = TreeRandomizer().node_count(N).index_base(1).root(root).leaf_count(leafCount).next().edges();
    } while (!isTree(N, U, V));

  }

  void makeTreeDep(int depth, int root = 1) {
    root = (root == 0 ? rnd.nextInt(1, N) : root);
    do {
      tie(U, V) = TreeRandomizer().node_count(N).index_base(1).root(root).depth(depth).next().edges();
    } while (!isTree(N, U, V));

  }

  void makeChain(int root = 1) {
    root = (root == 0 ? rnd.nextInt(1, N) : root);
    do {
      tie(U, V) = ChainTreeRandomizer().node_count(N).root(root).index_base(1).next().edges();
    } while (!isTree(N, U, V));
  }

  void makeCaterpillar(int root = 1) {
    root = (root == 0 ? rnd.nextInt(1, N) : root);
    do {
      tie(U, V) = CaterpillarTreeRandomizer().node_count(N).root(root).index_base(1).next().edges();
    } while (!isTree(N, U, V));
  }

  void makeStar(int root = 1) {
    root = (root == 0 ? rnd.nextInt(1, N) : root);
    do {
      tie(U, V) = StarTreeRandomizer().node_count(N).root(root).index_base(1).next().edges();
    } while (!isTree(N, U, V));
  }

  // Start of Trees Generator --------------

  // void get(vector <int> &U, vector <int> &V,
  //          bool ShuffleV = 1, bool ShuffleE = 1,
  //          bool swapV = 0);
  // This will assign edges to U and V consecutively
  // and shuffle accordingly. By default auto shuffle both, and dont swap edges. The generator bit weird for star...
  // Random tree with size N

  void fixOuuan() {
    for (int i = 0; i < N - 1; i++) {
      U[i]++;
      V[i]++;
    }
  }

  // All nodes degree doesn't exceed K
  void maxDegreeCase(int K) {
    OuuanTree tree;
    tree.maxDegree(N, K, 0);
    tree.get(U, V);
    fixOuuan();
    assert(isTree(N, U, V));
  }

  // All non-leaf nodes degree in range [K, K + 5]
  void minDegreeCase(int K) {
    OuuanTree tree;
    tree.minDegree(N, K, 5, 0);
    tree.get(U, V);
    fixOuuan();
    assert(isTree(N, U, V));
  }

// All nodes will try to make K-nary, will add accordingly if can't
  void knaryCase(int K) {
    OuuanTree tree;
    tree.complete(N, K, 0);
    tree.get(U, V);
    fixOuuan();
    assert(isTree(N, U, V));
  }

// All nodes will try to make K-nary, with N/2 nodes and some offsets for the rest
  void flowerKnaryCase(int K) {
    OuuanTree tree;
    tree.flowerKnary(N, N / 2, K, 0);
    tree.get(U, V);
    fixOuuan();
    assert(isTree(N, U, V));
  }

  void silkwormCase() {
    OuuanTree tree;
    tree.silkworm(N, 0);
    tree.get(U, V);
    fixOuuan();
    assert(isTree(N, U, V));
  }

  void starShuffleCase() {
    OuuanTree tree;
    tree.star(N, 0);
    tree.get(U, V);
    fixOuuan();
    assert(isTree(N, U, V));
  }

  void distinctCase() {
    OuuanTree tree;
    tree.distinctDegree(N, 0);
    tree.get(U, V);
    fixOuuan();
    assert(isTree(N, U, V));
  }

  void halvingCase() {
    OuuanTree tree;
    tree.halvingDegree(N, 0);
    tree.get(U, V);
    fixOuuan();
    assert(isTree(N, U, V));
  }

  // End of Trees Generator --------------

  /**
   * Shuffle the current tree index
   **/
  void shuffleTree() {
    vector<int> idxMap(N);
    iota(idxMap.begin(), idxMap.end(), 0);
    rnd.shuffle(idxMap.begin(), idxMap.end());
    for (int i = 0; i < N - 1; i++) {
      U[i] = idxMap[U[i] - 1] + 1;
      V[i] = idxMap[V[i] - 1] + 1;
    }
    if (sz(A) == N) {
      vector <int> old = A;
      for (int i = 0; i < N; i++) {
        A[idxMap[i]] = old[i];
      }
    }
  }

  /**
   * Shuffle the current tree index, except root at 1
   **/
  void shuffleTreeExceptRoot() {
    vector<int> idxMap(N);
    iota(idxMap.begin(), idxMap.end(), 0);
    rnd.shuffle(idxMap.begin(), idxMap.end());
    for (int i = 0; i < N; i++) if (idxMap[i] == 0) swap(idxMap[0], idxMap[i]);
    for (int i = 0; i < N - 1; i++) {
      U[i] = idxMap[U[i] - 1] + 1;
      V[i] = idxMap[V[i] - 1] + 1;
    }
    if (sz(A) == N) {
      vector <int> old = A;
      for (int i = 0; i < N; i++) {
        A[idxMap[i]] = old[i];
      }
    }
  }

  // For each level, divide the random by k^level, level starts with 0 from root
  void makeAHalving(int k = 2) {
    HalvingHelper solve(U, V, k, &rnd);
    A = solve.solve();
  }

  // a^k tree
  // b^d tree
  // a < b, d < k
  // Make a-ary tree with depth k, alongside with b-ary tree with depth d, maintaining minimum nodes
  // countComplete(a, k) + countComplete(b, d) - countComplete(a, d) < MAX
  void akbdTree(int a, int k, int b, int d, LL akBigger) {
    AKBDHelper solve(a, k, b, d, akBigger, &rnd);
    A = solve.A;
    U = solve.U;
    V = solve.V;
    N = solve.n;
    // shuffleTreeExceptRoot();
  }

  void insertNoiseUntilMAXN() {
    for (int i = N + 1; i <= MAXN; i++) {
      U.pb(rnd.nextInt(1, i - 1));
      V.pb(i);
    }
    N = MAXN;
  }

  void decreasingDegreeTree(string tipe, int k, double decRate) {
    vector <int> parK(N + 1);
    // Root is 1
    int idx = 1;
    int intRate = decRate;
    for (int i = 1; i <= N; i++) {
      if (idx == N) break;
      if (i > 1) {
        if (tipe == "divide") {
          k = (int) max(1.0, parK[i] / decRate);
        } else if (tipe == "root") {
          k = (int) max(1.0, pow((double)parK[i], 1 / (double)decRate));
        } else if (tipe == "subtract") {
          k = max(1, parK[i] - intRate);
        } else {
          assert(tipe == "random");
          k = max(1, parK[i] - rnd.nextInt(1, intRate));
        }
      }
      for (int j = 1; j <= k; j++) {
        if(idx == N) break;
        idx++;
        // cout << i << " " << idx << endl;
        U.pb(i);
        V.pb(idx);
        parK[idx] = k;
      }
    }
  }
  void maxA() {
    A.resize(N, MAXA);
  }
};
