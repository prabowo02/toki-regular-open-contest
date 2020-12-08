#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const string BON="bon?";

template<typename data>
bool eachElementBetween(const vector<data> &V,data mins,data maks) {
	for (data x : V) {
		if (x<mins||x>maks) {
			return 0;
		}
	}
	
	return 1;
}

bool allLowercase(string S) {
	for (char c : S) {
		if (c<'a'||c>'z') {
			return 0;
		}
	}
	
	return 1;
}

class ProblemSpec : public BaseProblemSpec {
protected:
	int N, Q;
	string S;
	vector <int> A, P, M;
	vector <int> H;
	
	void InputFormat() {
		LINE(N,Q);
		LINE(S);
		LINE(A%SIZE(N));
		LINES(P,M)%SIZE(Q);
	}
	
	void OutputFormat() {
		LINES(H)%SIZE(Q);
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
    }
	
	void Constraints() {
		CONS(1<=N&&N<=50000);
		CONS(1<=Q&&Q<=50000);
		CONS(S.length()==N);
		CONS(allLowercase(S));
		CONS(eachElementBetween(A,1,1000000000));
		CONS(eachElementBetween(P,1,66));
		CONS(eachElementBetween(M,1,1000000000));
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
			"8 3",
			"bbonbton",
			"1 2 3 4 5 6 7 8",
			"1 1",
			"2 1",
			"1 2"
		});
		Output({
			"95",
			"57",
			"449"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		CASE(N=48264,Q=49201,S=perfectString(N),A=randomBetween(N,1,1000000000),P=fillAll(Q,1),M=randomBetween(Q,1,1000000000));
		CASE(N=49180,Q=40238,S=perfectString(N),A=randomBetween(N,1,1000000000),P=fillAll(Q,66),M=randomBetween(Q,1,1000000000));
		CASE(N=41293,Q=49137,S=perfectString(N),A=fillAll(N,1),P=randomBetween(Q,1,66),M=randomBetween(Q,1,1000000000));
		
		CASE(N=50000,Q=50000,S=randomString(N),A=randomBetween(N,1,1000000000),P=randomBetween(Q,1,66),M=randomBetween(Q,1,1000000000));
		CASE(N=50000,Q=50000,S=perfectString(N),A=randomBetween(N,1,1000000000),P=randomBetween(Q,1,66),M=randomBetween(Q,1,1000000000));
		
		for (int i=0;i<3;i++) {
			CASE(N=rnd.nextInt(1,50000),Q=rnd.nextInt(1,50000),S=randomString(N),A=randomBetween(N,1,1000000000),P=randomBetween(Q,1,66),M=randomBetween(Q,1,1000000000));
			CASE(N=rnd.nextInt(1,50000),Q=rnd.nextInt(1,50000),S=perfectString(N),A=randomBetween(N,1,1000000000),P=randomBetween(Q,1,66),M=randomBetween(Q,1,1000000000));
		}
	}
	
	vector <int> fillAll(int size,int val) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			ret.push_back(val);
		}
		
		return ret;
	}
	
	vector <int> randomBetween(int size,int mins,int maks) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			ret.push_back(rnd.nextInt(mins,maks));
		}
		
		return ret;
	}
	
	string perfectString(int N) {
		string ret;
		ret="";
		
		for (int i=0;i<N;i++) {
			char c;
			c=BON[rnd.nextInt(0,2)];
			
			ret+=c;
		}
		
		return ret;
	}
	
	string randomString(int N) {
		string ret;
		ret="";
		
		for (int i=0;i<N;i++) {
			char c;
			c=BON[rnd.nextInt(0,3)];
			
			if (c=='?') {
				c=rnd.nextInt('a','z');
			}
			
			ret+=c;
		}
		
		return ret;
	}
};
