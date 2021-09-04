#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const long long mxn=1000;

class ProblemSpec:public BaseProblemSpec
{
	protected:
		long long n;
		string s;
		
		void InputFormat()
		{
			LINE(n);
		}
		void OutputFormat()
		{
			LINE(s);
		}
		void GradingConfig()
		{
			TimeLimit(1);
			MemoryLimit(64);
		}
		void Constraints()
		{
			CONS(1<=n&&n<=mxn);
		}
		void Subtask1()
		{
			Points(100);
		}
};

class TestSpec:public BaseTestSpec<ProblemSpec>
{
	protected:
		void SampleTestCase1()
		{
			Subtasks({1});
			Input
			({
				"265"
			});
			Output
			({
				"NO"
			});
		}
		void SampleTestCase2()
		{
			Subtasks({1});
			Input
			({
				"101"
			});
			Output
			({
				"YES"
			});
		}
		void SampleTestCase3()
		{
			Subtasks({1});
			Input
			({
				"20"
			});
			Output
			({
				"YES"
			});
		}
		void TestGroup1()
		{
			Subtasks({1});
			
			CASE(n=190);
			CASE(n=646);
			CASE(n=74);
			CASE(n=700);
			CASE(n=183);
			CASE(n=302);
			CASE(n=5);
			CASE(n=10);
			CASE(n=1000);
			CASE(n=1);
			CASE(n=999);
		}
};
