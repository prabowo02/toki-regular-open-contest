#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 100000;
const int MAXA = 100000;

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
        CONS((1 <= N) && (N <= MAXN));
        CONS(eachElementBetween(A,2,MAXA));
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
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1});
        Input({
            "8",
            "9 12 11 13 10 10 12 9",
        });
        Output({
            "4"
        });
    }
    void SampleTestCase2() {
        Subtasks({1});
        Input({
            "1",
            "265",
        });
        Output({
            "0",
        });
    }
    void BeforeTestCase(){ A.clear(); }
    void TestGroup1(){
        Subtasks({1});
        CASE(N = 3; A = {2,3,4});
        CASE(N = 3; A = {3,3,2});
        CASE(N = 9; A = {3,3,3,3,4,4,4,4,4});
        CASE(N = 11; A = {3,3,3,3,3,3,4,4,4,4,4});
        CASE(N = 3; A = {MAXA-3,MAXA-1,MAXA-1});
        CASE(N = 3; A = {MAXA-4,MAXA-1,MAXA-1});
        CASE(N = 4; A = {MAXA-1,MAXA-1,MAXA,MAXA});
        CASE(N = 5; genRandomArray(2, 5));
        CASE(N = 5; genRandomArray(2, 10));
        CASE(N = 10; genRandomArray(2, 10));
        CASE(N = rnd.nextInt(MAXN/2, MAXN); genPeriodArray(MAXA - 10000, MAXA, 4));
        CASE(N = rnd.nextInt(MAXN/2, MAXN); genRandomArray());
        CASE(N = MAXN; genRandomArray(MAXA*3/4, MAXA));
        CASE(N = MAXN; genRandomArray());
        CASE(N = MAXN; genRandomArray());
        CASE(N = MAXN; genPeriodArray(MAXA - 100, MAXA));
        CASE(N = MAXN; genPeriodArray(MAXA - 10000, MAXA, 3));
        CASE(N = MAXN; genPeriodArray(2, MAXA));
        CASE(N = MAXN; makeAllAvailable());
        CASE(N = MAXN; makeAllAvailable(MAXA/2, MAXA));
        CASE(N = MAXN; makeAllAvailable(MAXA*3/4, MAXA));
        CASE(N = MAXN; genPeriodArray(MAXA - 10000, MAXA, 6, 3));
        CASE(N = MAXN; genPeriodArray(MAXA - 10000, MAXA, 5, 2));
    }

private:
    void genRandomArray(int lo = 2, int hi = MAXA){
        A.resize(N);
        for(int &x : A) x = rnd.nextInt(lo, hi);
    }
    // Generate period like comments, do + shift on each, with overflow fit padding
    void genPeriodArray(int lo = 2, int hi = MAXA, int mod = 2, int x = 1){
        int shift = rnd.nextInt(mod);
        A.resize(N);
        for(int &val : A){
            val = rnd.nextInt(lo, hi);
            // let mod = 6, x = 2
            // o o o o x x
            // 0 1 2 3 4 5
            if(val%mod >= mod - x){
                val -= val%mod;              // This falls on x
                val += rnd.nextInt(mod - x); // Adjust to nearest o
            }
            val += shift;
            while(val < lo) val += mod;
            while(val > hi) val -= mod;
        }
    }

    void makeAllAvailable(int lo = 2, int hi = MAXA){
        A.clear();
        for(int i = lo;i <= hi;i++) A.push_back(i);
        while(A.size() < N) A.push_back(rnd.nextInt(lo, hi));
    }
};
