#include <tcframe/spec.hpp>
using namespace tcframe;

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 20000;
const int MAXM = 50000;
const int MAXK = 15;
const long long MAXS = 1e18;
const int MAXW = 50000;
const long long MAXC = 1e18;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, M, K;
    vector<long long> S;
    vector<int> U;
    vector<int> V;
    vector<int> W;
    vector<int> P;
    vector<long long> C;
    long long ANS;
    void InputFormat() {
        LINE(N, M, K);
        LINE(S % SIZE(N));
        LINES(U, V, W) % SIZE(M);
        LINES(P, C) % SIZE(K);
    }

    void OutputFormat() {
        LINE(ANS);
    }

    void GradingConfig() {
        TimeLimit(3);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= N && N <= MAXN);
        CONS(N - 1 <= M && M <= MAXM);
        CONS(1 <= K && K <= MAXK);
        CONS(inRange<long long>(S, 0, MAXS));
        CONS(inRange<int>(U, 1, N));
        CONS(inRange<int>(V, 1, N));
        CONS(inRange<int>(W, 1, MAXW));
        CONS(inRange<int>(P, 1, N));
        CONS(inRange<long long>(C, 0, MAXC));
        CONS(isConnected());
        CONS(isSimpleGraph());
        CONS(sum(S, MAXS));
        CONS(sum(C, MAXC));
    }

    void Subtask1(){

    }
private:

    bool sum(const vector<long long> &v, long long maks){
        long long ret = 0;
        for(auto i : v){
            if(ret + i > maks || ret > maks || i > maks)
                return false;
            ret += i;
        }
        return true;
    }

    bool isSimpleGraph(){
        set<pair<int, int>> edge;
        for(int i = 0; i < M; i++){
            edge.insert({U[i], V[i]});
            edge.insert({V[i], U[i]});
        }
        return (int)edge.size() == M * 2;
    }

    bool isConnected(){
        vector<int> visit(N, 0);
        vector<vector<int>> g(N);
        for(int i = 0; i < M; i++){
            g[U[i] - 1].push_back(V[i] - 1);
            g[V[i] - 1].push_back(U[i] - 1);
        }
        queue<int> q;
        q.push(0);
        visit[0] = 1;
        while(!q.empty()){
            int now = q.front();
            q.pop();
            for(int i : g[now]){
                if(!visit[i]){
                    visit[i] = 1;
                    q.push(i);
                }
            }
        }
        for(int i = 0; i < N; i++)
            if(!visit[i])
                return false;
        return true;
    }

    template<class T>
    bool inRange(const vector<T> &v, T lo, T hi){
        for(auto i : v)
            if(i > hi || i < lo)
                return false;
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1});
        Input({
            "6 10 3",
            "1 2 3 4 5 6",
            "4 1 3",
            "3 2 7",
            "4 3 3",
            "4 5 5",
            "4 6 6",
            "5 6 2",
            "1 2 1",
            "1 3 1",
            "3 5 8",
            "6 2 9",
            "1 10",
            "2 5",
            "3 6"
        });
        Output({
            "9"
        });
    }


    void TestGroup1() {
        Subtasks({1});

        for(int i = 0; i < 5; i++)
            CASE(N = MAXN, M = N - 1, K = 15, tie(U, V, W) = generateConnectedGraph(N, M), tie(P, C) = generateRumahSakit(K, 100000, N), S = generatePasien(N, 100000));
        for(int i = 0; i < 5; i++)
            CASE(N = MAXN, M = MAXM, K = 15, tie(U, V, W) = generateConnectedGraph(N, M), tie(P, C) = generateRumahSakit(K, 100000, N), S = generatePasien(N, 100000));
        for(int i = 0; i < 5; i++)
            CASE(N = MAXN, M = N - 1, K = 15, tie(U, V, W) = generateConnectedGraph(N, M), tie(P, C) = generateRumahSakit(K, rnd.nextLongLong(0, MAXC), N), S = generatePasien(N, rnd.nextLongLong(0, MAXC)));
        for(int i = 0; i < 5; i++)
            CASE(N = MAXN, M = MAXM, K = 15, tie(U, V, W) = generateConnectedGraph(N, M), tie(P, C) = generateRumahSakit(K, MAXC, N), S = generatePasien(N, MAXS));
        for(int i = 0; i < 5; i++)
            CASE(N = MAXN, M = rnd.nextInt(N - 1, MAXM), K = 15, tie(U, V, W) = generateConnectedGraph(N, M), tie(P, C) = generateRumahSakit(K, rnd.nextLongLong(0, MAXC), N), S = generatePasien(N, rnd.nextLongLong(0, MAXS)));
        for(int i = 0; i < 5; i++)
            CASE(N = rnd.nextInt(10000, MAXN), M = rnd.nextInt(N - 1, MAXM), K = rnd.nextInt(1, MAXK), tie(U, V, W) = generateConnectedGraph(N, M), tie(P, C) = generateRumahSakit(K, MAXC, N), S = generatePasien(N, MAXS));
        for(int i = 0; i < 5; i++)
            CASE(N = rnd.nextInt(10000, MAXN), M = rnd.nextInt(N - 1, MAXM), K = rnd.nextInt(1, MAXK), tie(U, V, W) = generateConnectedGraph(N, M), tie(P, C) = generateRumahSakit(K, rnd.nextLongLong(0, MAXC), N), S = generatePasien(N, rnd.nextLongLong(0, MAXS)));
        for(int i = 0; i < 5; i++)
            CASE(N = rnd.nextInt(10000, MAXN), M = rnd.nextInt(N - 1, MAXM), K = 15, tie(U, V, W) = generateConnectedGraph(N, M), tie(P, C, S) = jawabanNol(N, K, rnd.nextLongLong(MAXS / 2, MAXS)));
        for(int i = 0; i < 5; i++)
            CASE(N = rnd.nextInt(10000, MAXN), M = rnd.nextInt(N - 1, MAXM), K = 15, tie(U, V, W) = generateConnectedGraph(N, M), tie(P, C) = generateRumahSakit(K, rnd.nextLongLong(0, MAXC), N), S = pasienCumaAdaDiSatuKota(N, rnd.nextLongLong(0, MAXS)));
        CASE(N = MAXN, M = rnd.nextInt(N-1, MAXM), K = 1, tie(U, V, W) = generateConnectedGraph(N, M), tie(P, C) = generateRumahSakit(K, MAXC, N), S = generatePasien(N, MAXS));

    }  

 private:

    vector<long long> pasienCumaAdaDiSatuKota(int n, long long sum){
        vector<long long> s(n, 0);
        s[rnd.nextInt(0, n - 1)] = sum;
        return s;
    }

    tuple<vector<int>, vector<long long>, vector<long long>> jawabanNol(int n, int k, long long sum){
        vector<int> node(n), p(k);
        vector<long long> c(k), s(n, 0);
        iota(node.begin(), node.end(), 1);
        rnd.shuffle(node.begin(), node.end());
        for(int i = 0; i < k; i++){
            p[i] = node[i];
        }
        vector<long long> point(k + 1);
        for(int i = 0; i < k - 1; i++){
            point[i] = rnd.nextLongLong(0, sum);
        }
        point[k - 1] = 0;
        point[k] = sum;
        sort(point.begin(), point.end());
        for(int i = 0; i < k; i++){
            c[i] = point[i + 1] - point[i];
            s[p[i] - 1] = c[i];
        }
        return make_tuple(p, c, s);
    }

    vector<long long> generatePasien(int n, long long sum){
        vector<long long> ret(n);
        vector<long long> point(n + 1);
        for(int  i = 0; i < n - 1; i++){
            point[i] = rnd.nextLongLong(0, sum);
        }
        point[n - 1] = sum;
        point[n] = 0;
        sort(point.begin(), point.end());
        for(int i = 0; i < n; i++){
            ret[i] = point[i + 1] - point[i];
        }
        rnd.shuffle(ret.begin(), ret.end());
        return ret;
    }

    tuple<vector<int>, vector<long long>> generateRumahSakit(int k, long long sum, int n){
        vector<int> p(k), node(n);
        vector<long long> c(k), point(k + 1);
        iota(node.begin(), node.end(), 1);
        rnd.shuffle(node.begin(), node.end());
        for(int i = 0; i < k; i++){
            p[i] = node[i];
        }
        rnd.shuffle(c.begin(), c.end());

        for(int i = 0; i < k - 1; i++){
            point[i] = rnd.nextLongLong(0, sum);
        }
        point[k - 1] = 0;
        point[k] = sum;
        sort(point.begin(), point.end());
        for(int i = 0; i < k; i++){
            c[i] = point[i + 1] - point[i];
        }
        return make_tuple(p, c);
    }

    tuple<vector<int>, vector<int>, vector<int>> generateConnectedGraph(int n, int m){
        set<pair<int, int>> ada;
        vector<int> node(n), u(m), v(m), w(m);
        iota(node.begin(), node.end(), 1);
        rnd.shuffle(node.begin(), node.end());
        for(int i = 0; i < n - 1; i++){
            v[i] = i + 1;
            u[i] = rnd.nextInt(0, i);
            ada.insert({u[i], v[i]});
            ada.insert({v[i], u[i]});
        }
        for(int i = n - 1; i < m; i++){
            while(1){
                int x = rnd.nextInt(0, n - 1);
                int y = rnd.nextInt(0, n - 1);
                if(x != y && !ada.count({x, y})){
                    ada.insert({x, y});
                    ada.insert({y, x});
                    u[i] = x;
                    v[i] = y;
                    break;
                }
            }
        }
        for(int i = 0; i < m; i++)
            w[i] = rnd.nextInt(1, MAXW);
        for(int i = 0; i < m; i++){
            u[i] = node[u[i]];
            v[i] = node[v[i]];
        }
        return make_tuple(u, v, w);
    }

};
