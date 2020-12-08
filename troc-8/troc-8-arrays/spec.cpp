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
	int N, K;
	vector <int> A, B, C, D;
	long long H;
	
	void InputFormat() {
		LINE(N,K);
		LINE(A%SIZE(N));
		LINE(B%SIZE(N));
		LINE(C%SIZE(N));
		LINE(D%SIZE(N));
	}
	
	void OutputFormat() {
		LINE(H);
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
    }
	
	void Constraints() {
		CONS(1<=N&&N<=1000);
		CONS(1<=K&&K<=1000000000);
		CONS(eachElementBetween(A,1,1000000000));
		CONS(eachElementBetween(B,1,1000000000));
		CONS(eachElementBetween(C,1,1000000000));
		CONS(eachElementBetween(D,1,1000000000));
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
			"2 18",
			"1 2",
			"3 4",
			"5 6",
			"7 8"
		});
		Output({
			"11"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		CASE(N=1,K=928364810,A={146354738},B={274537280},C={93647382},D={218463046});
		CASE(N=1,K=584930475,A={274839026},B={184658302},C={184635802},D={139572021});
		CASE(N=1000,K=1000000000,A=fillAll(N,K),B=fillAll(N,K),C=fillAll(N,K),D=fillAll(N,K));
		
		CASE(N=749,K=1359841,A=fillPeriod(N,104582,73),B=fillPeriod(N,5372,19),C=fillPeriod(N,927354,133),D=fillPeriod(N,15326,97));
		CASE(N=1000,K=583635901,A=fillPeriod(N,1,1),B=fillPeriod(N,1000,1000),C=fillPeriod(N,1000000,1000000),D=fillPeriod(N,5,5));
		CASE(N=833,K=rnd.nextInt(1,300000),
			A=fillPeriod(N,rnd.nextInt(1,100000),rnd.nextInt(1,100)),
			B=fillPeriod(N,rnd.nextInt(1,100000),rnd.nextInt(1,100)),
			C=fillPeriod(N,rnd.nextInt(1,100000),rnd.nextInt(1,100)),
			D=fillPeriod(N,rnd.nextInt(1,100000),rnd.nextInt(1,100))
		);
		
		for (int i=0;i<2;i++) {
			CASE(N=rnd.nextInt(1,1000),K=rnd.nextInt(1,1000000000),A=randomBetween(N,1,500000000),B=randomBetween(N,1,500000000),C=randomBetween(N,1,500000000),D=randomBetween(N,1,500000000));
			CASE(N=rnd.nextInt(1,1000),K=rnd.nextInt(1,1000000000),A=randomBetween(N,1,1000000000),B=randomBetween(N,1,1000000000),C=randomBetween(N,1,1000000000),D=randomBetween(N,1,1000000000));
		}
	}
	
	vector <int> randomBetween(int size,int mins,int maks) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			ret.push_back(rnd.nextInt(mins,maks));
		}
		
		return ret;
	}
	
	vector <int> fillPeriod(int size,int awa,int frek) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			ret.push_back(awa);
			awa+=frek;
		}
		
		for (int i=size-1;i;i--) {
			swap(ret[i],ret[rnd.nextInt(0,i)]);
		}
		
		return ret;
	}
	
	vector <int> fillAll(int size,int val) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			ret.push_back(val);
		}
		
		return ret;
	}
};
