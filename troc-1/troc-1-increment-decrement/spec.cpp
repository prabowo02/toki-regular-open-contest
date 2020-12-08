#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:

    int N, Q;
    long long res;
    vector<int> cmd, pos, val;

    void InputFormat() {
        LINE(N, Q);
        LINES(cmd, pos, val) % SIZE(Q);
    }

    void OutputFormat() {
        LINE(res);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= N && N <= 1e9);
        CONS(1 <= Q && Q <= 1e5);
        CONS(eachElementBetween(cmd, 1, 2));
        CONS(eachElementBetween(pos, 1, N));
        CONS(eachElementBetween(val, 1, 1e9));
    }

    void Subtask1() {
        Points(100);
    }

private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        for (long long x : v) {
            if (x < lo || x > hi) {
                return false;
            }
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1});
        Input({
            "6 3",
            "1 2 3",
            "2 3 5",
            "1 4 1"
        });
        Output({
            "5"
        });
    }

    void BeforeTestCase() {
        cmd.clear();
        pos.clear();
        val.clear();
    }

    void TestGroup1() {
        Subtasks({1});
        // Test case without corner
        for(int i = 1; i <= 3; i++)
            CASE(N = rnd.nextInt(2, 1000), Q = rnd.nextInt(1, 1000), noCornerQuery(N, Q));
        for(int i = 1; i <= 3; i++) 
            CASE(N = rnd.nextInt(2, 1e5), Q = rnd.nextInt(1, 1e5), noCornerQuery(N, Q));
        for(int i = 1; i <= 3; i++) 
            CASE(N = rnd.nextInt(2, 1e9), Q = rnd.nextInt(1, 1e5), noCornerQuery(N, Q));

        // Test case random
        for(int i = 1; i <= 3; i++)
            CASE(N = 1, Q = rnd.nextInt(1, 1000), cornerQuery(N, Q));
        for(int i = 1; i <= 3; i++)
            CASE(N = rnd.nextInt(1, 1000), Q = rnd.nextInt(1, 1000), randomQuery(N, Q));
        for(int i = 1; i <= 3; i++)
            CASE(N = rnd.nextInt(1, 1e5), Q = rnd.nextInt(1, 1e5), randomQuery(N, Q));
        for(int i = 1; i <= 3; i++)
            CASE(N = rnd.nextInt(1, 1e9), Q = rnd.nextInt(1, 1e5), randomQuery(N, Q));

        // Test case full corner
        for(int i = 1; i <= 3; i++)
            CASE(N = 1, Q = rnd.nextInt(1, 1000), cornerQuery(N, Q));
        for(int i = 1; i <= 3; i++)
            CASE(N = rnd.nextInt(1, 1000), Q = rnd.nextInt(1, 1000), cornerQuery(N, Q));
        for(int i = 1; i <= 3; i++)
            CASE(N = rnd.nextInt(1, 1e5), Q = rnd.nextInt(1, 1e5), cornerQuery(N, Q));
        for(int i = 1; i <= 3; i++)
            CASE(N = rnd.nextInt(1, 1e9), Q = rnd.nextInt(1, 1e5), cornerQuery(N, Q));
    }

private:
    void noCornerQuery(int N, int Q) {
        assert(N > 1);
        for(int i = 0; i < Q; i++) {
            cmd.push_back(rnd.nextInt(1, 2));
            pos.push_back(rnd.nextInt(1, N-1));
            val.push_back(rnd.nextInt(1, 1e9));
        }
    }

    void randomQuery(int N, int Q) {
        for(int i = 0; i < Q; i++) {
            cmd.push_back(rnd.nextInt(1, 2));
            if(rnd.nextInt(0, 1)) {
                pos.push_back(N);
            }
            else {
                pos.push_back(rnd.nextInt(1, N-1));
            }
            val.push_back(rnd.nextInt(1, 1e9));
        }
    }

    void cornerQuery(int N, int Q) {
        for(int i = 0; i < Q; i++) {
            cmd.push_back(rnd.nextInt(1, 2));
            pos.push_back(N);
            val.push_back(rnd.nextInt(1, 1e9));
        }
    }
};