#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
	int A, X;
	int N, M;

	void InputFormat() {
		LINE(A, X);
	}

	void OutputFormat() {
		LINE(N, M);
	}

	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
	}

	void Subtask1() {
		Points(100);
	}

	void Constraints() {
		CONS(1 <= A && A <= 100);
		CONS(1 <= X && X <= 100);
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Subtasks({1});
        Input({
            "2 5"
        });
        Output({
            "2 1"
        });
    }

    void SampleTestCase2() {
		Subtasks({1});
        Input({
            "4 20"
        });
        Output({
            "5 0"
        });
    }

    void SampleTestCase3() {
		Subtasks({1});
        Input({
            "9 6"
        });
        Output({
            "0 6"
        });
    }

	void TestGroup1() {
		Subtasks({1});
		CASE(A = 1, X = 1);
		CASE(A = 13, X = 31);
		CASE(A = 100, X = 100);
		CASE(A = 100, X = rnd.nextInt(1, 100));
		CASE(A = 100, X = rnd.nextInt(1, 100));
		CASE(A = rnd.nextInt(1, 100), X = 100);
		CASE(A = rnd.nextInt(1, 100), X = 100);
		CASE(A = rnd.nextInt(1, 100), X = rnd.nextInt(1, 100));
		CASE(A = rnd.nextInt(1, 100), X = rnd.nextInt(1, 100));
		CASE(A = rnd.nextInt(1, 100), X = rnd.nextInt(1, 100));
	}
};