#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

const int MX = 1000;

class ProblemSpec : public BaseProblemSpec{
protected:
	int n, ans;

	void InputFormat(){
		LINE(n);
	}
	void OutputFormat(){
		LINE(ans);
	}

	void GradingConfig(){
		TimeLimit(1);
		MemoryLimit(64);
	}

	void Constraints(){
		CONS(1 <= n && n <= MX);
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
			"1",
		});
		Output({
			"0",
		});
	}

	void SampleTestCase2(){
		Subtasks({1});
		Input({
			"3",
		});
		Output({
			"8",
		});
	}

	void BeforeTestCase(){
	}

	void TestGroup1(){
		Subtasks({1});
		CASE(n = 2);
		CASE(n = 7);
		CASE(n = 24);
		CASE(n = 69);
		CASE(n = 297);
		CASE(n = 420);
		CASE(n = 501);
		CASE(n = 778);
		CASE(n = 999);
		CASE(n = 1000);
	}

private:

};