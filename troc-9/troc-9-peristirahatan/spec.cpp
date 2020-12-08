#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;
typedef long long LL;
#define pb push_back
const LL LINF = 4557430888798830399LL;
const LL MAXN = 100000;
const LL MAXQ = 100000;
const LL MAXA = 1000000000LL;
const LL STRESSCONST = 1000;
const LL MAXC = 10000;
const LL SHORTCONST = 10;
const LL MEDIUMCONST = 100;
// const LL MAXN = 100;
// const LL MAXQ = 100;
// const LL MAXA = 1000000LL;
// const LL MAXC = 10000;
// const LL STRESSCONST = 5;
// const LL SHORTCONST = 5;
// const LL MEDIUMCONST = 10;

class ProblemSpec : public BaseProblemSpec {
protected:
    LL N,Q;
    vector <LL> A;
    vector <LL> T,X,Y,Z;
    vector <LL> ANS;
    void InputFormat() {
        LINE(N,Q);
        LINE(A % SIZE(N));
        LINES(T,X,Y,Z) % SIZE(Q);
    }

    int query_count;
    void BeforeOutputFormat() {
        query_count = 0;
        for (int i = 0; i < Q; ++i){
            if(T[i] == 2) query_count++;
        }
    }

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
        CONS(eachElementBetween(A,1,MAXA));
        CONS(eachElementBetween(T,1,2));
        CONS(eachElementBetween(X,1,N));
        CONS(eachElementBetween(Y,1,N));
        CONS(YisBiggerThanX(X,Y));
        CONS(eachUpdateBetween(T,Z,N,MAXC));
    }

    void Subtask1(){
        Points(100);
    }



private:
    bool eachElementBetween(const vector<LL>&V,LL lo, LL hi){
        for(int i = 0;i < V.size();i++){
            if(lo <= V[i] && V[i] <= hi) continue;
            else return 0;
        }
        return 1;
    }
    bool YisBiggerThanX(const vector<LL>&X,const vector<LL>&Y){
        for(int i = 0;i < X.size();i++){
            if(X[i] > Y[i]) return 0;
        }
        return 1;
    }
    bool eachUpdateBetween(const vector<LL>&T, const vector<LL>&Z, LL N,LL C){
        for(int i = 0;i < T.size();i++){
            if(T[i] == 1){
                if(!(1 <= Z[i] && Z[i] <= C)) return 0;
            }else{
                if(!(1 <= Z[i] && Z[i] <= N)) return 0;
            }
        }
        return 1;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1});
        Input({
            "5 3",
            "2 2 3 2 1",
            "2 1 5 3",
            "1 3 5 5",
            "2 2 4 5",
        });
        Output({
            "1",
            "5",
        });
    }
    void BeforeTestCase(){
        A.clear();
        T.clear();
        X.clear();
        Y.clear();
        Z.clear();
    }
    void TestGroup1(){
        Subtasks({1});
        CASE(N = 10; Q = 10; RandomInitialArray(N); RandomQueries(N,Q));
        CASE(N = rnd.nextInt(1,MAXN);Q = rnd.nextInt(1,MAXQ);RandomInitialArray(N);RandomQueries(N,Q));

        CASE(N = MAXN; Q = MAXQ;RandomInitialArray(N);NoUpdQueries(N,Q));

        CASE(N = MAXN; Q = MAXQ;DecrInitialArray(N);RandomQueries(N,Q));
        CASE(N = MAXN; Q = MAXQ;IncrInitialArray(N);RandomQueries(N,Q));

        CASE(N = MAXN; Q = MAXQ;TrenchInitialArray(N);NoUpdQueries(N,Q));
        CASE(N = MAXN; Q = MAXQ;TrenchInitialArray(N);RandomQueries(N,Q));
    
        CASE(N = MAXN; Q = MAXQ;RandomInitialArray(N);PointQueries(N,Q));

        CASE(N = MAXN; Q = MAXQ;RandomInitialArray(N);ShortQueries(N,Q));
        CASE(N = MAXN; Q = MAXQ;RandomInitialArray(N);MediumQueries(N,Q));
        
        CASE(N = MAXN; Q = MAXQ;TrenchInitialArray(N);InsideQueries(N,Q));
        CASE(N = MAXN; Q = MAXQ;RandomInitialArray(N);InsideQueries(N,Q));

        CASE(N = MAXN; Q = MAXQ;RandomInitialArray(N);NoInsideQueries(N,Q));
        CASE(N = MAXN; Q = MAXQ;DecrInitialArray(N);NoInsideQueries(N,Q));
        CASE(N = MAXN; Q = MAXQ;IncrInitialArray(N);NoInsideQueries(N,Q));
        CASE(N = MAXN; Q = MAXQ;TrenchInitialArray(N);NoInsideQueries(N,Q));

        CASE(N = MAXN; Q = MAXQ;BigStressArray(N);BigStressUpdates(N,Q));
        CASE(N = MAXN; Q = MAXQ;BigStressArray(N);BigStressQueries(N,Q));
    }

private:
    void RandomInitialArray(LL N){
        for(int i = 1;i <= N;i++){
            A.pb(rnd.nextInt(1,MAXA));
        }
    }
    void DecrInitialArray(LL N){
        RandomInitialArray(N);
        sort(A.begin(),A.end(),greater<LL>());
    }
    void IncrInitialArray(LL N){
        RandomInitialArray(N);
        sort(A.begin(),A.end());
    }
    void TrenchInitialArray(LL N){
        RandomInitialArray(N);
        LL mid = rnd.nextInt(0,N-1);
        vector <LL> V; vector <LL> Vp;
        for(int i = 0;i <= mid;i++){
            V.pb(A[i]);
        }
        for(int i = mid+1;i <= N-1;i++){
            Vp.pb(A[i]);
        }
        sort(V.begin(),V.end(),greater<LL>());
        sort(Vp.begin(),Vp.end());
        for(int i = 0;i < Vp.size();i++) V.pb(Vp[i]);
        swap(A,V);
    }
    void BigStressArray(LL N){
        for(int i = 1;i <= N;i++){
            A.pb(rnd.nextInt(MAXA-STRESSCONST,MAXA));
        }
    }
    void RandomQueries(LL N,LL Q){
        for(int i = 1;i <= Q;i++){
            LL tipe = rnd.nextInt(1,2);
            if(tipe == 1){
                LL kiri = rnd.nextInt(1,N);
                LL kanan = rnd.nextInt(1,N);
                if(kiri > kanan) swap(kiri,kanan);
                LL val = rnd.nextInt(1,MAXC);
                T.pb(1); X.pb(kiri); Y.pb(kanan); Z.pb(val);
            }else{
                LL kiri = rnd.nextInt(1,N);
                LL kanan = rnd.nextInt(1,N);
                if(kiri > kanan) swap(kiri,kanan);
                LL val = rnd.nextInt(1,N);
                T.pb(2); X.pb(kiri); Y.pb(kanan); Z.pb(val);
            }
        }
    }
    void NoUpdQueries(LL N, LL Q){
        for(int i = 1;i <= Q;i++){
            LL kiri = rnd.nextInt(1,N);
            LL kanan = rnd.nextInt(1,N);
            if(kiri > kanan) swap(kiri,kanan);
            LL val = rnd.nextInt(1,N);
            T.pb(2); X.pb(kiri); Y.pb(kanan); Z.pb(val);
        }
    }
    void InsideQueries(LL N,LL Q){
        for(int i = 1;i <= Q;i++){
            LL tipe = rnd.nextInt(1,2);
            if(tipe == 1){
                LL kiri = rnd.nextInt(1,N);
                LL kanan = rnd.nextInt(1,N);
                if(kiri > kanan) swap(kiri,kanan);
                LL val = rnd.nextInt(1,MAXC);
                T.pb(1); X.pb(kiri); Y.pb(kanan); Z.pb(val);
            }else{
                LL kiri = rnd.nextInt(1,N);
                LL kanan = rnd.nextInt(1,N);
                if(kiri > kanan) swap(kiri,kanan);
                LL val = rnd.nextInt(kiri,kanan);
                T.pb(2); X.pb(kiri); Y.pb(kanan); Z.pb(val);
            }
        }
    }
    void NoInsideQueries(LL N,LL Q){
        for(int i = 1;i <= Q;i++){
            LL tipe = rnd.nextInt(1,2);
            if(tipe == 1){
                LL kiri = rnd.nextInt(1,N);
                LL kanan = rnd.nextInt(1,N);
                if(kiri > kanan) swap(kiri,kanan);
                LL val = rnd.nextInt(1,MAXC);
                T.pb(1); X.pb(kiri); Y.pb(kanan); Z.pb(val);
            }else{
                LL kiri = rnd.nextInt(1,N);
                LL kanan = rnd.nextInt(1,N);
                if(kiri > kanan) swap(kiri,kanan);
                if(kiri == 1 && kanan == N){
                    if(rnd.nextInt(0,1)) kiri++;
                    else kanan--;
                }
                LL val = rnd.nextInt(1,N-(kanan-kiri+1));
                if(val >= kiri) val += (kanan-kiri+1);
                T.pb(2); X.pb(kiri); Y.pb(kanan); Z.pb(val);
            }
        }
    }
    void PointQueries(LL N, LL Q){
        for(int i = 1;i <= Q;i++){
            LL tipe = rnd.nextInt(1,2);
            if(tipe == 1){
                LL kiri = rnd.nextInt(1,N);
                LL kanan = rnd.nextInt(1,N);
                if(kiri > kanan) swap(kiri,kanan);
                LL val = rnd.nextInt(1,MAXC);
                T.pb(1); X.pb(kiri); Y.pb(kanan); Z.pb(val);
            }else{
                LL tar = rnd.nextInt(1,N);
                LL val = rnd.nextInt(1,N);
                T.pb(2); X.pb(tar); Y.pb(tar); Z.pb(val);
            }
        }
    }
    void ShortQueries(LL N,LL Q){
        for(int i = 1;i <= Q;i++){
            LL tipe = rnd.nextInt(1,2);
            if(tipe == 1){
                LL kiri = rnd.nextInt(1,N);
                LL kanan = min(N,kiri+rnd.nextInt(0,SHORTCONST-1));
                LL val = rnd.nextInt(1,MAXC);
                T.pb(1); X.pb(kiri); Y.pb(kanan); Z.pb(val);
            }else{
                LL kiri = rnd.nextInt(1,N);
                LL kanan = min(N,kiri+rnd.nextInt(0,SHORTCONST-1));
                LL val = rnd.nextInt(1,N);
                T.pb(2); X.pb(kiri); Y.pb(kanan); Z.pb(val);
            }
        }
    }
    void MediumQueries(LL N,LL Q){
        for(int i = 1;i <= Q;i++){
            LL tipe = rnd.nextInt(1,2);
            if(tipe == 1){
                LL kiri = rnd.nextInt(1,N);
                LL kanan = min(N,kiri+rnd.nextInt(0,MEDIUMCONST-1));
                LL val = rnd.nextInt(1,MAXC);
                T.pb(1); X.pb(kiri); Y.pb(kanan); Z.pb(val);
            }else{
                LL kiri = rnd.nextInt(1,N);
                LL kanan = min(N,kiri+rnd.nextInt(0,MEDIUMCONST-1));
                LL val = rnd.nextInt(1,N);
                T.pb(2); X.pb(kiri); Y.pb(kanan); Z.pb(val);
            }
        }

    }
    void BigStressQueries(LL N, LL Q){
        for(int i = 1;i <= Q;i++){
            LL tipe = rnd.nextInt(1,2);
            if(tipe == 1){
                LL kiri = 1; LL kanan = N;
                if(kiri > kanan) swap(kiri,kanan);
                LL val = rnd.nextInt(MAXC-STRESSCONST,MAXC);
                T.pb(1); X.pb(kiri); Y.pb(kanan); Z.pb(val);
            }else{
                LL kiri = rnd.nextInt(1,N);
                LL kanan = rnd.nextInt(1,N);
                if(kiri > kanan) swap(kiri,kanan);
                LL val = rnd.nextInt(1,N);
                T.pb(2); X.pb(kiri); Y.pb(kanan); Z.pb(val);
            }
        }
    }
    void BigStressUpdates(LL N,LL Q){
        for(int i = 1;i <= Q-STRESSCONST;i++){
            LL kiri = 1; LL kanan = N;
            if(kiri > kanan) swap(kiri,kanan);
            LL val = rnd.nextInt(MAXC-STRESSCONST,MAXC);
            T.pb(1); X.pb(kiri); Y.pb(kanan); Z.pb(val);
        }
        for(int i = Q-STRESSCONST+1;i <= Q;i++){
            LL kiri = rnd.nextInt(1,N);
            LL kanan = rnd.nextInt(1,N);
            if(kiri > kanan) swap(kiri,kanan);
            LL val = rnd.nextInt(1,N);
            T.pb(2); X.pb(kiri); Y.pb(kanan); Z.pb(val);
        }
    }
};
