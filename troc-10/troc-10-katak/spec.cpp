#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
	int N, K, L;
	string ans;

	void InputFormat() {
		LINE(N, K, L);
	}

	void OutputFormat() {
		LINE(ans);
	}

	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
	}

	void Constraints() {
		CONS(2 <= N && N <= 1000000);
		CONS(2 <= K && K <= 1000000);
		CONS(2 <= L && L <= 1000000);
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
			"5 5 5"
		});
		Output({
			"A"
		});
	}

	void SampleTestCase2() {
		Subtasks({1});
		Input({
			"6 4 5"
		});
		Output({
			"B"
		});
	}

	void TestGroup1() {
		Subtasks({1});
		for(int i = 0;i < 3;i ++){
			for(int j = 0;j < 3;j ++){
				for(int k = 0;k < 3;k ++){
					//small TC
					CASE(N = i+2, K = j+2, L = k+2);
					//large TC
					CASE(N = i+999997, K = j+999997, L = k+999997);
				}
			}
		}
		for(int i = 0;i < 10;i ++){
			//random TC
			CASE(
				N = rnd.nextInt(2, 1000000),
				K = rnd.nextInt(2, 1000000),
				L = rnd.nextInt(2, 1000000));
		}
	}
};
