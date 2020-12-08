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
	vector <int> P;
	vector <int> R;
	
	void InputFormat() {
		LINE(N,M);
		LINE(P%SIZE(N));
	}
	
	void OutputFormat1() {
		LINE(R%SIZE(N));
	}

	void OutputFormat2() {
		LINE(R%SIZE(1));
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
    }
	
	void Constraints() {
		CONS(1<=N&&N<=100000);
		CONS(1<=M&&M<=100000);
		CONS(eachElementBetween(P,0,M-1));
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
			"7 3",
			"1 0 1 0 2 1 2"
		});
		Output({
			"7 6 4 3 5 1 2"
		});
	}

	void SampleTestCase2() {
		Subtasks({1});

		Input({
			"4 10",
			"2 3 1 5"
		});
		Output({
			"-1"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		CASE(N=5,M=3,P={0,1,0,2,2});
		CASE(N=4,M=5,P={0,1,2,4});
		CASE(N=5,M=10,P={1,3,2,2,4});
		CASE(N=7,M=5,P={2,1,0,3,2,4,1});
		
		CASE(N=100,M=1,P=permutation(N,M,0,1));
		CASE(N=1000,M=1,P=permutation(N,M,0,1));
		CASE(N=100000,M=1,P=permutation(N,M,0,1));
		
		CASE(N=1,M=N,P=permutation(N,M,0,1));
		CASE(N=rnd.nextInt(2,99999),M=N,P=permutation(N,M,0,1));
		CASE(N=100000,M=N,P=permutation(N,M,0,1));
		
		CASE(N=rnd.nextInt(1000,100000),M=rnd.nextInt(1,100),P=permutation(N,M,0,1));
		CASE(N=rnd.nextInt(1000,100000),M=N-rnd.nextInt(1,100),P=permutation(N,M,0,1));
		
		CASE(N=1,M=5,P=permutation(N,M,0,1));
		CASE(N=6277,M=50283,P=permutation(N,M,0,1));
		CASE(N=99999,M=100000,P=permutation(N,M,0,1));
		
		CASE(N=rnd.nextInt(1,100),M=rnd.nextInt(1000,100000),P=permutation(N,M,0,1));
		CASE(N=rnd.nextInt(100,50000),M=N+rnd.nextInt(1,10000),P=permutation(N,M,0,1));
		
		CASE(N=rnd.nextInt(1,100),M=rnd.nextInt(1000,100000),P=permutation(N,M,3,100));
		CASE(N=rnd.nextInt(100,50000),M=N+rnd.nextInt(1,10000),P=permutation(N,M,1,10000));
		
		CASE(N=rnd.nextInt(1,100),M=rnd.nextInt(1000,100000),P=permutation(N,M,0,1),P[rnd.nextInt(0,N-1)]=0);
		CASE(N=rnd.nextInt(100,50000),M=N+rnd.nextInt(1,10000),P=permutation(N,M,0,1),P[rnd.nextInt(0,N-1)]=0);
		
		CASE(N=rnd.nextInt(1,1000),M=N,P=permutation(N,M,0,1));
		CASE(N=rnd.nextInt(1000,100000),M=N,P=permutation(N,M,0,1));
		
		for (int i=0;i<3;i++) {
			CASE(N=rnd.nextInt(1,100000),M=rnd.nextInt(1,100000),P=dummy(N,M));
		}
		
		for (int i=0;i<5;i++) {
			CASE(N=rnd.nextInt(1,100000),M=rnd.nextInt(1,100000),P=permutation(N,M,1,rnd.nextInt(1,100000)));
		}
	}
	
	vector <int> dummy(int size,int modulo) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			ret.push_back(i%modulo);
		}
		
		for (int i=size-1;i>=0;i--) {
			swap(ret[i],ret[rnd.nextInt(0,i)]);
		}
		
		return ret;
	}
	
	vector <int> permutation(int size,int modulo,int a,int b) {
		vector <int> ret;
		ret.clear();
		
		for (int i=1;i<=size;i++) {
			ret.push_back(i%modulo);
		}
		
		for (int i=size-1;i>=0;i--) {
			swap(ret[i],ret[rnd.nextInt(0,i)]);
		}
		
		for (int i=0;i<size;i++) {
			if (rnd.nextInt(1,b)<=a) {
				ret[i]=rnd.nextInt(0,modulo-1);
			}
		}
		
		return ret;
	}
};
