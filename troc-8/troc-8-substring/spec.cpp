#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const string BON="bon?";

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
	string S;
	int H;
	
	void InputFormat() {
		LINE(S);
	}
	
	void OutputFormat() {
		LINE(H);
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
    }
	
	void Constraints() {
		CONS(S.length()<=100000);
		CONS(!S.empty());
		CONS(allLowercase(S));
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
			"abonabon"
		});
		Output({
			"1"
		});
	}
	
	void SampleTestCase2() {
		Subtasks({1});
		Input({
			"bobobobo"
		});
		Output({
			"0"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		CASE(S="a");
		CASE(S="b");
		CASE(S="o");
		CASE(S="n");
		
		CASE(S=bonString({rnd.nextInt(1,100000),0,0}));
		CASE(S=bonString({0,rnd.nextInt(1,100000),0}));
		CASE(S=bonString({0,0,rnd.nextInt(1,100000)}));
		
		CASE(S=bonString({0,rnd.nextInt(1,50000),rnd.nextInt(1,50000)}));
		CASE(S=bonString({rnd.nextInt(1,50000),0,rnd.nextInt(1,50000)}));
		CASE(S=bonString({rnd.nextInt(1,50000),rnd.nextInt(1,50000),0}));
		
		CASE(S=bonString({rnd.nextInt(1,33334),rnd.nextInt(1,33333),rnd.nextInt(1,33333)}));
		CASE(S=bonString({rnd.nextInt(1,33333),rnd.nextInt(1,33334),rnd.nextInt(1,33333)}));
		CASE(S=bonString({rnd.nextInt(1,33333),rnd.nextInt(1,33333),rnd.nextInt(1,33334)}));
		CASE(S=bonString({rnd.nextInt(2,33333),rnd.nextInt(2,33333),rnd.nextInt(2,33333)}));
		
		for (int i=0;i<3;i++) {
			CASE(S=randomString(rnd.nextInt(1,100000)));
		}
	}
	
	string randomString(int N) {
		string ret;
		ret="";
		
		for (int i=0;i<N;i++) {
			char c;
			c=rnd.nextInt('a','z');
			
			ret+=c;
		}
		
		return ret;
	}
	
	string bonString(vector<int> N) {
		string ret;
		ret="";
		
		while (N[0]+N[1]+N[2]) {
			int x;
			x=rnd.nextInt(0,2);
			
			if (N[x]) {
				ret+=BON[x];
				N[x]--;
			}
		}
		
		return ret;
	}
};
