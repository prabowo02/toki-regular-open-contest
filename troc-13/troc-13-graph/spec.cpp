// WARNING! This spec uses tcrand
// Compile with C++14
// Source : https://github.com/afaji/tcrand
// Please do get the library before compiling, and put it in tcframe/include/tcrand
#include <bits/stdc++.h>
#include <tcrand/tree.hpp>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;
using namespace tcrand;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<vector<LL>> grid;
#define fi first
#define se second
#define pb push_back

const int MAXN = 100000;
const int MAXQ = 100000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, Q;
    vector <int> U, V;
    vector <int> A, B, R;
    vector <int> ANS;

    void InputFormat() {
        LINE(N, Q);
        LINES(U, V) % SIZE(N-1);
        LINES(A, B, R) % SIZE(Q);
    }

    void OutputFormat(){
        LINES(ANS) % SIZE(Q);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS((1 <= N) && (N <= MAXN));
        CONS((1 <= Q) && (Q <= MAXQ));
        CONS(eachElementBetween(A, 1, N));
        CONS(eachElementBetween(B, 1, N));
        CONS(eachElementBetween(R, 1, N));
        CONS(isTree(N, U, V));
        CONS(different(A,B));
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
    bool different(const vector<int> &U, const vector<int> &V){
        for(int i = 0;i < Q;i++) if(U[i] == V[i]) return 0;
        return 1;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1});
        Input({
            "5 5",
            "1 2",
            "2 3",
            "2 4",
            "4 5",
            "3 5 1",
            "3 1 1",
            "2 3 1",
            "5 1 2",
            "5 4 1"
        });
        Output({
            "1",
            "2",
            "1",
            "0",
            "1",
        });
    }
    void BeforeTestCase(){
        U.clear(); V.clear();
        A.clear(); B.clear(); R.clear();
    }

    void TestGroup1(){
        Subtasks({1});

        // TC 1 - 5
        CASE(N = 2; U = {2}; V = {1}; allQuery());
        CASE(N = 3; makeChain(); shuffleTree(); allQuery());
        CASE(N = 7; Q = 10; U = {3,1,2,2,4,4}; V = {6,2,3,4,7,5}; A = {5,6,3,1,4,3,3,1,1,7}; B = {6,5,1,6,6,5,1,6,6,1}; R = {1,1,6,5,7,7,5,7,5,6});
        CASE(N = 15; Q = 200; makeTreeDeg(1,4); shuffleTree(); randomQuery(Q));
        CASE(N = 13; Q = 1; U = {1,2,3,4,4,5,5,8,9,10,11,12}; V = {2,3,4,5,6,7,8,9,10,11,12,13}; A = {5}; B = {13}; R = {1});
        
        // TC 6 - 10
        CASE(N = 46; makeTreeLeaf(16); shuffleTree(); allQuery());
        CASE(N = 1000; Q = 10000; makeTreeDeg(1,10); shuffleTree(); randomQuery(Q));
        CASE(N = 1000; Q = 10000; makeChain(); shuffleTree(); randomQuery(Q));
        CASE(N = 1000; Q = 10000; makeStar(); shuffleTree(); randomQuery(Q));
        CASE(N = MAXN; Q = MAXQ; makeCaterpillar(); shuffleTree(); randomQuery(Q));

        // TC 11 - 15
        CASE(N = MAXN; Q = MAXQ; makeTreeDeg(5,20); shuffleTree(); randomQuery(Q));
        CASE(N = MAXN; Q = MAXQ; makeTreeDep(3000); shuffleTree(); randomQuery(Q));
        CASE(N = MAXN; Q = MAXQ; makeTreeDep(20000); shuffleTree(); randomQuery(Q));
        CASE(N = MAXN; Q = MAXQ; makeTreeDep(10000); shuffleTree(); randomQuery(Q));
        CASE(N = MAXN; Q = MAXQ; makeTreeLeaf(30000); shuffleTree(); randomQuery(Q));
    }

private:
    void shuffleTree(){
        vector<int> idxMap(N);
        iota(idxMap.begin(), idxMap.end(), 0);
        rnd.shuffle(idxMap.begin(), idxMap.end());
        for(int i = 0;i < N-1;i++){
            U[i] = idxMap[U[i]-1]+1;
            V[i] = idxMap[V[i]-1]+1;
        }
        // cout << "Shuffle done, "  << flush;
    }

    void makeTreeDeg(int loDeg, int hiDeg){
        // cout << "Making tree, " << flush;
        Tree t = TreeRandomizer().node_count(N).index_base(1).child_count(loDeg,hiDeg).next();
        U = t.edges().fi;
        V = t.edges().se;
        // cout << "Tree done, " << flush;
    }

    void makeTreeLeaf(int leafCount){
        // cout << "Making tree, " << flush;
        Tree t = TreeRandomizer().node_count(N).index_base(1).leaf_count(leafCount).next();
        U = t.edges().fi;
        V = t.edges().se;
        // cout << "Tree done, " << flush;
    }

    void makeTreeDep(int depth){
        // cout << "Making tree, " << flush;
        Tree t = TreeRandomizer().node_count(N).index_base(1).depth(depth).leaf_count(rnd.nextInt(100,1000)).next();
        U = t.edges().fi;
        V = t.edges().se;
        // cout << "Tree done, " << flush;
    }

    void makeChain(){
        // cout << "Making tree, " << flush;
        Tree t = ChainTreeRandomizer().node_count(N).index_base(1).next();
        U = t.edges().fi;
        V = t.edges().se;
        // cout << "Tree done, " << flush;
    }
    void makeCaterpillar(){
        // cout << "Making tree, " << flush;
        Tree t = CaterpillarTreeRandomizer().node_count(N).index_base(1).next();
        U = t.edges().fi;
        V = t.edges().se;
        // cout << "Tree done, " << flush;
    }
    void makeStar(){
        // cout << "Making tree, " << flush;
        Tree t = StarTreeRandomizer().node_count(N).index_base(1).next();
        U = t.edges().fi;
        V = t.edges().se;
        // cout << "Tree done, " << flush;
    }
    template <class T>
    int pickRandom(vector<T> &V){
        return V[rnd.nextInt(V.size())];
    }
    void allQuery(){
        // cout << "Making all query, " << flush;
        for(int i = 1;i <= N;i++){
            for(int j = 1;j <= N;j++){
                for(int k = 1;k <= N;k++){
                    if(i == j) continue;
                    A.pb(i); B.pb(j); R.pb(k);
                }
            }
        }
        Q = A.size();
        // assert(Q == A.size());
        // cout << "all Query done, running solution " << flush;
    }
    void randomQuery(int Q){

        vector <int> degreeCount(N+1);
        vector <int> leaf;
        for(int i = 0;i < N;i++){
            degreeCount[U[i]]++;
            degreeCount[V[i]]++;
        }

        // cout << "Computing leaf, "  << flush;
        for(int i = 1;i <= N;i++){
            if(degreeCount[i] == 1){
                leaf.pb(i);
            }
        }
        // cout << "Computed " << leaf.size() << " leaf, "  << flush;

        // cout << "Making query, "  << flush;

        for(int i = 1;i <= Q;i++){
            // At least 90% of the query gotta be leaf
            int rootType = rnd.nextInt(1,10), root, a, b;
            a = rnd.nextInt(1,N); b = rnd.nextInt(1,N);
            while(a == b){ b = rnd.nextInt(1,N); }
            if(rootType == 1){
                // Random type
                root = rnd.nextInt(1,N);
            }else{
                // Leaf only type
                root = pickRandom(leaf);
            }
            A.pb(a); B.pb(b); R.pb(root);
        }
        // cout << "Query done, running solution "  << flush;
    }
};
