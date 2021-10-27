#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN = 1000000000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, ANS;
    void InputFormat() {
        LINE(N);
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
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "50",
        });
        Output({
            "4"
        });
    }
    void SampleTestCase2() {
        Input({
            "5",
        });
        Output({
            "0",
        });
    }
    void TestGroup1(){
        CASE(N = 9);
        CASE(N = 42);
        CASE(N = 100);
        CASE(N = 28);
        CASE(N = 83);
        CASE(N = 1234);
        CASE(N = 39);
        CASE(N = 69);
        CASE(N = 1000000000);
        //siapa tahu pakai short
        CASE(N = 65556);
        for(int i=0; i<3; i++){
            CASE(N = rnd.nextInt(1, MAXN));
        }        
    }

};
