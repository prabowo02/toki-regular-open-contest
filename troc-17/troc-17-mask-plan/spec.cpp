#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
#define fi first
#define se second

using namespace std;
using namespace tcframe;
typedef long long LL;
typedef pair<int, int> pii;

const LL MAXN = 200000;
const LL MAXQ = 200000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N,Q,D;
    string S;
    vector <int> T, X;
    vector <int> ANS;
    void InputFormat() {
        LINE(N,D);
        LINE(S);
        LINE(Q);
        LINES(T,X) % SIZE(Q);
    }

    int query_count;
    void BeforeOutputFormat() { query_count = count(T.begin(), T.end(), 2); }

    void OutputFormat(){
        LINES(ANS) % SIZE(query_count);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS((1 <= N) && (N <= MAXN));
        CONS((1 <= Q) && (Q <= MAXQ));
        CONS((1 <= D) && (D <= N));
        CONS((int)S.length() == N);
        CONS(eachElementBetween(T,1,2));
        CONS(eachElementBetween(S,'0','1'));
        CONS(isValidQuery(T,X,N,D));
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
    bool eachElementBetween(string &S, char lo, char hi){
        for(char x : S) if(x < lo || hi < x) return false;
        return true;
    }
    bool isValidQuery(const vector<int> &T, const vector<int> &X, int N, int D){
        for(int i = 0;i < T.size();i++){
            if(T[i] == 1 && !(1 <= X[i] && X[i] <= N)) return false;
            if(T[i] == 2 && !(1 <= X[i] && X[i] <= N)) return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1});
        Input({
            "5 4",
            "10111",
            "5",
            "2 2",
            "2 3",
            "1 2",
            "2 2",
            "2 3",
        });
        Output({
            "4",
            "-1",
            "3",
            "4",
        });
    }
    void SampleTestCase2() {
        Subtasks({1});
        Input({
            "13 4",
            "1001001001001",
            "2",
            "2 1",
            "2 2",
        });
        Output({
            "4",
            "-1"
        });
    }
    void SampleTestCase3() {
        Subtasks({1});
        Input({
            "5 3",
            "00000",
            "5",
            "2 1",
            "1 2",
            "2 1",
            "1 5",
            "2 1",
        });
        Output({
            "-1",
            "-1",
            "-1",
        });
    }
    
    void BeforeTestCase(){
        S = ""; T.clear(); X.clear();
    }

    void TestGroup1(){
        Subtasks({1});

        CASE(N = 4; D = 1; Q = 3; S = "1111", generateRandomQueries());
        CASE(N = 10; D = 4; S = "1010110111"; allAsk());
        CASE(N = 5; D = 2; Q = 5; S = "11111"; generateRandomQueries(2));
        CASE(N = 10; D = 5; Q = 10; S = "1101010110"; generateRandomQueries(3));
        CASE(N = 100; D = N; Q = 100; generateRandomS(4*N/5); generateRandomQueries(Q/2));
        CASE(N = 1000; D = 64; Q = MAXQ; generateRandomS(152); generateRandomQueries(Q/2));
        CASE(N = 1000; D = 32; Q = MAXQ; generateRandomS(372); generateRandomQueries(Q/2));
        CASE(N = 1000; Q = MAXQ; periodS(); generateRandomQueries(Q/2)); 
        CASE(N = MAXN; D = 11450; Q = MAXQ; generateRandomS(16855); generateRandomQueries());
        CASE(N = MAXN; D = 5817; Q = MAXQ; generateRandomS(65702); generateRandomQueries());
        CASE(N = MAXN; Q = MAXQ; periodS(); generateRandomQueries(6*Q/7)); 
        CASE(N = MAXN; D = 69420; Q = MAXQ; generateRandomS(); generateRandomQueries(1));
        CASE(N = MAXN; D = N/2; Q = MAXQ; generateRandomS(); generateRandomQueries(Q));
        // stressTest();
    }

    void stressTest(){
        for(int i = 1;i <= 100;i++)
            CASE(N = MAXN; D = rnd.nextInt(2, N); Q = MAXQ; generateRandomS(); generateRandomQueries());
    }

private:
    void generateRandomS(int use = -1){
        
        if(!(0 <= use && use <= N)){
            use = rnd.nextInt(0, N);
        }

        for(int i = 0;i < N;i++) S += (i < use ? '1' : '0');

        rnd.shuffle(S.begin(), S.end());
    }

    void periodS(){
        D = sqrt(N);
        for(int i = 1;S.length() < N;i++){
            for(int j = 0;j < D;j++){
                S += (j < i ? '1' : '0');
                if(S.length() == N) break;
            }
        }
    }

    void generateRandomQueries(int ask = -1){
        
        if(!(0 <= ask && ask <= Q)) ask = rnd.nextInt(0, Q);
        vector <pii> queries(Q);

        for(int i = 0;i < Q;i++){
            pii &current = queries[i];
            current.fi = (i < ask ? 2 : 1);
            if(current.fi == 1) current.se = rnd.nextInt(1, N);
            if(current.fi == 2){
                // This has been asserted and proven to exist
                if(rnd.nextInt(1, 5000) == 1) current.se = rnd.nextInt(D, N);
                else current.se = rnd.nextInt(1, max(1, D-1));
            }
        }

        rnd.shuffle(queries.begin(), queries.end());

        T.resize(Q); X.resize(Q);

        for(int i = 0;i < Q;i++){
            T[i] = queries[i].fi;
            X[i] = queries[i].se;
        }
    }

    void allAsk(){
        Q = D-1; T.resize(Q); X.resize(Q);
        for(int i = 1;i < D;i++) T[i-1] = 2, X[i-1] = i;
    }
    
};
