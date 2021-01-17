#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;
#define pb push_back

const int MAXN = 300;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, ANS;
    vector <int> A;
    void InputFormat() {
        LINE(N);
        LINE(A % SIZE(N));
    }

    void OutputFormat(){
        LINE(ANS);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS((3 <= N) && (N <= MAXN));
        CONS(isPermutation(N, A));
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
    bool isPermutation(int N, vector<int> V){
        sort(V.begin(),V.end());
        V.erase(unique(V.begin(),V.end()),V.end());
        return (V.size() == N && V.front() == 1 && V.back() == N);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1});
        Input({
            "3",
            "2 3 1",
        });
        Output({
            "1",
        });
    }
    void SampleTestCase2() {
        Subtasks({1});
        Input({
            "3",
            "3 2 1",
        });
        Output({
            "0",
        });
    }
    void SampleTestCase3() {
        Subtasks({1});
        Input({
            "4",
            "3 1 4 2",
        });
        Output({
            "2",
        });
    }
    void BeforeTestCase(){
        A.clear();
    }
    void TestGroup1(){
        Subtasks({1});

        CASE(N = 75; makeA());
        CASE(N = MAXN; PeriodSwap(2));
        CASE(N = MAXN; PeriodSwap(5));
        CASE(N = MAXN; PeriodSwap(N/2));
        CASE(N = 69; mountainSwap());

        CASE(N = 10; randomReverseEngineer());
        CASE(N = 15; randomReverseEngineer());
        CASE(N = 75; randomReverseEngineer());
        CASE(N = 150; randomReverseEngineer());
        CASE(N = 247; inverseMountainSwap());

        CASE(N = MAXN; randomReverseEngineer());
        CASE(N = MAXN; randomNoiseReverseEngineer());
        CASE(N = 5; randomMaybeValidCondition());
        CASE(N = 70; randomMaybeValidCondition());
        CASE(N = MAXN; randomMaybeValidCondition());
        
        CASE(N = 4; randomPermutation());
        CASE(N = MAXN; randomPermutation());
    }

private:
    void makeA(){
        A.resize(N); iota(A.begin(), A.end(), 1);
    }
    void randomMaybeValidCondition(int chain = -1){
        if(chain == -1) chain = max(N/3, 1);
        A.resize(N, 0); vector <int> tmp(N-2);
        
        iota(tmp.begin(), tmp.end(), 2);
        rnd.shuffle(tmp.begin(), tmp.end());
        tmp.resize(chain); sort(tmp.begin(), tmp.end());
        tmp.pb(N);

        vector <bool> done(N+1);
        vector <int> rem;

        // for(auto &cur : tmp) cout << cur << " ";
        // cout << endl;

        A[0] = tmp[0]; done[tmp[0]] = 1;
        for(int i = 1;i <= chain;i++){
            A[tmp[i-1]-1] = tmp[i];
            done[tmp[i]] = 1;
        }
        
        // for(auto &cur : A) cout << cur << " ";
        // cout << endl;

        for(int i = 1;i <= N;i++) if(!done[i]) rem.pb(i);

        rnd.shuffle(rem.begin(), rem.end());

        for(int i = 0;i < N;i++){
            if(A[i]) continue;
            A[i] = rem.back();
            rem.pop_back();
        }

    }
    void randomReverseEngineer(){
        makeA(); vector<int>Q(N-1);
        iota(Q.begin(), Q.end(), 0);
        rnd.shuffle(Q.begin(), Q.end());
        for(int i = 0;i < N-1;i++) swap(A[Q[i]], A[Q[i]+1]);
    }
    void PeriodSwap(int period = 2){
        makeA(); vector<int>Q(N-1,-1);
        int cnt = 0;
        for(int i = 0;i < N-1;i++){
            for(int j = i;j < N-1;j += period){
                if(Q[j] != -1) continue;
                Q[j] = cnt++;
            }
        }
        for(int i = 0;i < N-1;i++) swap(A[Q[i]], A[Q[i]+1]);

    }
    void mountainSwap(){
        makeA(); vector<int>Q(N-1,-1);
        int cnt = 0;
        int middle = (N-1)/2;
        for(int i = middle;i >= 0;i--) Q[i] = cnt++;
        for(int i = middle+1;i < N-1;i++) Q[i] = cnt++;
        for(int i = 0;i < N-1;i++) swap(A[Q[i]], A[Q[i]+1]);
    }
    void inverseMountainSwap(){
        // tambahin juga testcase yang "inverse mountain", jadi swapnya yang [1, 2, ..., mid - 1] dulu, terus [N-1, N-2, ..., mid + 1], dan terakhir swap mid
        makeA(); vector<int>Q(N-1,-1);
        int cnt = 0;
        int middle = (N-1)/2;
        for(int i = middle+1;i < N-1;i++) Q[i] = cnt++;
        for(int i = middle;i >= 0;i--) Q[i] = cnt++;
        for(int i = 0;i < N-1;i++) swap(A[N-Q[i]-2], A[N-Q[i]-1]);
        // for(int i = 0;i < N-1;i++) cout << N-Q[i]-2 << endl;
    }
    void randomNoiseReverseEngineer(int noise = 5){
        randomReverseEngineer();
        while(noise--){
            int noiseIdx = rnd.nextInt(0, N-2);
            swap(A[noiseIdx], A[noiseIdx+1]);
        }
    }
    void randomPermutation(){
        makeA();
        rnd.shuffle(A.begin(), A.end());
    }
};