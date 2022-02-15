#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

#define fi first
#define se second

typedef long long LL;

const int MAXN = 2e5;
const int MAXT = 1e9;

class ProblemSpec : public BaseProblemSpec {
    protected:
        int N, K;
        LL Ans;
        vector<int> T;

        void InputFormat() {
            LINE(N, K);
            LINE(T % SIZE(N));
        }

        void OutputFormat() {
            LINE(Ans);
        }

        void GradingConfig() {
            TimeLimit(1); // TBC
            MemoryLimit(64);
        }

        void Constraints() {
            CONS((1 <= K) && (K <= N) && (N <= MAXN));
            CONS(eachElementBetween(T, 1, MAXT));
        }

        void Subtask1(){
            Points(100);
        }

    private:
        template <class T>

        bool eachElementBetween(const vector<T> &V, T lo, T hi){
            for(T x : V) if(x < lo || hi < x) return false;
            return true;
        }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
    protected:
        void SampleTestCase1() {
            Subtasks({1});
            Input({
                "5 5",
                "1 3 2 6 3",
            });
            Output({
                "27",
            });
        }

        void SampleTestCase2() {
            Subtasks({1});
            Input({
                "7 1",
                "1 1 2 2 2 2 2",
            });
            Output({
                "14",
            });
        }

        void BeforeTestCase(){
            T.clear();
        }
        
        void TestGroup1(){
            Subtasks({1});

            // Basic random array
                CASE(N = 153, K = 132, randomArray());
                CASE(N = 3201, K = 1023, randomArray());
            
            // One value array -> Divide into 1 group
                CASE(N = 63236, K = 50791, oneValueArray());

            // Integer overflow
                CASE(N = MAXN, K = 3, oneValueArray(MAXT,MAXT));
                CASE(N = MAXN, K = 342, randomArray(MAXT-500,MAXT));
                CASE(N = MAXN, K = 42503, randomArray(MAXT-500,MAXT));
                CASE(N = MAXN, K = 167422, randomArray(MAXT-500,MAXT));

            // Big Random array
                CASE(N = MAXN, K = 821, randomArray());
                CASE(N = MAXN, K = 47886, randomArray());
                CASE(N = MAXN, K = 121003, randomArray());

            // Big N, big K, big T[]
                CASE(N = MAXN, K = MAXN, randomArray(MAXT-20,MAXT));
                CASE(N = MAXN, K = MAXN, nonDecreasingArray(MAXT-500,MAXT));

            // T[] is non-decreasing -> All element must be considered
                CASE(N = MAXN, K = MAXN, nonDecreasingArray(MAXT-500,MAXT));

            // Convex-hull killer -> Big convex-hull size
                CASE(N = MAXN, K = MAXN, tightArray());

            // Many groups
                CASE(N = MAXN, K = MAXN, manyGroups(3,1,MAXT));
                CASE(N = MAXN, K = MAXN, manyGroups(5,1,MAXT));
                CASE(N = MAXN, K = MAXN, manyGroups(9,1,MAXT));
                CASE(N = MAXN, K = MAXN, manyGroups(10,1,MAXT));
                CASE(N = MAXN, K = MAXN, manyGroups(11,1,MAXT));
                CASE(N = MAXN, K = MAXN, manyGroups(16,1,MAXT));
                CASE(N = MAXN, K = MAXN, manyGroups(21,1,MAXT));
                CASE(N = MAXN, K = MAXN, manyGroups(-1,1,MAXT));
                CASE(N = MAXN, K = MAXN, manyGroups(-1,MAXT/100,MAXT));
                CASE(N = MAXN, K = MAXN, manyGroups(-1,1,MAXT/100,5));
                CASE(N = MAXN, K = MAXN, manyGroups(-1,1,MAXT,5));
                CASE(N = MAXN, K = MAXN, manyGroups(-1,1,MAXT,5));
                CASE(N = MAXN, K = MAXN, manyGroups());
                CASE(N = MAXN, K = MAXN, manyGroups());
            
            // Good small killer tc
                CASE(N = 4, K = 2, T = {1,1,3,7});
        }

    private:
        void oneValueArray(int lo=1, int hi=MAXT) {
            T.resize(N);
            int val = rnd.nextInt(lo,hi);
            for (int i = 0; i < N; i++) T[i] = val;
        }

        void randomArray(int lo=1, int hi=MAXT) {
            T.resize(N);
            for (int i = 0; i < N; i++) T[i] = rnd.nextInt(lo,hi);
        }

        void nonDecreasingArray(int lo=1, int hi=MAXT) {
            T.resize(N);
            int lst = lo;
            for (int i = 0; i < N; i++) {
                T[i] = rnd.nextInt(lst,hi);
                lst = T[i];
            }
        }

        void tightArray(int lo=1, int hi=MAXT) {
            // Create a tight non-decreasing array
            // Tight -> difference of adjacent element is small
            T.resize(N);
            int lst = rnd.nextInt(lo,hi-20*N);
            for (int i = 0; i < N; i++) {
                T[i] = lst + rnd.nextInt(0,20);
                lst = T[i];
            }
        }

        void manyGroups(int size=-1, int lo=1, int hi=MAXT, int noise=1) {
            vector<int> X, Y;
            
            X.push_back(1); Y.push_back(hi);
            while (X.back()*10/6 + 1 <= N && Y.back()*4LL/10 >= lo) {
                X.push_back(min(N, X.back()*10/6 + rnd.nextInt(1, noise)));
                Y.push_back(max(1LL, Y.back()*4LL/10 - rnd.nextInt(1, noise) + 1));
            }
            if (size >= 0 && X.size() > size) X.resize(size), Y.resize(size);
            X.push_back(N); Y.push_back(lo);

            T.resize(N);

            for (int i = 0; i < X.size(); ++i) {
                T[--X[i]] = Y[i];
            }
            for (int i = 1; i < X.size(); ++i) {
                for (int j = X[i - 1] + 1; j < X[i]; ++j) {
                    T[j] = rnd.nextInt(min(Y[i - 1], Y[i] + 1), Y[i - 1]);
                }
            }
            reverse(T.begin(), T.end());
        }

        // void manyGroups(int lo=1, int hi=MAXT) {
        //     vector<int> X, Y;
            
        //     X.push_back(1);
        //     while (X.back()*2 <= N) X.push_back(X.back()*2);
            
        //     Y.push_back(hi);
        //     while (Y.size() < X.size()) Y.push_back((Y.back()+1)/2);

        //     T.resize(N);
        //     for (int &i : T) i = -1;
        //     for (int &i : X) i = N-i;
        //     for (int i = 0; i < X.size(); i++) T[X[i]] = Y[i];
        //     for (int i = N-1, j = -1; i >= 0; i--) {
        //         if (T[i] != -1) j = T[i];
        //         else T[i] = j;
        //     }
        // }
};