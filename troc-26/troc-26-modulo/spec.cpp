#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec
{
protected:
	int N;
	string res;

	void InputFormat()
	{
		LINE(N);
	}

	void OutputFormat()
	{
		LINE(res);
	}

	void GradingConfig()
	{
		TimeLimit(1);
		MemoryLimit(64);
	}

	void Constraints()
	{
		CONS(1 <= N && N <= 100);
	}

	void Subtask1()
	{
		Points(100);
	}

	void StyleConfig()
	{
		CustomScorer();
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec>
{
protected:
	void SampleTestCase1()
	{
		Subtasks({ 1 });
		Input({
			"69",
		});
		Output({
			"420",
		});
	}

	void TestGroup1()
	{
		Subtasks({ 1 });
		CASE(N = 1);
		CASE(N = 7);
		CASE(N = 13);
		CASE(N = 28);
		CASE(N = 40);
		CASE(N = 59);
		CASE(N = 84);
		CASE(N = 96);
		CASE(N = 100);
	}
};