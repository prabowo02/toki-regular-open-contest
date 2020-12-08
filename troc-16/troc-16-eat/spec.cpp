#include <tcframe/spec.hpp>
#include <iostream>
#include <assert.h>
#define ll long long
using namespace tcframe;
const ll MAX_N = 200000, MAX_A = 1000000000;

using namespace std;

class ProblemSpec : public BaseProblemSpec 
{
protected:
    int N, M, ans;
   	vector<int> A;

    void InputFormat() 
    {
        LINE(N, M);
        LINE(A % SIZE(N));
    }

    void OutputFormat() 
    {
        LINE(ans);
    }

    void GradingConfig() 
    {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() 
    {
        CONS(1 <= N && N <= MAX_N);
        CONS(0 <= M && M <= MAX_A);
        CONS(checkVector(A, 1, M));
    }

    void Subtask1() 
    {
        Points(100);
    }

private:
    bool checkVector(const vector<int>& V, int L, int R)
    {
        for (auto &A : V) 
        {
            if (A < L || A > R) {return 0;}
        }
        return 1;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> 
{
protected:
    void SampleTestCase1() 
    {
        Subtasks({1});
        Input({
            "3 10",
            "2 10 8"
        });
        Output({
            "4"
        });
    }

    void SampleTestCase2() 
    {
        Subtasks({1});
        Input({
            "3 1",
            "1 1 1"
        });
        Output({
            "0"
        });
    }

    void BeforeTestCase()
    {
        A.clear();
    }

    void TestGroup1()
    {
        Subtasks({1});

        // Corner case : same element
        CASE(N = 1, M = 1, A = {1});
        CASE(N = MAX_N, M = MAX_A, sameVector(N, M));

        // Hocky's cases
        CASE(N = 2, M = 4, A = {2, 3});
        CASE(N = 2, M = 4, A = {1, 4});

        // Max-tests
        CASE(N = M = MAX_N, randomPermutation(N));
        CASE(N = MAX_N, M = MAX_A, equalSpace(N, M));
        CASE(N = MAX_N, M = N / 5, randomVector(N, M));
        CASE(N = MAX_N, M = MAX_A, cornerAns(N, M, M - 69));

        // Random-tests
        CASE(N = MAX_N, M = MAX_A, randomVector(N, M));
        CASE(N = MAX_N, M = rnd.nextInt(1, MAX_A), equalSpace(N, M));
        CASE(N = 169420, M = rnd.nextInt(1, MAX_A), randomVector(N, M));
        CASE(N = rnd.nextInt(1, MAX_N), M = rnd.nextInt(1, MAX_A), randomVector(N, M));
        CASE(N = rnd.nextInt(1, MAX_N), M = rnd.nextInt(1, MAX_A), cornerAns(N, M, (int)(M / rnd.nextDouble(1, 10))));
        CASE(N = rnd.nextInt(1, MAX_N), M = rnd.nextInt(1, MAX_A), equalSpace(N, M));
    }


private:

    void randomVector(int N, int M) 
    {
        for (int i = 0; i < N; i++) {A.push_back(rnd.nextInt(1, M));}
    }

    void equalSpace(int N, int M) //Code doesn't work for N == 1
    {
        assert(N > 1);
        int cur = rnd.nextInt(0, M - 1);

        vector<int> lol; //Slightly randomizes spacing
        for (int i = 0; i < N; i++) {lol.push_back(0);}
        for (int i = 0; i < M % N; i++) {lol[rnd.nextInt(N - 1)]++;}

        for (int i = 0; i < N; i++)
        {
            A.push_back(cur + 1); cur += M / N;
            cur += lol[i]; cur %= M;
        }
        rnd.shuffle(A.begin(), A.end());
    }

    void cornerAns(int N, int M, int d) //Code assumes large enough M for spacing to not be an issue
    {
        assert(M >= d); assert(N >= 2);
        
        int L = rnd.nextInt(0, d - 2), R = L + M - d; //The solution
        A.push_back(L + 1);
        A.push_back(R + 1);

        for (int i = L + d - 1; i < R; i += d - 1) //Everything else
        {
            A.push_back(i + 1);
        }
        while (A.size() < N) {A.push_back(rnd.nextInt(L, R) + 1);}
        rnd.shuffle(A.begin(), A.end());
    } 

    void sameVector(int N, int M)
    {
        int cur = rnd.nextInt(1, M);
        for (int i = 0; i < N; i++) {A.push_back(cur);}
    }

    void randomPermutation(int N)
    {
        assert(N == M);
        for (int i = 1; i <= N; i++) {A.push_back(i);}
        rnd.shuffle(A.begin(), A.end());
    }
}; 
