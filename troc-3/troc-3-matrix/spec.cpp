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
	int N, M;
	vector <int> A, B;
	int H;
	
	void InputFormat() {
		LINE(N,M);
		LINE(A%SIZE(N));
		LINE(B%SIZE(M));
	}

	void OutputFormat() {
  }
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
  }

  void StyleConfig() {
    InteractiveEvaluator();
  }
	
	void Constraints() {
		CONS(1<=N&&N<=1000);
		CONS(1<=M&&M<=1000);
		CONS(eachElementBetween(A,0,(1<<30)-1));
    }
	
	void Subtask1() {
		Points(100);
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	// TODO: make it the same with sample (e.g. if there are two scenario, make 2 sample tc)
	void SampleTestCase1() {
		Subtasks({1});
		Input({
			"3 2",
			"1 2 3",
			"0 1"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		CASE(N=4,M=8,A=allRandom(N,10),B=allRandom(M,10));
		CASE(N=10,M=10,A=allRandom(N,10),B=allRandom(M,10));
		CASE(N=100,M=100,A=allRandom(N,10),B=allRandom(M,10));
		CASE(N=100,M=1000,A=allRandom(N,10),B=allRandom(M,10));
		CASE(N=1000,M=100,A=allRandom(N,10),B=allRandom(M,10));
		CASE(N=1000,M=1000,A=allRandom(N,10),B=allRandom(M,10));
		
		CASE(N=4,M=8,A=allRandom(N,30),B=allRandom(M,30));
		CASE(N=10,M=10,A=allRandom(N,30),B=allRandom(M,30));
		CASE(N=100,M=100,A=allRandom(N,30),B=allRandom(M,30));
		CASE(N=100,M=1000,A=allRandom(N,30),B=allRandom(M,30));
		CASE(N=1000,M=100,A=allRandom(N,30),B=allRandom(M,30));
		CASE(N=1000,M=1000,A=allRandom(N,30),B=allRandom(M,30));
		
		CASE(N=100,M=100,A=allEmpty(N),B=allEmpty(M));
		CASE(N=1000,M=1000,A=allEmpty(N),B=allEmpty(M));
		
		CASE(N=100,M=100,A=allRandom(N,20),B=allEmpty(M));
		CASE(N=1000,M=1000,A=allRandom(N,30),B=allEmpty(M));
		
		CASE(N=100,M=100,A=allEmpty(N),B=allRandom(M,20));
		CASE(N=1000,M=1000,A=allEmpty(N),B=allRandom(M,30));

		for (int i = 0 ; i < 10 ; i++) {
			CASE(N = rnd.nextInt(990, 1000), M = rnd.nextInt(990, 1000),
			     A = allRandom(N, 30), B = allRandom(M, 30));
		}
	}
	
	vector <int> allEmpty(int size) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			ret.push_back(0);
		}
		
		return ret;
	}
	
	vector <int> allRandom(int size,int bit) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			ret.push_back(rnd.nextInt(0,(1<<bit)-1));
		}
		
		return ret;
	}
};
