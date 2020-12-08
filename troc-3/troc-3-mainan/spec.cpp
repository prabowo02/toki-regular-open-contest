#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
	int X;
	int A, B, C;
	int H;
	
	void InputFormat() {
		LINE(X);
		LINE(A,B,C);
	}
	
	void OutputFormat() {
		LINE(H);
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
    }
	
	void Constraints() {
		CONS(1<=X&&X<=10000);
		CONS(1<=A&&A<=100);
		CONS(1<=B&&B<=100);
		CONS(1<=C&&C<=100);
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
			"34",
			"3 2 4"
		});
		Output({
			"11"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		CASE(X=77,A=12,B=9,C=5);
		CASE(X=9998,A=74,B=14,C=52);
		
		CASE(X=1,A=1,B=1,C=1);
		CASE(X=10000,A=100,B=100,C=100);
		
		CASE(X=1,A=1,B=2,C=3);
		CASE(X=1,A=1,B=3,C=2);
		CASE(X=1,A=2,B=1,C=3);
		CASE(X=1,A=2,B=3,C=1);
		CASE(X=1,A=3,B=1,C=2);
		CASE(X=1,A=3,B=2,C=1);
		
		CASE(X=3,A=1,B=2,C=3);
		CASE(X=3,A=1,B=3,C=2);
		CASE(X=3,A=2,B=1,C=3);
		CASE(X=3,A=2,B=3,C=1);
		CASE(X=3,A=3,B=1,C=2);
		CASE(X=3,A=3,B=2,C=1);
		
		CASE(X=1,A=rnd.nextInt(1,10),B=rnd.nextInt(1,10),C=rnd.nextInt(1,10));
		CASE(X=1,A=rnd.nextInt(1,100),B=rnd.nextInt(1,100),C=rnd.nextInt(1,100));
		
		CASE(X=10000,A=rnd.nextInt(1,10),B=rnd.nextInt(1,10),C=rnd.nextInt(1,10));
		CASE(X=10000,A=rnd.nextInt(1,100),B=rnd.nextInt(1,100),C=rnd.nextInt(1,100));
		
		CASE(A=rnd.nextInt(1,10),B=rnd.nextInt(1,10),C=rnd.nextInt(1,10),X=(A+B+C)*rnd.nextInt(1,20));
		CASE(A=rnd.nextInt(1,100),B=rnd.nextInt(1,100),C=rnd.nextInt(1,100),X=(A+B+C)*rnd.nextInt(1,20));
		
		CASE(A=rnd.nextInt(1,10),B=rnd.nextInt(1,10),C=rnd.nextInt(1,10),X=(A+B+C)*rnd.nextInt(1,10)+rnd.nextInt(1,A+B+C-1));
		CASE(A=rnd.nextInt(1,100),B=rnd.nextInt(1,100),C=rnd.nextInt(1,100),X=(A+B+C)*rnd.nextInt(1,10)+rnd.nextInt(1,A+B+C-1));
		
		CASE(A=4,B=rnd.nextInt(10,100),C=rnd.nextInt(10,100),X=(A+B+C)*rnd.nextInt(1,15)+13);
		CASE(A=rnd.nextInt(10,100),B=3,C=rnd.nextInt(10,100),X=(A+B+C)*rnd.nextInt(1,15)+9);
		CASE(A=rnd.nextInt(10,100),B=rnd.nextInt(10,100),C=2,X=(A+B+C)*rnd.nextInt(1,15)+11);
		
		for (int i=0;i<5;i++) {
			CASE(X=rnd.nextInt(1,10000),A=rnd.nextInt(1,100),B=rnd.nextInt(1,100),C=rnd.nextInt(1,100));
		}
	}
};
