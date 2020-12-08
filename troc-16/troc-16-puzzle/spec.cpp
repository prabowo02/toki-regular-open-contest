#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const long long mxn=100;

class ProblemSpec:public BaseProblemSpec
{
	protected:
		long long n,z,z2;
		
		void InputFormat()
		{
			LINE(n);
		}
		void OutputFormat()
		{
			LINE(z,z2);
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
		void StyleConfig()
		{
			CustomScorer();
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
				"77"
			});
			Output
			({
				"7 11"
			});
		}
		void SampleTestCase2()
		{
			Subtasks({1});
			Input
			({
				"12"
			});
			Output
			({
				"6 2"
			});
		}
		void SampleTestCase3()
		{
			Subtasks({1});
			Input
			({
				"1"
			});
			Output
			({
				"1 1"
			});
		}
		void TestGroup1()
		{
			Subtasks({1});
			
			CASE(n=69);
			CASE(n=99);
			CASE(n=100);
			CASE(n=60);
			CASE(n=90);
			CASE(n=64);
			CASE(n=49);
			CASE(n=2);
			CASE(n=3);
			CASE(n=89);
			CASE(n=97);
		}
};
