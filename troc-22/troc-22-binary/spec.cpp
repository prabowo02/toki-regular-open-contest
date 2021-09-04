#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
	int x, y, a, b;

	void InputFormat() {
		LINE(x, y, a, b);
	}

	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
	}

	void StyleConfig() {
		InteractiveEvaluator();
	}

	void Constraints() {
		CONS(1 <= x && x <= 1000000000);
		CONS(3 <= y && y <= 1000000000);
		CONS(0 <= a && a < x*2);
		CONS(0 <= b && b < x*2);
		// constraints for n = 2ll * x * y - a - b
		CONS(4 <= 2ll * x * y - a - b &&
			2ll * x * y - a - b <= 2000000000000000000ll);
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
			"2 3 2 1"
		});
	}

	void TestGroup1() {
		Subtasks({1});

		// small cases
		CASE(x = 1, y = 3, a = 0, b = 0);
		CASE(x = 1, y = 3, a = 0, b = 1);
		CASE(x = 1, y = 3, a = 1, b = 1);
		CASE(x = 2, y = 3, a = 0, b = 0);
		CASE(x = 2, y = 3, a = 1, b = 2);
		CASE(x = 2, y = 3, a = 2, b = 3);
		CASE(x = 2, y = 3, a = 3, b = 1);

		// large cases
		CASE(x = 999999999, y = 999999999, a = 999999999, b = 999999999);
		CASE(x = 1000000000, y = 1000000000, a = 1999999999, b = 1999999999);

		// random cases, y is minimum
		for (int i = 0; i < 10; ++i) {
			int _x = rnd.nextInt(1, 1000000000);
			int _y = 3;
			int _a = rnd.nextInt(_x * 2);
			int _b = rnd.nextInt(_x * 2);
			CASE(x = _x, y = _y, a = _a, b = _b);
		}

		// random cases, y also random
		for (int i = 0; i < 10; ++i) {
			int _x = rnd.nextInt(1, 1000000000);
			int _y = rnd.nextInt(3, 1000000000);
			int _a = rnd.nextInt(_x * 2);
			int _b = rnd.nextInt(_x * 2);
			CASE(x = _x, y = _y, a = _a, b = _b);
		}
	}
};
