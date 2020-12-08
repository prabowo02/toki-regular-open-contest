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
bool eachRowBetween(const vector< vector <data> > &V,data mins,data maks) {
	for (vector <data> x : V) {
		if (!eachElementBetween(x,mins,maks)) {
			return 0;
		}
	}
	
	return 1;
}

class ProblemSpec : public BaseProblemSpec {
protected:
	int N, M, K;
	vector < vector <int> > A;
	int H;
	
	void InputFormat() {
		LINE(N,M,K);
		GRID(A)%SIZE(N,M);
	}
	
	void OutputFormat() {
		LINE(H);
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
    }
	
	void Constraints() {
		CONS(2<=1LL*N*M&&1LL*N*M<=100000);
		CONS(0<=K&&K<(1<<10));
		CONS(eachRowBetween(A,0,(1<<10)-1));
		CONS(A[0][0]==0);
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
			"3 4 5",
			"0 7 4 3",
			"6 9 5 2",
			"1 4 8 3"
		});
		Output({
			"73"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		CASE(N=1,M=2,K=0,A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		CASE(N=100000,M=1,K=0,A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		CASE(N=316,M=316,K=0,A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		
		CASE(N=1,M=2,K=rnd.nextInt(1,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		CASE(N=2,M=1,K=rnd.nextInt(1,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		CASE(N=1,M=100000,K=rnd.nextInt(1,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		CASE(N=100000,M=1,K=rnd.nextInt(1,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		
		CASE(N=10,M=10000,K=rnd.nextInt(1,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		CASE(N=10000,M=10,K=rnd.nextInt(1,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		CASE(N=20,M=5000,K=rnd.nextInt(1,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		CASE(N=5000,M=20,K=rnd.nextInt(1,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		CASE(N=50,M=2000,K=rnd.nextInt(1,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		CASE(N=2000,M=50,K=rnd.nextInt(1,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		CASE(N=100,M=1000,K=rnd.nextInt(1,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		CASE(N=1000,M=100,K=rnd.nextInt(1,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		
		CASE(N=315,M=317,K=rnd.nextInt(1,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		CASE(N=317,M=315,K=rnd.nextInt(1,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		CASE(N=316,M=316,K=rnd.nextInt(1,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		
		for (int i=0;i<3;i++) {
			CASE(N=rnd.nextInt(1,15),M=100000/N,K=rnd.nextInt(0,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
			CASE(M=rnd.nextInt(1,15),N=100000/M,K=rnd.nextInt(0,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		}
		
		for (int i=0;i<3;i++) {
			CASE(N=rnd.nextInt(16,316),M=100000/N,K=rnd.nextInt(0,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
			CASE(M=rnd.nextInt(16,316),N=100000/M,K=rnd.nextInt(0,(1<<10)-1),A=randomGrid(N,M,0,(1<<10)-1),A[0][0]=0);
		}
	}
	
	vector <int> randomArray(int size,int mins,int maks) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			ret.push_back(rnd.nextInt(mins,maks));
		}
		
		return ret;
	}
	
	vector < vector <int> > randomGrid(int size_x,int size_y,int mins,int maks) {
		vector < vector <int> > ret;
		ret.clear();
		
		for (int i=0;i<size_x;i++) {
			ret.push_back(randomArray(size_y,mins,maks));
		}
		
		return ret;
	}
};
