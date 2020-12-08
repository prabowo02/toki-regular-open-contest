#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
	int N;
	string ans;

	void InputFormat() {
		LINE(N);
	}

	void OutputFormat() {
		LINE(ans);
	}

	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
	}

	void Constraints() {
		CONS(0 <= N && N <= 100000);
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
			"1"
		});
		Output({
			"0"
		});
	}

	void SampleTestCase2() {
		Subtasks({1});
		Input({
			"3"
		});
		Output({
			"48"
		});
	}

	void TestGroup1() {
		Subtasks({1});
		CASE(N = 0);
		CASE(N = 2);
		CASE(N = 4);
		CASE(N = 5);
		CASE(N = rnd.nextInt(50000, 90000)|1);
		CASE(N = (rnd.nextInt(50000, 90000)|1)^1);
		CASE(N = 99999);
		CASE(N = 100000);
	}
};