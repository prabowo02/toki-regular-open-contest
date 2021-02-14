#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const long long mxn=100;

class ProblemSpec:public BaseProblemSpec
{
	protected:
		long long n,m,z;
		
		void InputFormat()
		{
			LINE(n,m);
		}
		void OutputFormat()
		{
			LINE(z);
		}
		void GradingConfig()
		{
			TimeLimit(1);
			MemoryLimit(64);
		}
		void Constraints()
		{
			CONS(1<=n&&n<=mxn);
			CONS(1<=m&&m<=mxn);
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
				"12 73"
			});
			Output
			({
				"-1"
			});
		}
		void TestGroup1()
		{
			Subtasks({1});
			
			CASE(n=21,m=20);
			CASE(n=69,m=63);
			CASE(n=3,m=43);
			CASE(n=58,m=8);
			CASE(n=18,m=34);
			CASE(n=56,m=78);
			CASE(n=19,m=45);
			CASE(n=83,m=2);
			CASE(n=22,m=11);
			CASE(n=100,m=100);
			CASE(n=100,m=99);
			CASE(n=99,m=100);
			CASE(n=1,m=2);
			CASE(n=2,m=1);
			CASE(n=1,m=1);
		}
};
