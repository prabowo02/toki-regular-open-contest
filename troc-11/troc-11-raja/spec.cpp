#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    long long N, M;
    long long ans;

    void InputFormat() {
        LINE(N, M);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Subtask1() {
      Points(100);
    }
    void Constraints() {
        CONS(3 <= N && N <= 100000);
        CONS(3 <= M && M <= 100000);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1});
        Input({
            "3 3"
        });
        Output({
            "16"
        });
    }


    void SampleTestCase2() {
        Subtasks({1});
        Input({
            "4 3"
        });
        Output({
            "28"
        });
    }

    void SampleTestCase3() {
        Subtasks({1});
        Input({
            "10 10"
        });
        Output({
            "352"
        });
    }

    void TestGroup1() {
        Subtasks({1});
        CASE(N = 4, M = 4);
        CASE(N = 3, M = 10);
        CASE(N = 420, M = 69);
        CASE(N = 100000, M = 100000);
        for(int i = 0; i < 2; i++)
            CASE(N = rnd.nextInt(3, 100000), M = 100000);
        for(int i = 0; i < 2; i++)
            CASE(N = 100000, M = rnd.nextInt(3, 100000));
        for(int i = 0; i < 6; i++)
            CASE(N = rnd.nextInt(3, 100000), M = rnd.nextInt(3, 100000));
    }
};
