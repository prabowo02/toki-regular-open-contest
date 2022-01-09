#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T, M;
    vector <int> N;

    vector <int> ans;

    void InputFormat() {
        LINE(T, M);
        LINES(N) % SIZE(T);
    }

    void OutputFormat() {
        LINES(ans) % SIZE(T);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(256);
    }

    bool check(vector <int> &V){
        for(auto i : V)
            if(i < 1 || i > 200000) return false;
        return true;
    }

    bool isPrime(int p) {
        for (int i = 2; i*i <= p; ++i) {
            if (p % i == 0) return false;
        }
        return true;
    }

    void Constraints() {
        CONS(1 <= T && T <= 200000);
        CONS(4e8 <= M && M <= 1e9 + 10);
        CONS(isPrime(M));
        CONS(check(N));
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "3 1000000007",
            "5",
            "1",
            "100",
        });
        Output({
            "7",
            "1",
            "592090280",
        });
    }

    vector <int> Primes = {
        1000000007,
        998244353,
        420691273,
        420691261,
        420691987,
        420691991,
        420691993,
        803428919,
        696972889,
        690003341,
        816022177,
        999999937,
        533841733,
        784878883,
        999727999,
    };

    void BeforeTestCase() {
        N.clear();
    }

    void RandomArray(){
        for(int i = 0; i < T; i++){
            N.push_back(rnd.nextInt(1, 200000));
        }
    }

    void Permute(){
        for(int i = 0; i < T; i++){
            N.push_back(i + 1);
        }
        rnd.shuffle(N.begin(), N.end());
    }

    void TestGroup1() {
        for(int i = 0; i < 5; i++){
            CASE(T = rnd.nextInt(100000, 200000), M = Primes[i], RandomArray());
        }
        for(int i = 0; i < 15; i++){
            CASE(T = 200000, M = Primes[i], Permute());
        }
    }
};
