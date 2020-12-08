#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

#define ll long long
const ll MX = 1000000000000ll;

class ProblemSpec : public BaseProblemSpec{
protected:
	ll GCD, LCM;

	ll A, B;

	void InputFormat(){
		LINE(GCD, LCM);
	}
	void OutputFormat(){
		LINE(A, B);
	}

	void GradingConfig(){
		TimeLimit(1);
		MemoryLimit(64);
	}
	void StyleConfig(){
		CustomScorer();
	}

	void Constraints(){
		CONS(1 <= GCD && GCD <= MX);
		CONS(1 <= LCM && LCM <= MX);
	}

	void Subtask1(){
		Points(100);
	}

private:

};

class TestSpec : public BaseTestSpec<ProblemSpec>{
protected:
	void SampleTestCase1(){
		Subtasks({1});
		Input({
			"2 30",
		});
		Output({
			"6 10",
		});
	}
	void SampleTestCase2(){
		Subtasks({1});
		Input({
			"6 9",
		});
		Output({
			"-1 -1",
		});
	}

	void BeforeTestCase(){
	}

	void TestGroup1(){
		Subtasks({1});

		// base case
		CASE({GCD = 69, LCM = 420;});
		CASE({GCD = MX, LCM = MX;});
		CASE({GCD = 1, LCM = MX;});
		CASE({GCD = MX, LCM = 1;});
		CASE({GCD = 1, LCM = 1;});

		//small prime * large prime
		CASE({GCD = rnd.nextLongLong(1, 499), LCM = GCD * 2ll * 1000000069ll;});
		CASE({GCD = 1, LCM = 499999999979ll;});
		//prime
		CASE({GCD = rnd.nextLongLong(1, 999), LCM = GCD * 1000000069ll;});
		CASE({GCD = 1, LCM = 999999999989ll;});
		//prime square
		CASE({GCD = rnd.nextLongLong(1, 15994), LCM = GCD * 7907ll * 7907ll;});
		CASE({GCD = 1, LCM = 999983ll * 999983ll;});

		// highly composite number
		CASE({GCD = 1, LCM = 963761198400ll;});
		CASE({GCD = 1, LCM = 642507465600ll;});
		CASE({GCD = rnd.nextLongLong(1, 92500), LCM = GCD * 10810800ll;});
		CASE({GCD = rnd.nextLongLong(1, 143), LCM = GCD * 6983776800ll;});

		// rand flip
		CASE({GCD = rnd.nextLongLong(1, MX - 1), LCM = rnd.nextLongLong(GCD + 1, MX);});
		CASE({GCD = rnd.nextLongLong(2, MX), LCM = rnd.nextLongLong(1, GCD - 1);});

		// same
		CASE({GCD = rnd.nextLongLong(1, MX), LCM = GCD;});
	}

private:

};
