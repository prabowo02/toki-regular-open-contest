#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, M;
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

    void Constraints() {
        CONS(1 <= N && N <= 1e9);
        CONS(1 <= M && M <= 1e9);
    }
    void Subtask1() {}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1});
        Input({
            "4 4"
        });
        Output({
            "4"
        });
    }
    void SampleTestCase2() {
        Subtasks({1});
        Input({
            "3 3"
        });
        Output({
            "-1"
        });
    }
    void SampleTestCase3() {
        Subtasks({1});
        Input({
            "5 9"
        });
        Output({
            "0"
        });
    }
    void SampleTestCase4() {
        Subtasks({1});
        Input({
            "24 7"
        });
        Output({
            "24"
        });
    }

    void TestGroup1() {
        Subtasks({1});
        //Genap semua
        for(int i=0; i<1; i++){
            CASE(N = 2*rnd.nextInt(1,1e4), M = 2*rnd.nextInt(1,1e4));
        }
        for(int i=0; i<1; i++){
            CASE(N = 2*rnd.nextInt(1e4,1e9/2), M = 2*rnd.nextInt(1e4,1e9/2));
        }
        CASE(N=2, M=2);
        CASE(N=1e9, M=1e9);
        //Genap-Ganjil
        for(int i=0; i<1; i++){
            CASE(N = 2*rnd.nextInt(1,1e4)-i%2, M = 2*rnd.nextInt(1,1e4)-(i+1)%2);
        }
        for(int i=3; i<4; i++){
            CASE(N = 2*rnd.nextInt(1e4,1e9/2)-i%2, M = 2*rnd.nextInt(1e4,1e9/2)-(i+1)%2);
        }
        CASE(N=1, M=2);
        CASE(N=4, M=1);
        CASE(N=3, M=2);
        CASE(N=3, M=4);
        CASE(N=1, M=rnd.nextInt(1e4,1e9/2)*2);
        //Ganjil semua
        CASE(N = 1, M = 2*rnd.nextInt(1,1e9/2)-1);
        CASE(N = 2*rnd.nextInt(1,1e9/2)-1, M = 3);
        CASE(N = 3, M = 2*rnd.nextInt(1,1e9/2)-1);
        CASE(N=5, M=5);
        CASE(N=5, M=7);
        CASE(N=7, M=7);
        CASE(N=7, M=9);
        CASE(N=9, M=9);
        CASE(N=9, M=5);
        CASE(N=1, M=1);
        for(int i=0; i<2; i++){
            CASE(N = 2*rnd.nextInt(1,1e4)-1, M = 2*rnd.nextInt(1,1e4)-1);
        }
        for(int i=0; i<6; i++){
            CASE(N = 2*rnd.nextInt(1e4,1e9/2)-1, M = 2*rnd.nextInt(1e4,1e9/2)-1);
        }
    }
};