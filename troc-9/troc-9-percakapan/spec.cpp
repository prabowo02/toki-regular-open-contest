#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

bool validMoves(vector <string> &S) {
	for (string x : S) {
		if (x.length()!=3) {
			return 0;
		}
		
		for (char c : x) {
			if (c!='U'&&c!='D'&&c!='L'&&c!='R') {
				return 0;
			}
		}
	}
	
	return 1;
}

class ProblemSpec : public BaseProblemSpec {
protected:
	int N;
	bool B;
	vector <string> S;
	
	void InputFormat() {
		LINE(N,B);
		LINES(S)%SIZE(N);
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
		CONS(validMoves(S));
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
			"9 1",
			"URL",
			"DRL",
			"DUU",
			"RLR",
			"RUR",
			"DLU",
			"UDU",
			"UDU",
			"LRU"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		CASE(N=1,B=0,S={"UUR"});
		CASE(N=1,B=0,S={"LDL"});
		CASE(N=1,B=0,S={"LRR"});
		CASE(N=4,B=0,S={"RLU","UUD","UUD","LRU"});
		
		CASE(N=1000,B=0,S=merge(walk(N,0,-500,0,0),walk(N,0,500,0,0),walk(N,500,0,1000,0)));
		CASE(N=1000,B=0,S=merge(walk(N,0,-500,500,-500),walk(N,0,500,0,1000),walk(N,500,0,500,-500)));
		CASE(N=1000,B=0,S=merge(walk(N,0,-500,0,-1000),walk(N,0,500,500,500),walk(N,500,0,500,500)));
		
		CASE(N=1000,B=0,S=merge(walk(N,-500,0,-1000,0),walk(N,250,250,500,0),walk(N,250,-250,500,0)));
		CASE(N=1000,B=0,S=merge(walk(N,-500,0,-250,-250),walk(N,250,250,500,500),walk(N,250,-250,-250,-250)));
		CASE(N=1000,B=0,S=merge(walk(N,-500,0,-250,250),walk(N,250,250,-250,250),walk(N,250,-250,500,-500)));
		
		CASE(N=1000,B=0,S=merge(walk(N,192,-52,380,-74),walk(N,152,-73,380,-74),walk(N,181,-54,373,-102)));
		CASE(N=1000,B=0,S=merge(walk(N,rnd.nextInt(-250,250),rnd.nextInt(-250,250),0,0),walk(N,rnd.nextInt(-250,250),rnd.nextInt(-250,250),0,0),walk(N,rnd.nextInt(-250,250),rnd.nextInt(-250,250),0,0)));
		CASE(N=1000,B=0,S=merge(walk(N,rnd.nextInt(-250,250),rnd.nextInt(-250,250),rnd.nextInt(-250,250),rnd.nextInt(-250,250)),walk(N,rnd.nextInt(-250,250),rnd.nextInt(-250,250),rnd.nextInt(-250,250),rnd.nextInt(-250,250)),walk(N,rnd.nextInt(-250,250),rnd.nextInt(-250,250),rnd.nextInt(-250,250),rnd.nextInt(-250,250))));
		CASE(N=1000,B=0,S=merge(acak(N),acak(N),acak(N)));
		CASE(N=999,B=0,S=merge(acak(N),acak(N),acak(N)));
	}
	
	vector <string> merge(string A,string B,string C) {
		vector <string> S;
		S.clear();
		
		for (int i=0;i<A.length();i++) {
			string T;
			T=A[i];
			T+=B[i];
			T+=C[i];
			S.push_back(T);
		}
		
		return S;
	}
	
	string acak(int N) {
		string S, R;
		S="";
		R="RLUD";
		
		for (int i=0;i<N;i++) {
			S+=R[rnd.nextInt(0,3)];
		}
		
		return S;
	}
	
	string walk(int N,int X1,int Y1,int X2,int Y2) {
		string S, T, R;
		S="";
		T="";
		R="RLUD";
		
		for (int i=0;i<X1;i++) S+='R';
		for (int i=0;i>X1;i--) S+='L';
		for (int i=0;i<Y1;i++) S+='U';
		for (int i=0;i>Y1;i--) S+='D';
		
		X2-=X1;
		Y2-=Y1;
		
		for (int i=0;i<X2;i++) T+='R';
		for (int i=0;i>X2;i--) T+='L';
		for (int i=0;i<Y2;i++) T+='U';
		for (int i=0;i>Y2;i--) T+='D';
		
		N-=S.length()+T.length();
		
		while (N>0) {
			char c;
			c=R[rnd.nextInt(0,3)];
			N-=2;
			
			if (rnd.nextInt(0,1)) {
				S+=c;
				S+=c;
			}
			else {
				T+=c;
				T+=c;
			}
		}
		
		for (int i=1;i<S.length();i++) {
			swap(S[i],S[rnd.nextInt(0,i)]);
		}
		
		for (int i=1;i<T.length();i++) {
			swap(T[i],T[rnd.nextInt(0,i)]);
		}
		
		S+=T;
		return S;
	}
};
