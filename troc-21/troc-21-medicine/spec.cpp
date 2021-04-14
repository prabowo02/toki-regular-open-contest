#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const long long mxn=1e5;

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
			CONS(2<=n&&n<=mxn);
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
				"5 3"
			});
			Output
			({
				"165"
			});
		}
		void SampleTestCase2()
		{
			Subtasks({1});
			Input
			({
				"2 4"
			});
			Output
			({
				"16"
			});
		}
		void TestGroup1()
		{
			Subtasks({1});
			
			CASE(n=rnd.nextLongLong(3,mxn-10),m=rnd.nextLongLong(3,mxn-10));
			CASE(n=rnd.nextLongLong(3,mxn-10),m=rnd.nextLongLong(3,mxn-10));
			CASE(n=rnd.nextLongLong(3,mxn-10),m=rnd.nextLongLong(3,mxn-10));
			
			CASE(n=99848,m=99932);
			
			CASE(n=mxn,m=mxn);
			CASE(n=mxn,m=rnd.nextLongLong(mxn-10,mxn-1));
			CASE(n=rnd.nextLongLong(mxn-10,mxn-1),m=mxn);
			CASE(n=rnd.nextLongLong(mxn-10,mxn-1),m=rnd.nextLongLong(mxn-10,mxn-1));
			
			CASE(n=2,m=rnd.nextLongLong(mxn-10,mxn-1));
			CASE(n=rnd.nextLongLong(mxn-10,mxn-1),m=1);
			CASE(n=2,m=1);
		}
};
