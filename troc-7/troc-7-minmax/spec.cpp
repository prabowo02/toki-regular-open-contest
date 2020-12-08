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
	int N;
	vector <int> A, L, R;
	
	void InputFormat() {
		LINE(N);
		LINE(L%SIZE(N));
		LINE(R%SIZE(N));
	}
	
	void OutputFormat1() {
		LINE(A%SIZE(N));
	}
	
	void OutputFormat2() {
		LINE(A%SIZE(1));
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
    }
	
	void Constraints() {
		CONS(1<=N&&N<=100000);
		CONS(eachElementBetween(L,1,1000000));
		CONS(eachElementBetween(R,1,1000000));
    }

    void StyleConfig(){
    	CustomScorer();
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
			"5",
			"4 2 1 9 10",
			"9 3 5 9 15"
		});
		Output({
			"5 2 3 9 14"
		});
	}
	
	void SampleTestCase2() {
		Subtasks({1});
		Input({
			"1",
			"2",
			"3"
		});
		Output({
			"-1"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		CASE(N=84023,L=randomBetween(N,1,1000000),R=L);
		CASE(N=92537,L=randomBetween(N,1,1000000),R=L);
		CASE(N=100000,L=randomBetween(N,1,1000000),R=L);
		
		CASE(N=70162,L=randomBetween(N,1,999999),R=L,R[rnd.nextInt(0,N-1)]++);
		CASE(N=90936,L=randomBetween(N,1,999999),R=L,R[rnd.nextInt(0,N-1)]++);
		CASE(N=100000,L=randomBetween(N,1,999999),R=L,R[rnd.nextInt(0,N-1)]++);
		
		CASE(N=79203,L=randomBetween(N,1,999998),R=L,R[rnd.nextInt(0,N-1)]+=2);
		CASE(N=100000,L=randomBetween(N,1,999998),R=L,R[rnd.nextInt(0,N-1)]+=2);
		
		CASE(N=92401,L=randomBetween(N,1,999998),R=L,R[rnd.nextInt(0,N-1)]++,R[rnd.nextInt(0,N-1)]++);
		CASE(N=100000,L=randomBetween(N,1,999998),R=L,R[rnd.nextInt(0,N-1)]++,R[rnd.nextInt(0,N-1)]++);
		
		CASE(N=50242,L=randomBetween(N,1,999997),R=L,R[rnd.nextInt(0,N-1)]++,R[rnd.nextInt(0,N-1)]++,R[rnd.nextInt(0,N-1)]++);
		CASE(N=69760,L=randomBetween(N,1,999997),R=L,R[rnd.nextInt(0,N-1)]++,R[rnd.nextInt(0,N-1)]++,R[rnd.nextInt(0,N-1)]++);
		CASE(N=100000,L=randomBetween(N,1,999997),R=L,R[rnd.nextInt(0,N-1)]++,R[rnd.nextInt(0,N-1)]++,R[rnd.nextInt(0,N-1)]++);
		
		CASE(N=100000,L=randomBetween(N,1,1),R=randomBetween(N,1000000,1000000));

		CASE(N = 100000, L = randomBetween(N, 1, 500000), R = randomBetween(N, 500000, 1000000));
		CASE(N = 100000, L = randomBetween(N, 1, 5), R = randomBetween(N, 5, 9));
	}
	
	vector <int> randomBetween(int size,int mins,int maks) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			ret.push_back(rnd.nextInt(mins,maks));
		}
		
		return ret;
	}
};
