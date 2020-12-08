#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

bool isUnique(string S) {
	int mask;
	mask=0;
	
	for (char c : S) {
		if ((mask>>(c-'a'))&1) {
			return 0;
		}
		
		mask^=1<<(c-'a');
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

bool allUppercase(string S) {
	for (char c : S) {
		if (c<'A'||c>'Z') {
			return 0;
		}
	}
	
	return 1;
}

class ProblemSpec : public BaseProblemSpec {
protected:
	string S, T;
	int H;
	
	void InputFormat() {
		LINE(S);
		LINE(T);
	}
	
	void OutputFormat() {
		LINE(H);
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
    }
	
	void Constraints() {
		CONS(!S.empty());
		CONS(allLowercase(S));
		CONS(isUnique(S));
		CONS(S.length()==T.length());
		CONS(allUppercase(T));
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
			"abcde",
			"AAAAA"
		});
		Output({
			"7776"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		CASE(S="a",T="A");
		CASE(S="h",T="E");
		
		CASE(S=lowercaseString(1),T=uppercaseString(1,1));
		CASE(S=lowercaseString(5),T=uppercaseString(5,5));
		CASE(S=lowercaseString(10),T=uppercaseString(10,10));
		CASE(S=lowercaseString(13),T=uppercaseString(13,13));
		CASE(S=lowercaseString(17),T=uppercaseString(17,17));
		CASE(S=lowercaseString(25),T=uppercaseString(25,25));
		
		CASE(S=lowercaseString(8),T=uppercaseString(8,3));
		CASE(S=lowercaseString(14),T=uppercaseString(14,5));
		CASE(S=lowercaseString(23),T=uppercaseString(23,14));
		
		CASE(S=lowercaseString(26),T=uppercaseString(26,1));
		CASE(S=lowercaseString(26),T=uppercaseString(26,2));
		CASE(S=lowercaseString(26),T=uppercaseString(26,3));
		
		for (int i=0;i<3;i++) {
			CASE(S=lowercaseString(26),T=uppercaseString(26,26));
		}
	}
	
	string lowercaseString(int N) {
		string ret;
		ret="";
		
		int mask;
		mask=0;
		
		for (int i=0;i<N;i++) {
			char c;
			c=rnd.nextInt('a','z');
			
			if ((mask>>(c-'a'))&1) {
				i--;
			}
			else {
				ret+=c;
				mask^=1<<(c-'a');
			}
		}
		
		return ret;
	}
	
	string uppercaseString(int N,int K) {
		string cand;
		cand="";
		
		int mask;
		mask=0;
		
		for (int i=0;i<K;i++) {
			char c;
			c=rnd.nextInt('A','Z');
			
			if ((mask>>(c-'A'))&1) {
				i--;
			}
			else {
				cand+=c;
				mask^=1<<(c-'A');
			}
		}
		
		string ret;
		ret="";
		
		for (int i=0;i<N;i++) {
			ret+=cand[rnd.nextInt(0,K-1)];
		}
		
		return ret;
	}
};
