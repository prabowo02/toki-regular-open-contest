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

const int MAXN = 100000;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N;
  vector<int> A;
  vector<int> U, V;
  string ANS;

  void InputFormat() {
    LINE(N);
    LINE(A % SIZE(N));
    LINES(U, V) % SIZE(N - 1);
  }

  void OutputFormat(){
    LINE(ANS);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS((2 <= N) && (N <= MAXN));
    CONS(eachElementBetween(A, 0, 1));
    CONS(eachElementBetween(U, 1, N));
    CONS(eachElementBetween(V, 1, N));
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
      "4",
      "1 1 1 1",
      "1 2",
      "2 3",
      "2 4",
    });
    Output({
      "YES",
    });
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "2",
      "1 1",
      "1 2",
    });
    Output({
      "NO",
    });
  }

  void BeforeTestCase() {
    A.clear();
    U.clear(); V.clear();
  }

  void AfterTestCase() {
    shuffleTree();
  }

  void TestGroup1() {
    Subtasks({1});
    
    // every small testcase0
    CASE(N = 2, makeTree(), A = {0, 0});
    CASE(N = 2, makeTree(), A = {1, 0});
    CASE(N = 3, makeTree(), A = {1, 1, 1});
    CASE(N = 3, makeTree(), A = {0, 0, 0});
    CASE(N = 3, U = {2, 3}, V = {1, 1}, A = {0, 1, 1});
    CASE(N = 3, U = {2, 3}, V = {1, 1}, A = {1, 0, 1});
    CASE(N = 3, U = {2, 3}, V = {1, 2}, A = {1, 0, 0});
    CASE(N = 3, U = {2, 3}, V = {1, 2}, A = {0, 1, 0});
    
    //big tree 
    CASE(N = 100000, makeTree(), randomA());
    CASE(N = 95947, makeTree(), fixedA(0));
    CASE(N = 98795, makeTree(), fixedA(1));
    CASE(N = 98846, makeTree(), fixedA(N - 1));
    CASE(N = 99999, makeTree(), fixedA(N));

    //in case someone even accessed the tree
    CASE(N = 100000, makeTreeDeg(sqrt(N)-100, sqrt(N)+1000), randomA());
    CASE(N = 100000, makeTreeLeaf(100), fixedA(N), makeLeaf(0));
    CASE(N = 100000, makeTreeLeaf(10000), fixedA(N - 1000), makeLeaf(1));
    CASE(N = 100000, makeChain(), fixedA(0));
    CASE(N = 100000, makeStar(), randomA());
    CASE(N = 100000, makeStar(), fixedA(1));
    CASE(N = 100000, makeCaterpillar(), randomA());
  }

private:
  void shuffleTree() {
    vector<int> idxMap(N);
    vector<int> B(N);
    iota(idxMap.begin(), idxMap.end(), 0);
    rnd.shuffle(idxMap.begin(), idxMap.end());
    
    for (int i = 0; i < N; i++) {
      B[idxMap[i]] = A[i];
    }

    for (int i = 0; i < N - 1; i++) {
      U[i] = idxMap[U[i] - 1] + 1;
      V[i] = idxMap[V[i] - 1] + 1;
    }
    A = B;
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

  void randomA() {
    A.resize(N);
    generate(A.begin(), A.end(), [&]() { return rnd.nextInt(0, 1); });
  }

  void fixedA(int cnt_one) {
    if (cnt_one > N) cnt_one = N;
    A.resize(N);
    int index = 0;
    generate(A.begin(), A.end(), [&]() { return ++index > cnt_one ? 0 : 1; });
    rnd.shuffle(A.begin(), A.end());
  }

  void makeLeaf(int value) {
    vector<int> cnt(N + 5);
    for(int i = 0; i < U.size(); i++) {
      cnt[U[i]]++;
      cnt[V[i]]++;
    }
    for(int i = 1; i <= N; i++) {
      if(cnt[i] == 1) {
        A[i - 1] = value;
      }
    }
  }
};
