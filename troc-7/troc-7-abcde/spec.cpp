#include <tcframe/spec.hpp>
using namespace tcframe;

#include<bits/stdc++.h>
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
	int P, Q, R, S, T;
    int A, B, C, D, E;
    void InputFormat() {
        LINE(P, Q, R, S, T);
    }

    void OutputFormat() {
        LINE(A, B, C, D, E);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
    	CONS(1 <= P && P <= 64);
        CONS(1 <= Q && Q <= 64);
        CONS(1 <= R && R <= 64);
        CONS(1 <= S && S <= 64);
        CONS(1 <= T && T <= 64);
    }

    void Subtask1(){

    }

};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1});
        Input({
            "4 4 4 4 4"
        });
        Output({
            "2 2 2 2 2"
        });
    }

    void SampleTestCase2() {
        Subtasks({1});
        Input({
            "8 24 6 10 5"
        });
        Output({
            "1 8 3 2 5"
        });
    }

    void TestGroup1() {
        Subtasks({1});
        
        for(int i = 0; i < 15; i++)
            CASE(tie(P, Q, R, S, T) = generateTuple());
        CASE(P = 1, Q = 1, R = 1, S = 1, T = 1);
        for(int i = 0; i < 8; i++)
            CASE(tie(P, Q, R, S, T) = prima());
        for(int i = 0; i < 8; i++)
            CASE(tie(P, Q, R, S, T) = magicNumber());
    }   

private:

    tuple<int, int, int, int, int> generateTuple(){
        int a, b, c, d, e;
        a = rnd.nextInt(1, 8);
        b = rnd.nextInt(1, 8);
        c = rnd.nextInt(1, 8);
        d = rnd.nextInt(1, 8);
        e = rnd.nextInt(1, 8);
        return make_tuple(a * b, b * c, c * d, d * e, e * a);
    }

    tuple<int, int, int, int, int> prima(){
        vector<int> prime(4);
        prime = {2, 3, 5, 7};
        int a, b, c, d, e;
        a = rnd.nextInt(0, 3);
        b = rnd.nextInt(0, 3);
        c = rnd.nextInt(0, 3);
        d = rnd.nextInt(0, 3);
        e = rnd.nextInt(0, 3);
        a = prime[a];
        b = prime[b];
        c = prime[c];
        d = prime[d];
        e = prime[e];
        return make_tuple(a * b, b * c, c * d, d * e, e * a);
    }

    tuple<int, int, int, int, int> magicNumber(){
        vector<int> bil(4);
        bil = {8, 7, 6, 5};
        int a, b, c, d, e;
        a = rnd.nextInt(0, 3);
        b = rnd.nextInt(0, 3);
        c = rnd.nextInt(0, 3);
        d = rnd.nextInt(0, 3);
        e = rnd.nextInt(0, 3);
        a = bil[a];
        b = bil[b];
        c = bil[c];
        d = bil[d];
        e = bil[e];
        return make_tuple(a * b, b * c, c * d, d * e, e * a);
    }

};
