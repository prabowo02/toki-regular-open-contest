#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;
typedef int LL;
typedef pair<LL,LL> PLL;
typedef vector<vector<LL>> grid;
#define fi first
#define se second
#define pb push_back
const LL MAXN = 500;
const LL MAXA = 100000;
const LL MAXQ = 100000;

class ProblemSpec : public BaseProblemSpec {
protected:
    LL N,M,Q;
    vector<vector<LL>> A;
    vector<LL> X,Y,L;
    vector<LL> ANS;
    void InputFormat() {
        LINE(N,M,Q);
        GRID(A)%SIZE(N,M);
        LINES(X,Y,L)%SIZE(Q);
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
        CONS((1 <= M) && (M <= MAXN));
        CONS((1 <= Q) && (Q <= MAXQ));
        CONS(eachElementBetween(X,1,N));
        CONS(eachElementBetween(Y,1,M));
        CONS(eachElementBetween(L,1,MAXQ));
        CONS(eachGridBetween(A,1,MAXA));
        CONS(eachQueryValueSafe(A,X,Y,L));
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
    bool eachQueryValueSafe(const vector<vector<LL>>&A,const vector<LL>&X,const vector<LL>&Y,const vector<LL>&L){
        for(int i = 0;i < L.size();i++){
            if(A[X[i]-1][Y[i]-1] > L[i]) return 0;
        }
        return 1;
    }
    bool eachGridBetween(const vector<vector<LL>>&V,LL lo, LL hi){
        for(int i = 0;i < V.size();i++){
            for(int j = 0;j < V[i].size();j++){
                if(lo <= V[i][j] && V[i][j] <= hi) continue;
                return 0;
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
            "3 3 6",
            "5 6 4",
            "3 2 4",
            "3 1 5",
            "3 2 1",
            "2 2 2",
            "3 1 3",
            "2 3 4",
            "1 1 5",
            "3 3 10"
        });
        Output({
            "3",
            "2",
            "1",
            "1",
            "0",
            "0"
        });
    }
    void SampleTestCase2() {
        Subtasks({1});
        Input({
            "2 3 2",
            "5 5 5",
            "5 5 5",
            "2 3 5",
            "2 3 6",
        });
        Output({
            "0",
            "0",
        });
    }
    void BeforeTestCase(){
        A.clear(); X.clear();
        Y.clear(); L.clear();
    }
    void TestGroup1(){
        Subtasks({1});
        CASE(N = 5,M = 5,RandGrid(1,1000),AllQ(1000));
        CASE(N = 10,M = 10,Q = 100000,MakeMaze());
        CASE(N = 10,M = 10,Q = 100000,FlipMaze());
        CASE(N = 100,M = 100,Q = 100000,RandGrid(),RandQ());
        CASE(N = 500,M = 500,Q = 100000,RandGrid(),RandQ());
        CASE(N = 500,M = 500,Q = 100000,ThinCase(10));
        CASE(N = 500,M = 500,Q = 100000,ThinCase(200));
        CASE(N = 500,M = 500,Q = 100000,ThinCase(3000));
        CASE(N = rnd.nextInt(300,500),M = rnd.nextInt(450,500),Q = 100000,RandGrid(),RandQ());
        CASE(N = rnd.nextInt(450,500),M = rnd.nextInt(300,500),Q = 100000,RandGrid(),RandQ());
        CASE(N = 500,M = 500,Q = 100000,RandGrid(MAXA-1000,MAXA),RandQ(MAXA-5000,MAXA));
        CASE(N = rnd.nextInt(3,10), M = 500,Q = 100000,RandGrid(),RandQ());
        CASE(N = 500, M = rnd.nextInt(3,10),Q = 100000,RandGrid(),RandQ());
        CASE(N = 500,M = 500,Q = 100000,BipartiteGrid(),RandQ());
        CASE(N = 500,M = 500,Q = 100000,ThinCase(0));
        CASE(N = 500,M = 500,Q = 100000,MakeMaze());
        CASE(N = 500,M = 500,Q = 100000,FlipMaze());
        CASE(N = rnd.nextInt(450,500),M = rnd.nextInt(300,500),Q = 100000,MakeMaze());
        CASE(N = rnd.nextInt(450,500),M = rnd.nextInt(300,450),Q = 100000,FlipMaze());
        CASE(N = 500, M = 500, MakeMaze(),SameQ());
        CASE(N = 500, M = 500, MakeMaze(1),PojokQ());
        CASE(N = 500,M = 500,Q = 100000,ThinCase(10,1));
    }

private:
    void whiten(LL tar, LL kiri, LL kanan, bool tipe,LL getchange){
        if(kiri > kanan) return;
        LL mid = rnd.nextInt(kiri,kanan);
        A[tar][mid] = tipe;
        whiten(tar,kiri,mid-getchange,tipe,getchange);
        whiten(tar,mid+getchange,kanan,tipe,getchange);
    }
    void MakeMaze(bool forced = 0){
        A.resize(N);
        for(int i = 0;i < N;i++){
            for(int j = 0;j < M;j++){
                if(i%2 == 0) A[i].pb(1);
                else A[i].pb(0);
            }
        }
        for(int i = 1;i < N;i += 2){
            whiten(i,0,M-1,1,rnd.nextInt(2,5));
        }
        for(int i = 0;i < N;i += 2){
            whiten(i,0,M-1,0,rnd.nextInt(3,9));
        }
        if(forced) A[N-1][M-1] = 1;
        PLL st = {1,100};
        PLL ed = {MAXA-100,MAXA};
        for(int i = 0;i < N;i++){
            for(int j = 0;j < M;j++){
                LL curval;
                if(A[i][j]) A[i][j] = rnd.nextInt(st.fi,st.se);
                else A[i][j] = rnd.nextInt(ed.fi,ed.se);
            }
        }
        if(forced) return;

        for(int i = 0;i < Q;i++){
            LL posx,posy;
            do{
                posx = rnd.nextInt(1,N);
                posy = rnd.nextInt(1,M);
            }while(A[posx-1][posy-1] > 100);
            LL curval,isi = A[posx-1][posy-1];
            if(rnd.nextInt(0,100)) curval = rnd.nextInt(isi,isi+25);
            else curval = rnd.nextInt(isi,100);
            X.pb(posx); Y.pb(posy); L.pb(curval);
        }
    }
    void FlipMaze(){
        MakeMaze();
        //Transpose A, and swap X,Y
        grid TEMP;
        swap(N,M);
        TEMP.resize(N);
        for(int i = 0;i < N;i++){
            for(int j = 0;j < M;j++){
                TEMP[i].pb(A[j][i]);
            }
        }
        for(int i = 0;i < Q;i++) swap(X[i],Y[i]);
        swap(TEMP,A);
    }
    void RandGrid(LL lo = 1, LL hi = MAXA){
        A.resize(N);
        for(int i = 0;i < N;i++){
            for(int j = 0;j < M;j++){
                LL curval = rnd.nextInt(lo,hi);
                A[i].pb(curval);
            }
        }
    }
    void ThinCase(LL diff,bool isAll = 0){
        LL lo,hi;
        do{
            lo = rnd.nextInt(1,100000);
            hi = lo+diff;
        }while(!(1 <= lo && hi <= MAXA));
        RandGrid(lo,hi);
        if(diff <= 10) diff = 10;
        if(!isAll) RandQ(lo,min(MAXA,hi+(diff/2)));
        else AllQ(hi);
    }
    void PojokQ(){
        for(int i = A[N-1][M-1];i <= MAXA;i++){
            X.pb(N); Y.pb(M); L.pb(i);
        }
        Q = X.size();
        return;
    }   
    void RandQ(LL lo = 1, LL hi = MAXA){
        for(int i = 0;i < Q;i++){
            LL posx = rnd.nextInt(1,N);
            LL posy = rnd.nextInt(1,M);
            LL curval,isi = A[posx-1][posy-1];
            if(rnd.nextInt(0,100)) curval = rnd.nextInt(isi,min(isi+rnd.nextInt(0,(hi-lo)/2),hi));
            else curval = rnd.nextInt(isi,hi);
            X.pb(posx); Y.pb(posy); L.pb(curval);
        }
    }
    void SameQ(){
        X.clear(); Y.clear(); L.clear();
        for(int i = 0;i < Q;i++){
            LL posx = rnd.nextInt(1,N);
            LL posy = rnd.nextInt(1,M);
            LL curval = A[posx-1][posy-1];
            X.pb(posx); Y.pb(posy); L.pb(curval);
        }
    }
    void AllQ(LL maxa){
        X.clear(); Y.clear(); L.clear();
        for(int i = 1;i <= N;i++){
            for(int j = 1;j <= M;j++){
                for(int k = A[i-1][j-1];k <= maxa;k++){
                    if(X.size() < MAXQ){ X.pb(i); Y.pb(j); L.pb(k);}
                    else break;
                }
            }
        }
        Q = X.size();
    }
    void BipartiteGrid(){
        PLL st = {1,100};
        PLL ed = {MAXA-100,MAXA};
        A.resize(N);
        for(int i = 0;i < N;i++){
            for(int j = 0;j < M;j++){
                LL curval;
                if(rnd.nextInt(0,5)){
                    curval = rnd.nextInt(st.fi,st.se);
                }else{
                    curval = rnd.nextInt(ed.fi,ed.se);
                }
                A[i].pb(curval);
            }
        }
    }
};
