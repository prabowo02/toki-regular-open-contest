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

bool eachElementBON(string S) {
	for (char c : S) {
		if (c!='b'&&c!='o'&&c!='n') {
			return 0;
		}
	}
	
	return 1;
}

class ProblemSpec : public BaseProblemSpec {
protected:
	int L, K;
	long long M;
	vector <long long> B;
	string T;
	vector <int> ans;
	
	void InputFormat() {
		LINE(L,M,K);
		LINE(T);
		LINES(B)%SIZE(K);
	}
	
	void OutputFormat() {
		LINES(ans) % SIZE(K);
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
    }
	
	void Constraints() {
		CONS(1<=L&&L<=2000);
		CONS(1<=M&&M<=1000000000);
		CONS(1<=K&&K<=300);
		CONS(T.length()==L);
		CONS(eachElementBON(T));
		CONS(eachElementBetween(B,1LL,3LL*L*M-1));
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
			"3 1 1",
			"bon",
			"8"
		});
		Output({
			"1"
		});
	}
	
	void SampleTestCase2() {
		Subtasks({1});
		Input({
			"1 2 3",
			"n",
			"3",
			"1",
			"5"
		});
		Output({
			"500000004",
			"0",
			"1"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		CASE(L=1998,M=947382940,K=294,T=fillPeriod("bon",666),B=randomBetween(K,1,3*L*M-1));
		CASE(L=2000,M=647839201,K=275,T=fillPeriod("b",2000),B=randomBetween(K,1,3*L*M-1));
		CASE(L=2000,M=738290174,K=269,T=fillPeriod("o",2000),B=randomBetween(K,1,3*L*M-1));
		CASE(L=2000,M=302748293,K=293,T=fillPeriod("n",2000),B=randomBetween(K,1,3*L*M-1));
		CASE(L=2000,M=1000000000,K=300,T=fillRandom(L),B=randomBetween(K,1,3*L*M-1));
		
		for (int i=0;i<3;i++) {
			CASE(L=rnd.nextInt(1,2000),M=rnd.nextInt(1,1000000000),K=rnd.nextInt(1,300),T=fillRandom(L),B=randomBetween(K,1,3*L*M-1));
		}
	}
	
	string fillPeriod(string x,int y) {
		string ret;
		ret="";
		
		for (int i=0;i<y;i++) {
			ret+=x;
		}
		
		return ret;
	}
	
	string fillRandom(int x) {
		string ret;
		ret="";
		
		for (int i=0;i<x;i++) {
			if (rnd.nextInt(1,3)==1) {
				ret+='b';
			}
			else if (rnd.nextInt(1,2)==1) {
				ret+='o';
			}
			else {
				ret+='n';
			}
		}
		
		return ret;
	}
	
	vector <long long> randomBetween(int size,long long mins,long long maks) {
		vector <long long> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			ret.push_back(rnd.nextLongLong(mins,maks));
		}
		
		return ret;
	}
};
