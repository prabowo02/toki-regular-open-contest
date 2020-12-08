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

bool isTree(const vector<int> &V) {
	int now;
	now=1;
	
	for (int x : V) {
		now++;
		
		if (x>=now || x < 1) {
			return 0;
		}
	}
	
	return 1;
}

class ProblemSpec : public BaseProblemSpec {
protected:
	int N;
	vector <int> A;
	vector <int> P;
	long long H;
	
	void InputFormat() {
		LINE(N);
		LINE(A%SIZE(N));
		LINE(P%SIZE(N-1));
	}
	
	void OutputFormat() {
		LINE(H);
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
    }
	
	void Constraints() {
		CONS(2<=N&&N<=100000);
		CONS(eachElementBetween(A,0,(1<<20)-1));
		CONS(isTree(P));
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
			"2 3 5 1 6",
			"1 1 2 2"
		});
		Output({
			"37"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		// CASE(N=1,A={102},P={});
		// CASE(N=1,A={rnd.nextInt(0,(1<<20)-1)},P={});
		CASE(N=2,A=allRandom(N,0,(1<<20)-1),P={1});
		
		CASE(N=100,A=allRandom(N,0,(1<<20)-1),P=treeA(N));
		CASE(N=100000,A=allRandom(N,0,(1<<20)-1),P=treeA(N));
		
		CASE(N=1000,A=allRandom(N,0,(1<<20)-1),P=treeB(N));
		CASE(N=100000,A=allRandom(N,0,(1<<20)-1),P=treeB(N));
		
		CASE(N=100,A=allRandom(N,0,(1<<20)-1),P=treeC(N));
		CASE(N=100000,A=allRandom(N,0,(1<<20)-1),P=treeC(N));
		
		CASE(N=1000,A=allRandom(N,0,(1<<20)-1),P=treeD(N));
		CASE(N=100000,A=allRandom(N,0,(1<<20)-1),P=treeD(N));
		
		for (int i=0;i<3;i++) {
			CASE(N=100000,A=allRandom(N,0,(1<<20)-1),P=treeE(N));
		}
		
		for (int i=0;i<5;i++) {
			CASE(N=100000,A=allRandom(N,0,(1<<20)-1),P=treeRandom(N));
		}
	}
	
	vector <int> treeA(int size) {
		vector <int> ret;
		ret.clear();
		
		for (int i=1;i<size;i++) {
			ret.push_back(i);
		}
		
		return ret;
	}
	
	vector <int> treeB(int size) {
		vector <int> ret;
		ret.clear();
		
		for (int i=1;i<size;i++) {
			ret.push_back((i+1)/2);
		}
		
		return ret;
	}
	
	vector <int> treeC(int size) {
		vector <int> ret;
		ret.clear();
		
		for (int i=1;i<size;i++) {
			ret.push_back(i-((i+1)%2));
		}
		
		return ret;
	}
	
	vector <int> treeD(int size) {
		vector <int> ret;
		ret.clear();
		
		for (int i=1;i<size;i++) {
			ret.push_back(1);
		}
		
		return ret;
	}
	
	vector <int> treeE(int size) {
		vector <int> ret;
		ret.clear();
		
		for (int i=1;i<size;i++) {
			ret.push_back(0);
		}
		
		for (int i=1;i<size;i++) {
			ret[rnd.nextInt(0,i-1)]++;
		}
		
		int now;
		now=size-2;
		
		for (int i=size-2;i>=0;i--) {
			for (int j=ret[i];j>0;j--) {
				ret[now]=i+1;
				now--;
			}
		}
		
		return ret;
	}
	
	vector <int> treeRandom(int size) {
		vector <int> ret;
		ret.clear();
		
		for (int i=1;i<size;i++) {
			ret.push_back(rnd.nextInt(1,i));
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
