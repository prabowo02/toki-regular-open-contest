#include <tcframe/spec.hpp>
using namespace tcframe;

#include<bits/stdc++.h>
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
	int N, X;
	vector<int> A;
	int ANS;
    void InputFormat() {
        LINE(N);
        LINE(A % SIZE(N));
        LINE(X);
    }

    void OutputFormat() {
        LINE(ANS);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
    	CONS(1 <= N && N <= 8);
        CONS(1 <= X && X <= N);
    	CONS(isPermutation(A, N));
    }

    void Subtask1(){

    }

private:

    bool isPermutation(vector<int> V, int siz){
    	if(V.size() != siz)
    		return false;
    	sort(V.begin(), V.end());
    	for(int i = 0; i < V.size(); i++){
    		if(V[i] != i + 1)
    			return false;
    	}
    	return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1});
        Input({
            "3",
            "2 3 1",
            "3"
        });
        Output({
            "2"
        });
    }

    void TestGroup1() {
        Subtasks({1});

        CASE(N = 1, A = generateRandomPermutation(N), X = rnd.nextInt(1, N));
        CASE(N = 2, A = generateRandomPermutation(N), X = rnd.nextInt(1, N));
        CASE(N = 3, A = generateRandomPermutation(N), X = rnd.nextInt(1, N));
        CASE(N = 4, A = generateRandomPermutation(N), X = rnd.nextInt(1, N));
        CASE(N = 5, A = generateRandomPermutation(N), X = rnd.nextInt(1, N));
        CASE(N = 6, A = generateRandomPermutation(N), X = rnd.nextInt(1, N));
        CASE(N = 6, A = generateRandomPermutation(N), X = rnd.nextInt(1, N));
        CASE(N = 7, A = generateRandomPermutation(N), X = rnd.nextInt(1, N));
        CASE(N = 7, A = generateRandomPermutation(N), X = rnd.nextInt(1, N));
        CASE(N = 8, A = generateRandomPermutation(N), X = rnd.nextInt(1, N));
        CASE(N = 8, A = generateRandomPermutation(N), X = rnd.nextInt(1, N));
    }   
private:

    vector<int> generateRandomPermutation(int T){
        vector<int> ret(T);
        iota(ret.begin(), ret.end(), 1);
        rnd.shuffle(ret.begin(), ret.end());
        return ret;
    }
};
