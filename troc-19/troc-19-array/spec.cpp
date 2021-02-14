#include <tcframe/spec.hpp>
#include <iostream>
#include <assert.h>
#define ll long long
using namespace tcframe;
const ll MAX_K = (1 << 15) - 1;
const int randomPermutation[14] = {8, 5, 4, 9, 11, 3, 6, 12, 14, 1, 13, 10, 2, 7};

using namespace std;

class ProblemSpec : public BaseProblemSpec 
{
protected:
    int K, N;
   	vector<int> A;

    void InputFormat() 
    {
        LINE(K);
    }

    void OutputFormat() 
    {
        LINE(N);
        LINE(A % SIZE(N));
    }

    void GradingConfig() 
    {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void StyleConfig()
    {
        BatchEvaluator();
        CustomScorer();
    }

    void Constraints() 
    {
        CONS(1 <= K && K <= MAX_K);
    }

    void Subtask1() 
    {
        Points(100);
    }

private:
};

class TestSpec : public BaseTestSpec<ProblemSpec> 
{
protected:
    void SampleTestCase1() 
    {
        Subtasks({1});
        Input({
            "6"
        });
        Output({
            "4",
            "47 43 34 32"
        });
    }

    void SampleTestCase2() 
    {
        Subtasks({1});
        Input({
            "1"
        });
        Output({
            "2",
            "1273 1272"
        });
    }

    void BeforeTestCase()
    {
        A.clear();
    }

    void TestGroup1()
    {
        Subtasks({1});
        CASE(K = (1 << 15) - 1);            // 111111111111111
        CASE(K = 22937);                    // 101100110011001
        CASE(K = 21845);                    // 101010101010101

        for (int i = 0; i < 14; i++) CASE(K = getNumber(randomPermutation[i]));
        
        CASE(K = rnd.nextInt(1, MAX_K));
        CASE(K = rnd.nextInt(1, MAX_K));
    }


private:

    inline int getNumber(int B)
    {
        vector<int> S; int ret = 0;
        for (int i = 0; i < 15; i++) {S.push_back(1 << i);}
        rnd.shuffle(S.begin(), S.end());
        for (int i = 0; i < B; i++) {ret |= S[i];}
        return ret;
    }
}; 
