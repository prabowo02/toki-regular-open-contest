#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

template<typename data>
bool eachElementBetween(const vector<data> &V,data mins,data maks) {
	for (data x : V) {
		if (x<mins||x>maks) {
			return 0;
		}
	}
	
	return 1;
}

class ProblemSpec : public BaseProblemSpec {
protected:
	int X, Y, Z;
	int H;
	
	void InputFormat() {
		LINE(X,Y,Z);
	}
	
	void OutputFormat() {
		LINE(H);
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
    }
	
	void Constraints() {
		CONS(0<X&&X<=10000000);
		CONS(X%10000==0);
		CONS(0<=Y&&Y<=100);
		CONS(0<=Z&&Z<=1000);
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
			"10000 20 10"
		});
		Output({
			"8800"
		});
	}
	
	void SampleTestCase2() {
		Subtasks({1});
		Input({
			"20000 1 1"
		});
		Output({
			"19998"
		});
	}
	
	void SampleTestCase3() {
		Subtasks({1});
		Input({
			"10000 0 101"
		});
		Output({
			"20100"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		CASE(X=rnd.nextInt(1,1000)*10000,Y=0,Z=rnd.nextInt(0,1000));
		CASE(X=rnd.nextInt(1,1000)*10000,Y=43,Z=rnd.nextInt(0,1000));
		CASE(X=rnd.nextInt(1,1000)*10000,Y=100,Z=rnd.nextInt(0,1000));
		CASE(X=rnd.nextInt(1,1000)*10000,Y=rnd.nextInt(0,100),Z=0);
		CASE(X=rnd.nextInt(1,1000)*10000,Y=rnd.nextInt(0,100),Z=27);
		CASE(X=rnd.nextInt(1,1000)*10000,Y=rnd.nextInt(0,100),Z=100);
		CASE(X=rnd.nextInt(1,1000)*10000,Y=rnd.nextInt(0,100),Z=1000);
		
		for (int i=0;i<3;i++) {
			CASE(X=rnd.nextInt(1,1000)*10000,Y=rnd.nextInt(0,100),Z=rnd.nextInt(0,100));
			CASE(X=rnd.nextInt(1,1000)*10000,Y=rnd.nextInt(0,100),Z=rnd.nextInt(0,1000));
		}
	}
};
