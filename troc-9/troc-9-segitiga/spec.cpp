#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
	int A, B, C;
	string ans;
	
	void InputFormat() {
		LINE(A,B,C);
	}
	
	void OutputFormat() {
		LINE(ans);
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
    }
	
	void Constraints() {
		CONS(1<=A&&A<=1000000000);
		CONS(1<=B&&B<=1000000000);
		CONS(1<=C&&C<=1000000000);
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
			"3 4 5"
		});
		Output({
			"Tidak"
		});
	}
	
	void SampleTestCase2() {
		Subtasks({1});
		Input({
			"4 8 4"
		});
		Output({
			"Tidak"
		});
	}
	
	void SampleTestCase3() {
		Subtasks({1});
		Input({
			"5 4 4"
		});
		Output({
			"Ya"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		CASE(A=999999999,B=1000000000,C=999999999);
		CASE(A=1,B=1,C=1);
		CASE(A=1,B=1,C=2);
		CASE(A=1,B=2,C=1);
		CASE(A=2,B=1,C=1);
		
		CASE(A=rnd.nextInt(3,1000000000),B=A-1,C=A-1);
		CASE(B=rnd.nextInt(3,1000000000),A=B-1,C=B-1);
		CASE(C=rnd.nextInt(3,1000000000),A=C-1,B=C-1);
		
		CASE(A=30831,B=9036,C=170933);
		CASE(A=rnd.nextInt(1,1000000000),B=rnd.nextInt(1,1000000000),C=rnd.nextInt(1,1000000000));
	}
};
