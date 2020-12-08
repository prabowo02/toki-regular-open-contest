#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace std;
using namespace tcframe;
const int MAXN = 100;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, M;
    vector<vector<char>> ANS;
    void InputFormat() {
        LINE(N, M);
    }

    void OutputFormat(){
        GRID(ANS) % SIZE(N, M);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void StyleConfig() {
        CustomScorer();
    }

    void Constraints() {
        CONS((1 <= N) && (N <= MAXN));
        CONS((1 <= M) && (M <= MAXN));
    }

    void Subtask1(){
        Points(100);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1});
        Input({
            "2 3",
        });
        Output({
            "WWW",
            "BBB",
        });
    }
    void SampleTestCase2() {
        Subtasks({1});
        Input({
            "4 1",
        });
        Output({
            "W",
            "B",
            "W",
            "B",
        });
    }
    void TestGroup1(){
        Subtasks({1});
        CASE(N = 1; M = 1);
        CASE(N = 1; M = 2);
        CASE(N = 2; M = 1);
        CASE(N = 3; M = 3);
        CASE(N = rnd.nextInt(25,50)*2; M = rnd.nextInt(25,50)*2);
        CASE(N = rnd.nextInt(25,50)*2; M = rnd.nextInt(25,50)*2-1);
        CASE(N = rnd.nextInt(25,50)*2-1; M = rnd.nextInt(25,50)*2);
        CASE(N = rnd.nextInt(25,50)*2-1; M = rnd.nextInt(25,50)*2-1);
        CASE(N = 100; M = 100);
    }
};