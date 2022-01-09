#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, K;
    long long ans;

    void InputFormat() {
        LINE(N, K);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= N && N <= 50);
        CONS(1 <= K && K <= 50);
    }

    void Subtask1() {
        Points(100);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1});
        Input({
            "10 2"
        });
        Output({
            "512"
        });
    }

    void SampleTestCase2() {
        Subtasks({1});
        Input({
            "10 7"
        });
        Output({
            "56"
        });
    }

    void TestGroup1() {
        Subtasks({1});
        CASE(N = 1, K = 2); //min constraint / min ans
        CASE(N = 50, K = 2); //max ans
        CASE(N = 50, K = 32); // k = 2^a
        CASE(N = 50, K = 50); //max constraints
        CASE(N = 50, K = 49); // k != 2^a
        //  random
        for(int i=1; i<=3; i++){
            CASE(N = rnd.nextInt(1,50), K = rnd.nextInt(2,50));
        }
    }
};