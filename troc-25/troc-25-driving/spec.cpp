#include <tcframe/spec.hpp>
using namespace tcframe;

long long min_dist(long long T, long long F){
    if(F > T){
        return (long long)1e18 + 1;
    }
    return F*(F-1)/2;
}

long long max_dist(long long T, long long F){
    if(F > T){
        return -1;
    }
    else{
        long long ret = F * (F-1)/2;
        if((T - (F-1)) % 2 == 0){
            T -= F-1;
            ret += ((F + (F + T/2 - 1)) * T)/2;
        }
        else{
            T -= F-1;
            ret += ((F + (F + T/2 - 1)) * (T-1))/2 + (F + T/2);
        }
        return ret;
    }
}

class ProblemSpec : public BaseProblemSpec {
protected:
    long long T, F, D;
    string ans;

    void InputFormat() {
        LINE(T, F, D);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= T && T <= 1000000);
        CONS(1 <= F && F <= 1000000);
        CONS(1 <= D && D <= (long long) 1e18);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "6 2 14"
        });
        Output({
            "YES"
        });
    }

    void SampleTestCase2() {
        Input({
            "4 3 10"
        });
        Output({
            "NO"
        });
    }

    void TestGroup1() {
        // T > F
        CASE(T = rnd.nextInt(3, 1000000), F = T-1, D = min_dist(T, F) - 1);
        CASE(T = rnd.nextInt(3, 1000000), F = T-1, D = min_dist(T, F));
        CASE(T = rnd.nextInt(2, 1000000), F = T-1, D = max_dist(T, F));
        CASE(T = rnd.nextInt(2, 1000000), F = T-1, D = max_dist(T, F) + 1);

        CASE(T = 999999, F = 785123, D = min_dist(999999, 785123) - 1);
        CASE(T = 999999, F = 785123, D = min_dist(999999, 785123));
        CASE(T = 999999, F = 785123, D = max_dist(999999, 785123));
        CASE(T = 999999, F = 785123, D = max_dist(999999, 785123) + 1);

        CASE(T = 1000000, F = 834523, D = min_dist(1000000, 834523) - 1);
        CASE(T = 1000000, F = 834523, D = min_dist(1000000, 834523));
        CASE(T = 1000000, F = 834523, D = max_dist(1000000, 834523));
        CASE(T = 1000000, F = 834523, D = max_dist(1000000, 834523) + 1);

        // T < F
        CASE(T = rnd.nextInt(1, 999999), F = rnd.nextInt(T + 1, 1000000), D = rnd.nextLongLong((long long) 1e17, (long long) 1e18));
        CASE(T = rnd.nextInt(1, 999999), F = rnd.nextInt(T + 1, 1000000), D = 1);
        CASE(T = rnd.nextInt(1, 999999), F = T+1, D = rnd.nextLongLong((long long) 1e17, (long long) 1e18));
        CASE(T = rnd.nextInt(1, 999999), F = T+1, D = 1);

        // T = F
        CASE(T = 1, F = 1, D = 1);
        CASE(T = 1, F = 1, D = 2);
        CASE(T = rnd.nextInt(2, 1000000), F = T, D = min_dist(T, F) - 1);
        CASE(T = rnd.nextInt(2, 1000000), F = T, D = min_dist(T, F));
        CASE(T = rnd.nextInt(1, 1000000), F = T, D = max_dist(T, F));
        CASE(T = rnd.nextInt(1, 1000000), F = T, D = max_dist(T, F) + 1);
    }
};
