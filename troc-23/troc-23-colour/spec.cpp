#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    int type, seed;
    string ANS;
    void InputFormat() {
        LINE(type);
        LINE(seed);
    }

    void OutputFormat(){
        LINE(ANS);
    }

    void StyleConfig() {
        InteractiveEvaluator();
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void TestGroup1(){
        CASE(type = 0, seed = 0);
        CASE(type = 3, seed = 0);
        CASE(type = 4, seed = 0);
        long long seeds[3] = {142857, 265, 42069};
        for(int i=0; i<3; i++){
            CASE(type = 1, seed = seeds[i]);
            CASE(type = 2, seed = seeds[i]);
            CASE(type = 5, seed = seeds[i]);
            CASE(type = 6, seed = seeds[i]);
        }
    }

};