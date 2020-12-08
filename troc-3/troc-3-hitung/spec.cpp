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

template<typename data>
bool slowlyIncreasing(const vector<data> &V) {
	data before;
	before=V[0];
	
	for (data x : V) {
		if (x!=before&&x!=before+1) {
			return 0;
		}
		
		before=x;
	}
	
	return 1;
}

class ProblemSpec : public BaseProblemSpec {
protected:
	int N;
	vector <int> A;
	int H;
	
	void InputFormat() {
		LINE(N);
		LINE(A%SIZE(N+1));
	}
	
	void OutputFormat() {
		LINE(H);
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
    }
	
	void Constraints() {
		CONS(1<=N&&N<=100000);
		CONS(1<=A[0]&&A[N]<=1000000000);
		CONS(slowlyIncreasing(A));
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
			"2",
			"3 4 5"
		});
		Output({
			"3"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		CASE(N=1,A={1,2});
		CASE(N=1,A={6,6});
		CASE(N=1,A={983635287,983635288});
		CASE(N=2,A={14,15,15});
		CASE(N=2,A={20,21,22});
		CASE(N=2,A={37,37,37});
		
		CASE(N=10,A=smallCase(N,1000,0,1));
		CASE(N=100,A=smallCase(N,1000,0,1));
		CASE(N=1000,A=smallCase(N,1000000,0,1));
		CASE(N=10000,A=smallCase(N,1000000,0,1));
		CASE(N=100000,A=smallCase(N,1000000000,0,1));
		
		CASE(N=10,A=smallCase(N,1000,1,1));
		CASE(N=100,A=smallCase(N,1000,1,1));
		CASE(N=1000,A=smallCase(N,1000000,1,1));
		CASE(N=10000,A=smallCase(N,1000000,1,1));
		CASE(N=100000,A=smallCase(N,1000000000,1,1));
		
		CASE(N=10,A=bigCase(N,1000));
		CASE(N=100,A=bigCase(N,1000));
		CASE(N=1000,A=bigCase(N,1000000));
		CASE(N=10000,A=bigCase(N,1000000));
		CASE(N=100000,A=bigCase(N,1000000000));
		
		CASE(N=10,A=smallCase(N,1000,1,3));
		CASE(N=100,A=smallCase(N,1000,2,5));
		CASE(N=1000,A=smallCase(N,1000000,4,7));
		CASE(N=10000,A=smallCase(N,1000000,5,19));
		CASE(N=100000,A=smallCase(N,1000000000,27,92));
		
		for (int i=0;i<10;i++) {
			CASE(N=rnd.nextInt(99000,100000),A=smallCase(N,1000000000,1,100000));
		}
	}
	
	vector <int> bigCase(int size,int pos) {
		vector <int> ret;
		ret.clear();
		
		int id;
		id=rnd.nextInt(0,size-1);
		ret.push_back(rnd.nextInt(1,pos-N+1));
		
		for (int i=0;i<size;i++) {
			if (i==id) {
				ret.push_back(ret[i]);
			}
			else {
				ret.push_back(ret[i]+1);
			}
		}
		
		return ret;
	}
	
	vector <int> smallCase(int size,int pos,int a,int b) {
		vector <int> ret;
		ret.clear();
		
		ret.push_back(rnd.nextInt(1,pos-N));
		
		for (int i=0;i<size;i++) {
			if (rnd.nextInt(1,b)<=a) {
				ret.push_back(ret[i]);
			}
			else {
				ret.push_back(ret[i]+1);
			}
		}
		
		return ret;
	}
};
