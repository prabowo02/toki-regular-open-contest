#include <tcframe/spec.hpp>
#include <random>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
	int A, B, C, D, E, F;
	int ans;

	void InputFormat() {
		LINE(A, B, C, D, E, F);
	}

	void OutputFormat() {
		LINE(ans);
	}

	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
	}

	void Constraints() {
		CONS(1 <= A && A <= 10000);
		CONS(1 <= B && B <= 10000);
		CONS(1 <= C && C <= 10000);
		CONS(1 <= D && D <= 10000);
		CONS(1 <= E && E <= 10000);
		CONS(1 <= F && F <= 10000);
		CONS(A+B == D+E);
		CONS(B+C == E+F);
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
			"6 6 7 3 9 4"
		});
		Output({
			"81"
		});
	}

	void TestGroup1() {
		Subtasks({1});
		//small tc
		for(int i = 1;i <= 3;i ++){
			for(int j = i;j <= 3;j ++){
				for(int k = i;k <= 3;k ++){
					for(int l = i;l <= 3;l ++){
						if(i+j-l>=1&&k+l-i>=1)
							CASE(A = i, B = j, C = k, D = l, E = i+j-l, F = k+l-i);
					}
				}
			}
		}
		//large tc
		CASE(A = 5329, B = 4534, C = 4371, D = 5179, E = 4684, F = 4221);
		CASE(A = 9590, B = 1108, C = 1475, D = 10000, E = 698, F = 1885);
		CASE(A = 10000, B = 9435, C = 738, D = 9435, E = 10000, F = 173);
		CASE(A = 10000, B = 10000, C = 10000, D = 10000, E = 10000, F = 10000);
	}
};