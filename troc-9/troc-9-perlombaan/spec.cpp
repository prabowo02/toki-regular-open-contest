#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

bool isUppercase(string S) {
	for (char c : S) {
		if (c<'A'||c>'Z') {
			return 0;
		}
	}
	
	return 1;
}

class ProblemSpec : public BaseProblemSpec {
protected:
	string S;
	string ans;
	
	void InputFormat() {
		LINE(S);
	}
	
	void OutputFormat() {
		LINE(ans);
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
    }
	
	void Constraints() {
		CONS(S.length()<=100);
		CONS(isUppercase(S));
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
			"YOGA"
		});
		Output({
			"Ya"
		});
	}
	
	void SampleTestCase2() {
		Subtasks({1});
		Input({
			"SALMAN"
		});
		Output({
			"Tidak"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		CASE(S="PRABOWO");
		CASE(S="JOKOWI");
		CASE(S="HOCKY");
		CASE(S="MOSES");
		CASE(S="FIDE");
		CASE(S="VIO");
		CASE(S="GLENDA");
		CASE(S="YOLANDA");
		CASE(S="SANGGAU");
		CASE(S="CIREBON");
		CASE(S="BONBON");
		CASE(S="INDONESIA");
		CASE(S="MERDEKA");
		CASE(S="MAJULAH");
		CASE(S="SINGAPORE");
		
		CASE(S="A");
		CASE(S="Z");
		CASE(S="O");
		CASE(S="OO");
		CASE(S="OOO");
		CASE(S="OXO");
		
		CASE(S=allO(100));
		CASE(S=randomString(100));
		CASE(S=randomString(100),S[rnd.nextInt(0,99)]='O');
		CASE(S=randomString(100),S[rnd.nextInt(0,49)]='O',S[rnd.nextInt(50,99)]='O');
	}
	
	string allO(int x) {
		string ret;
		ret="";
		
		for (int i=0;i<x;i++) {
			ret+='O';
		}
		
		return ret;
	}
	
	string randomString(int x) {
		string ret;
		ret="";
		
		for (int i=0;i<x;i++) {
			char c;
			c=rnd.nextInt('A','Z');
			ret+=c;
		}
		
		return ret;
	}
};
