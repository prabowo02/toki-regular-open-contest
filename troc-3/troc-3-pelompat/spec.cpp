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
	int N, Q;
	vector <int> H;
	vector <int> X, Y, Z;
	vector <int> P;
	
	void InputFormat() {
		LINE(N);
		LINE(H%SIZE(N));
		LINE(Q);
		LINES(X,Y,Z)%SIZE(Q);
	}
	
	void OutputFormat() {
		LINES(P)%SIZE(Q);
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(256);
    }
	
	void Constraints() {
		CONS(1<=N&&N<=10000);
		CONS(1<=Q&&Q<=100);
		CONS(eachElementBetween(H,1,100));
		CONS(eachElementBetween(X,1,N));
		CONS(eachElementBetween(Y,1,N));
		CONS(eachElementBetween(Z,0,1000000));
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
			"4",
			"3 2 5 3",
			"4",
			"1 4 4",
			"2 3 5",
			"1 2 10",
			"2 1 10"
		});
		Output({
			"8",
			"57",
			"0",
			"1023"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		for (int i=0;i<3;i++) {
			CASE(N=100,Q=100,H=allRandom(N,5,10),X=allRandom(Q,1,N),Y=allRandom(Q,1,N),Z=allRandom(Q,500,1000));
		}
		
		for (int i=0;i<3;i++) {
			CASE(N=10000,Q=100,H=allRandom(N,1,100),X=allRandom(Q,1,N),Y=allRandom(Q,1,N),Z=fillAll(Q,0));
		}
		
		for (int i=0;i<3;i++) {
			CASE(N=10000,Q=100,H=allRandom(N,1,100),X=allRandom(Q,1,N),Y=allRandom(Q,1,N),Z=fillAll(Q,1000000));
		}
		
		for (int i=0;i<3;i++) {
			CASE(N=rnd.nextInt(1,10000),Q=100,H=allRandom(N,1,100),X=allRandom(Q,1,N),Y=allRandom(Q,1,N),Z=allRandom(Q,0,5));
		}
		
		for (int i=0;i<3;i++) {
			CASE(N=rnd.nextInt(1,10000),Q=100,H=allRandom(N,1,100),X=allRandom(Q,1,N),Y=allRandom(Q,1,N),Z=allRandom(Q,999000,1000000));
		}
		
		for (int i=0;i<5;i++) {
			CASE(N=rnd.nextInt(1,10000),Q=100,H=allRandom(N,1,100),X=allRandom(Q,1,N),Y=allRandom(Q,1,N),Z=allRandom(Q,0,1000000));
		}
	}
	
	vector <int> fillAll(int size,int fill) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			ret.push_back(fill);
		}
		
		return ret;
	}
	
	vector <int> allRandom(int size,int mins,int maks) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			ret.push_back(rnd.nextInt(mins,maks));
		}
		
		return ret;
	}
};
