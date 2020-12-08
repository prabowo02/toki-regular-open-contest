// WARNING! This spec uses tcrand
// Source : https://github.com/afaji/tcrand
// Please do get the library before compiling, and put it in tcframe/include/tcrand
#include <bits/stdc++.h>
#include <tcrand/tree.hpp>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;
using namespace tcrand;
#define fi first
#define se second
#define pb push_back
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;

const int MAXN = 50000;
const int MAXQ = 50000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, Q;
    vector <int> A;
    vector <int> U, V;
    vector <int> O, X;
    vector <long long> ANS;

    void InputFormat() {
        LINE(N, Q);
        LINE(A % SIZE(N));
        LINES(U, V) % SIZE(N-1);
        LINES(O, X) % SIZE(Q);
    }

    void OutputFormat(){
        LINES(ANS) % SIZE(queryCount);
    }

    void GradingConfig() {
        TimeLimit(3);
        MemoryLimit(256);
    }

    int queryCount;

    void BeforeOutputFormat(){
        queryCount = 0;
        for(int i = 0;i < Q;i++){
            queryCount += (O[i] == 2);
        }
    }

    void Constraints() {
        CONS((1 <= N) && (N <= MAXN));
        CONS((1 <= Q) && (Q <= MAXQ));
        CONS(eachElementBetween(A, 0, 1));
        CONS(eachElementBetween(U, 1, N));
        CONS(eachElementBetween(V, 1, N));
        CONS(eachElementBetween(O, 1, 2));
        CONS(eachElementBetween(X, 1, N));
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
            "6 3",
            "1 0 0 1 1 0",
            "1 2",
            "1 3",
            "2 4",
            "2 5",
            "2 6",
            "1 2",
            "2 2",
            "2 1",
        });
        Output({
            "3",
            "0",
        });
    }
    void BeforeTestCase(){
        A.clear();
        U.clear(); V.clear();
        O.clear(); X.clear();
    }

    void TestGroup1(){
        Subtasks({1});
        
        // Testcase 1-5
        CASE(N = 2; Q = 10; U = {2}; V = {1}; randomA(); lowUpdateHighQuery());
        CASE(N = 10; Q = 10; makeTree(); randomA(); lowUpdateHighQuery());
        CASE(N = 69; Q = 100; makeTree(); randomA(1); lowUpdateHighQuery());
        CASE(N = 300; Q = 1000; makeTree(); randomA(); potential());
        CASE(N = rnd.nextInt(MAXN-5000, MAXN); Q = MAXQ; makeTreeDeg(N/100, N/10); randomA(); potential());
        
        // Testcase 6 - 10
        CASE(N = rnd.nextInt(MAXN-5000, MAXN); Q = MAXQ; makeTreeDeg(sqrt(N)-100, sqrt(N)+100); randomA(); lowUpdateHighQuery(0,0,N/5));
        CASE(N = rnd.nextInt(MAXN-5000, MAXN); Q = MAXQ; makeTreeDeg(sqrt(N)-100, sqrt(N)+100); randomA(); lowUpdateHighQuery(0,0,-2));
        CASE(N = rnd.nextInt(MAXN-5000, MAXN); Q = MAXQ; makeTreeDeg(sqrt(N)-100, sqrt(N)+100); randomA(); potential());
        CASE(N = rnd.nextInt(MAXN-5000, MAXN); Q = MAXQ; makeTreeDeg(sqrt(N)-10, sqrt(N)+100); randomA(); potential());
        CASE(N = rnd.nextInt(MAXN-5000, MAXN); Q = MAXQ; makeTreeDeg(sqrt(N)-50, sqrt(N)+1000); randomA(); potential());
        
        // Testcase 11 - 15
        CASE(N = MAXN; Q = MAXQ; makeTree(); randomA(); lowUpdateHighQuery(0,1));
        CASE(N = MAXN; Q = MAXQ; makeTree(); randomA(); potential(-1,0));
        CASE(N = MAXN; Q = MAXQ; makeTreeLeaf(20000); randomA(); potential(-1,0));
        CASE(N = MAXN; Q = MAXQ; makeTreeDep(30000); randomA(); potential(-1,0));
        CASE(N = MAXN; Q = MAXQ; makeChain(1); randomA(); potential());
        
        // Testcase 16-20
        CASE(N = MAXN; Q = MAXQ; makeChain(0); randomA(); potential());
        CASE(N = MAXN; Q = MAXQ; makeCaterpillar(); randomA(); lowUpdateHighQuery(0, 0));
        CASE(N = MAXN; Q = MAXQ; makeCaterpillar(); randomA(); potential());
        CASE(N = MAXN; Q = MAXQ; makeStar(); randomA(); lowUpdateHighQuery(1,0));
        CASE(N = rnd.nextInt(MAXN-5000, MAXN); Q = MAXQ; makeTreeDeg(1,2); randomA(); potential());

        // Testcase 21-30
        // All A = 1
        CASE(N = MAXN; Q = MAXQ; makeTree(); randomA(1); potential(-1,0));
        // Tlekiller = N/2
        CASE(N = MAXN; Q = MAXQ; makeTree(); randomA(); potential(N/2,0,0));
        // Maxtide and depth = 2
        CASE(N = MAXN; Q = MAXQ; makeTree(); randomA(); lowUpdateHighQuery(2,2));
        // All type 2 query
        CASE(N = MAXN; Q = MAXQ; makeTree(); randomA(); potential(0));
        // Update MAXQ-100 times, then query 100 times on random tree
        CASE(N = MAXN; Q = MAXQ; makeTree(); randomA(); potential(MAXQ-100,0,0));
        // Update MAXQ-50 times, then query 50 times on chain tree with random root
        CASE(N = MAXN; Q = MAXQ; makeChain(0); randomA(); potential(MAXQ-300,1,0));
        // Chain tree, Almost-all update, then some query
        CASE(N = MAXN; Q = MAXQ; makeChain(0); randomA(); allUpdate(MAXQ-50); potentialQuery());
        // Chain tree, kill rfpermen's solution 
        CASE(N = MAXN; Q = MAXQ; makeChain(1); randomA(); lowUpdateHighQuery(1,1,1,1,1));
        // Chain tree, kill rfpermen's solution 
        CASE(N = MAXN; Q = MAXQ; makeChain(1); randomA(); lowUpdateHighQuery(1,1,1,2,2));
        // Star tree, kill Bohdan's solution
        CASE(N = MAXN; Q = MAXQ; makeStar(1); randomA(); lowUpdateHighQuery(1,1,1,2,2));

    }

private:

    void shuffleQuery(){
        vector <pii> tmp(Q);
        for(int i = 0;i < Q;i++) tmp[i] = {O[i], X[i]};
        rnd.shuffle(tmp.begin(), tmp.end());
        for(int i = 0;i < Q;i++) O[i] = tmp[i].fi, X[i] = tmp[i].se;
    }

    void shuffleTree(){
        vector<int> idxMap(N);
        iota(idxMap.begin(), idxMap.end(), 0);
        rnd.shuffle(idxMap.begin(), idxMap.end());
        for(int i = 0;i < N-1;i++){
            U[i] = idxMap[U[i]-1]+1;
            V[i] = idxMap[V[i]-1]+1;
        }
    }

    void makeTree(){
        tie(U, V) = TreeRandomizer().node_count(N).index_base(1).next().edges();
        shuffleTree();
    }

    void makeTreeDeg(int loDeg, int hiDeg, int root = 1){
        root = (root == 0 ? rnd.nextInt(1, N) : root);
        tie(U, V) = TreeRandomizer().node_count(N).index_base(1).root(root).child_count(loDeg,hiDeg).next().edges();
    }

    void makeTreeLeaf(int leafCount, int root = 1){
        root = (root == 0 ? rnd.nextInt(1, N) : root);
        tie(U, V) = TreeRandomizer().node_count(N).index_base(1).root(root).leaf_count(leafCount).next().edges();
    }

    void makeTreeDep(int depth, int root = 1){
        root = (root == 0 ? rnd.nextInt(1, N) : root);
        tie(U, V) = TreeRandomizer().node_count(N).index_base(1).root(root).depth(depth).next().edges();
    }

    void makeChain(int root = 1){
        root = (root == 0 ? rnd.nextInt(1, N) : root);
        tie(U, V) = ChainTreeRandomizer().node_count(N).root(root).index_base(1).next().edges();
    }

    void makeCaterpillar(int root = 1){
        root = (root == 0 ? rnd.nextInt(1, N) : root);
        tie(U, V) = CaterpillarTreeRandomizer().node_count(N).root(root).index_base(1).next().edges();
    }

    void makeStar(int root = 1){
        root = (root == 0 ? rnd.nextInt(1, N) : root);
        tie(U, V) = StarTreeRandomizer().node_count(N).root(root).index_base(1).next().edges();
    }

    void randomA(int lowA = 0, int highA = 1){
        A.resize(N);
        for(int i = 0;i < N;i++) A[i] = rnd.nextInt(lowA, highA);
    }

    template <class T>
    inline T pickRandom(const vector<T>&V){ return V[rnd.nextInt((int)(V.size()))]; }

    /**
     * Make update on node with distance <= maxTide from closest leaf
     * and query on node with distance <= maxDepth from root
     * both is 1 based.
     * In particular, maxDepth = 1 : root only, maxTide = 1 : leaf only
     * @param maxDepth | > 0 if custom, 0 if all, else treeDepth/5
     * @param maxTide | > 0 if custom, 0 if all, else treeTide/5
     * @param tleKiller | if 0, random, if -1 alternating| else updates first, and the value last is query
     */
    void lowUpdateHighQuery(int maxDepth = 0, int maxTide = 0, int tleKiller = 0, int lowO = 1, int highO = 2){
        O.resize(Q); X.resize(Q);

        vvi edge(N+1);
        vi depth(N+1), tide(N+1);
        vi order = {1};

        int levelSize = 0;
        
        depth[1] = 1;

        for(int i = 0;i < N-1;i++){
            edge[U[i]].pb(V[i]);
            edge[V[i]].pb(U[i]);
        }

        for(int i = 0;i < N;i++){
            int pos = order[i];
            levelSize = max(levelSize, depth[pos]);
            for(auto &nx : edge[pos]){
                if(!depth[nx]){
                    depth[nx] = depth[pos]+1;
                    order.pb(nx);
                }
            }
        }

        // cout << levelSize << endl;

        for(int i = N-1;i >= 0;i--){
            int pos = order[i];
            for(auto &nx : edge[pos])
                tide[pos] = max(tide[pos], tide[nx]);
            tide[pos]++;
        }

        vvi levelDepth(levelSize+1), levelTide(levelSize+1);

        for(int i = 1;i <= N;i++){
            levelDepth[depth[i]].pb(i);
            levelTide[tide[i]].pb(i);
        }

        if(maxDepth > 0) maxDepth = min(maxDepth, levelSize);
        else if(maxDepth == 0) maxDepth = levelSize;
        else maxDepth = max(1, levelSize/5);

        if(maxTide > 0) maxTide = min(maxTide, levelSize);
        else if(maxTide == 0) maxTide = levelSize;
        else maxTide = max(1, levelSize/5);


        for(int i = 0;i < Q;i++){
            O[i] = rnd.nextInt(lowO, highO);
            if(tleKiller > 0) O[i] = (i >= Q-tleKiller ? 2 : 1);
            else if(tleKiller == -1) O[i] = (i%2)+1;
            if(O[i] == 1) X[i] = pickRandom(levelTide[rnd.nextInt(maxTide)+1]);
            else X[i] = pickRandom(levelDepth[rnd.nextInt(maxDepth)+1]);
        }
    }

    void potentialQuery(int self = 1){

        vvi edge(N+1);
        vi subsz(N+1);
        vector <pii> potAns(N+1);

        for(int i = 0;i < N-1;i++){
            edge[U[i]].pb(V[i]);
            edge[V[i]].pb(U[i]);
        }
        function<void(int, int)> dfs = [&](int pos, int par){
            subsz[pos]++;
            potAns[pos] = {0, pos};
            trav(nx, edge[pos]){
                if(nx == par) continue;
                dfs(nx, pos);
                potAns[pos].fi += subsz[pos]*subsz[nx];
                subsz[pos] += subsz[nx];
            }
        };
        dfs(1, -1);
        if(!self) for(int i = 1;i <= N;i++) potAns[i].fi -= subsz[i]-1;

        // Sort by potential answer
        sort(potAns.begin(), potAns.end(), [](pii a, pii b){
            if(a.fi != b.fi) return a.fi < b.fi;
            return a.se < b.se;
        });

        if(!self) while(potAns.size() && potAns.back().fi == 0) potAns.pop_back();

        assert(potAns.size() > 0);

        int m = potAns.size();
        vector <ll> distribution(m);

        for(int i = 0;i < m;i++) distribution[i] = (i == 0 ? 0 : distribution[i-1])+potAns[i].fi;

        while(O.size() < Q){
            O.pb(2);

            // Get distribution using prefix sum
            ll curVal = rnd.nextLongLong(1, distribution.back());

            ll curPos = lower_bound(distribution.begin(), distribution.end(), curVal) - distribution.begin();

            X.pb(potAns[curPos].se);

        }
    }

    void potentialUpdate(int uCount = -1){
        if(uCount == -1) uCount = rnd.nextInt(1, Q);
        vvi edge(N+1);

        // cerr << "Here" << endl;
        vector <pii> potAns(N+1);
        for(int i = 0;i < N-1;i++){
            edge[U[i]].pb(V[i]);
            edge[V[i]].pb(U[i]);
        }

        function<void(int, int)> dfs = [&](int pos, int par){
            potAns[pos] = {(par == -1 ? 1 : potAns[par].fi+1), pos};
            trav(nx, edge[pos]){
                if(nx == par) continue;
                dfs(nx, pos);
            }
        };
        // cerr << "Here" << endl;

        dfs(1, -1);

        // Sort by potential answer
        sort(potAns.begin(), potAns.end(), [](pii a, pii b){
            if(a.fi != b.fi) return a.fi < b.fi;
            return a.se < b.se;
        });

        int m = potAns.size();
        vector <ll> distribution(m);

        for(int i = 0;i < m;i++) distribution[i] = (i == 0 ? 0 : distribution[i-1])+potAns[i].fi;

        while(O.size() < uCount){
            O.pb(1);

            // Get distribution using prefix sum
            ll curVal = rnd.nextLongLong(1, distribution.back());

            int curPos = lower_bound(distribution.begin(), distribution.end(), curVal) - distribution.begin();

            X.pb(potAns[curPos].se);
            // cout << curVal << endl;
            // cout << "Here is " << potAns[curPos].se << endl;
        }
    }

    void potential(int uCount = -1, int self = 1, bool shuffle = 1){
        if(uCount == -1) uCount = rnd.nextInt((2*Q/5), (3*Q/5));
        assert(0 <= uCount && uCount <= Q);
        // cerr << "making update";
        potentialUpdate(uCount);
        // cerr << "update finish";
        // cerr << "making query";
        potentialQuery(self);
        // cerr << ", query finish ";
        if(shuffle) shuffleQuery();
    }

    void allUpdate(int uCount){
        O.resize(uCount, 1);
        X.resize(N);
        iota(X.begin(), X.end(), 1);
        rnd.shuffle(X.begin(), X.end());
        while(X.size() > uCount) X.pop_back();
    }
};
