#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const long long mxn=100;

class ProblemSpec:public BaseProblemSpec
{
	protected:
		long long n,d;
		string s;
		
		void InputFormat()
		{
			LINE(n,d);
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
			CONS(1<=d&&d<=mxn);
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
				"9 3"
			});
			Output
			({
				"YES"
			});
		}
		void SampleTestCase2()
		{
			Subtasks({1});
			Input
			({
				"17 38"
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
				"1 1"
			});
			Output
			({
				"NO"
			});
		}
		void TestGroup1()
		{
			Subtasks({1});
			
			CASE(n=100,d=100);
			CASE(n=2,d=1);
			CASE(n=100,d=1);
			CASE(n=100,d=2);
			CASE(n=1,d=100);
			
			CASE(n=rnd.nextLongLong(3,98),d=rnd.nextLongLong(n+1,99));
			CASE(n=rnd.nextLongLong(4,99),d=rnd.nextLongLong(3,n-1));
			CASE(n=rnd.nextLongLong(3,99),d=n);
			
			CASE(n=rnd.nextLongLong(3,99),d=1);
			CASE(n=rnd.nextLongLong(3,99),d=2);
			CASE(n=1,d=rnd.nextLongLong(3,99));
		}
};
