#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;
#define fi first
#define se second
typedef long long LL;
typedef pair<LL,LL> PLL;
#define pb push_back
const LL LINF = 4557430888798830399LL;
const LL MAXN = 1000;
const LL MAXA = 1000000000LL;

class ProblemSpec : public BaseProblemSpec {
protected:
    LL N,M,P;
    vector<vector<LL>> A;
    string ANS;
    void InputFormat() {
        LINE(N,M,P);
        GRID(A)%SIZE(N, M);
    }

    void OutputFormat(){
        LINE(ANS);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(P <= min(N,M));
        CONS((1 <= N) && (N <= MAXN));
        CONS((1 <= M) && (M <= MAXN));
        CONS((1 <= P) && (P <= MAXN));
        CONS(eachElementBetween(A,0,MAXA));
    }

    void Subtask1(){
        Points(100);
    }

private:
    bool eachElementBetween(const vector<vector<LL>>&V,LL lo, LL hi){
        for(int i = 0;i < V.size();i++){
            for(int j = 0;j < V[i].size();j++){
                if(V[i][j] < lo || V[i][j] > hi) return 0;
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
            "3 3 2",
            "1 2 1",
            "2 4 2",
            "1 2 1"
        });
        Output({
            "YA"
        });
    }
    void SampleTestCase2(){
        Subtasks({1});
        Input({
            "2 3 2",
            "1 2 1",
            "1 3 1"
        });
        Output({
            "TIDAK"
        });

    }
    void BeforeTestCase(){
        P = -1;
        A.clear();
    }
    void TestGroup1(){
        Subtasks({1});
        //YES Query
        CASE(N = 1; M = 1; MakeYesGrid(N,M));
        CASE(N = 3; M = 3; P = 2; MakeYesGrid(N,M));
        CASE(N = 10; M = 10; MakeYesGrid(N,M));
        CASE(N = 1000; M = 1000; MakeYesGrid(N,M));
        CASE(N = 1000; M = 1000; P = 1; MakeYesGrid(N,M));
        CASE(N = rnd.nextInt(500,1000); M = rnd.nextInt(750,1000); MakeYesGrid(N,M));
        CASE(N = rnd.nextInt(500,1000); M = rnd.nextInt(750,1000); MakeYesGrid(N,M));
        CASE(N = rnd.nextInt(750,1000); M = rnd.nextInt(250,1000); MakeYesGrid(N,M));
        CASE(N = rnd.nextInt(750,1000); M = rnd.nextInt(250,1000); MakeYesGrid(N,M));
        CASE(N = 840; M = 720; P = 12; MakeExtremeYesGrid(N,M));
        CASE(N = rnd.nextInt(750,1000); M = rnd.nextInt(250,1000); MakeExtremeYesGrid(N,M));

        //NO Query
        CASE(N = 1000; M = 1000; MakeAlmostYesGrid(N,M));
        CASE(N = rnd.nextInt(750,1000); M = rnd.nextInt(250,1000); MakeExtremeNoGrid(N,M));
        CASE(N = rnd.nextInt(200,1000); M = rnd.nextInt(750,1000); MakeExtremeNoGrid(N,M));
        CASE(N = rnd.nextInt(500,1000); M = rnd.nextInt(750,1000); MakeAlmostYesGrid(N,M));
        CASE(N = rnd.nextInt(750,1000); M = rnd.nextInt(250,1000); MakeAlmostYesGrid(N,M));
        CASE(N = rnd.nextInt(500,1000); M = rnd.nextInt(750,1000); MakeOneAwayGrid(N,M));
        CASE(N = rnd.nextInt(750,1000); M = rnd.nextInt(250,1000); MakeOneAwayGrid(N,M));

        CASE(N = rnd.nextInt(500,1000); M = rnd.nextInt(750,1000); MakeOutGrid(N,M));
        CASE(N = rnd.nextInt(500,1000); M = rnd.nextInt(750,1000); MakeOutGrid(N,M));

        //Random Query
        CASE(N = rnd.nextInt(500,1000); M = rnd.nextInt(750,1000); MakeRandomGrid(N,M));
        CASE(N = rnd.nextInt(750,1000); M = rnd.nextInt(250,1000); MakeRandomGrid(N,M));

        //Suggestion Query
        CASE(N = 720, M = 720, P = 24; MakeYesGrid(N,M));
        CASE(N = 840, M = 840, P = 42; MaxGrid(N,M));
        CASE(N = 800, M = 1000, makeGrid(N,M));

        //Big P
        CASE(N = 1000; M = 1000; P = 333; MakeYesGrid(N,M));
        CASE(N = 999; M = 999; P = 333; MakeExtremeYesGrid(N,M));

        //Underflow
        CASE(N = 1000; M = 1000; P = 125; UnderflowGrid(N,M));
        CASE(Custom_Case_1());
        CASE(Custom_Case_2());

    }

private:
    void makeGrid(LL n, LL m){
        A.resize(n);
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                A[i].pb(0);
            }
        }
        LL maxP = min(n,m);
        if(P == -1) P = rnd.nextInt(1,maxP);
    }
    void sumGrid(LL n, LL m){
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                PLL pre = {i-1,j-1};
                if(pre.fi >= 0) A[i][j] += A[pre.fi][j];
                if(pre.se >= 0) A[i][j] += A[i][pre.se];
                if(pre.fi >= 0 && pre.se >= 0) A[i][j] -= A[pre.fi][pre.se];
            }
        }
    }
    void MaxGrid(LL n, LL m){
        makeGrid(n,m);
        for(int i = 0;i < N;i++){
            for(int j = 0;j < M;j++){
                A[i][j] = MAXA;
            }
        }
    }
    void updaterect(PLL st, PLL ed,LL val){
        if(val == 0) return;
        A[st.fi][st.se] += val;
        if(ed.fi+1 < N) A[ed.fi+1][st.se] -= val;
        if(ed.se+1 < M) A[st.fi][ed.se+1] -= val;
        if(ed.fi+1 < N && ed.se+1 < M) A[ed.fi+1][ed.se+1] += val;
    }
    void MakeYesGrid(LL n, LL m){
        makeGrid(n,m);
        LL curval = MAXA/(P*P);
        for(int i = 0;i < n;i++){
            if(i+P-1 >= N) break;
            for(int j = 0;j < m;j++){
                if(j+P-1 >= M) break;
                updaterect({i,j},{i+P-1,j+P-1},rnd.nextInt(1,curval));
            }
        }
        sumGrid(n,m);
    }
    void MakeRandomGrid(LL n, LL m){
        makeGrid(n,m);
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                A[i][j] = rnd.nextInt(1,MAXA);
            }
        }
    }
    void MakeOutGrid(LL n, LL m){
        makeGrid(n,m);
        LL curval = 1000000000LL/(P*P);
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                updaterect({i,j},{i+P-1,j+P-1},curval);
            }
        }
        sumGrid(n,m);
    }
    void MakeAlmostYesGrid(LL n, LL m){
        MakeYesGrid(n,m);
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                LL curval = min(rnd.nextLongLong(1,5),A[i][j]);
                A[i][j] -= curval;
            }
        }
    }
    void MakeOneAwayGrid(LL n, LL m){
        MakeYesGrid(n,m);
        PLL pos = {rnd.nextInt(0,n-1),rnd.nextInt(0,m-1)};
        A[pos.fi][pos.se] -= rnd.nextInt(1,A[pos.fi][pos.se]);
    }
    void MakeExtremeNoGrid(LL n, LL m){
        makeGrid(n,m);
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                A[i][j] = rnd.nextInt(MAXA-100LL,MAXA);
            }
        }
    }
    void MakeExtremeYesGrid(LL n, LL m){
        MakeYesGrid(n,m);
        LL maksi = A[0][0];
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                maksi = max(A[i][j],maksi);
            }
        }
        LL selisih = MAXA-maksi;
        selisih = rnd.nextInt(max(0LL,selisih-100LL),selisih);
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                A[i][j] += selisih;
            }
        }
    }
    void UnderflowGrid(LL n, LL m){
        makeGrid(n,m);
        LL curval = MAXA/(P*P);
        for(int i = 0;i < n;i++){
            if(i+P-1 >= N) break;
            for(int j = 0;j < m;j++){
                if(j+P-1 >= M) break;
                updaterect({i,j},{i+P-1,j+P-1},rnd.nextInt(1,curval));
            }
        }
        sumGrid(n,m);
        //Pilih satu titik pojok
        PLL under = {rnd.nextInt(1,N-P),rnd.nextInt(1,M-P)};
        LL undermin = LINF;
        for(int i = under.fi;i <= under.fi+P-1;i++){
            for(int j = under.se;j <= under.se+P-1;j++){
                undermin = min(undermin,A[i][j]);
            }
        }
        for(int i = under.fi;i <= under.fi+P-1;i++){
            for(int j = under.se;j <= under.se+P-1;j++){
                A[i][j] -= undermin;
            }
        }
    }
    void Custom_Case_1(){
        N = 2; M = 4; P = 2;
        A = {{1,0,0,1},{1,0,0,1}};
    }
    void Custom_Case_2(){
        N = 4; M = 4; P = 2;
        A = {{1,1,1,1},{1,0,0,1},{1,0,0,1},{1,1,1,1}};
    }
};