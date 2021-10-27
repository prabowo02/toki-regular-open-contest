#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const long long mxn=1e15;

class ProblemSpec : public BaseProblemSpec
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

class TestSpec : public BaseTestSpec<ProblemSpec>
{
	protected:
		void SampleTestCase1()
		{
			Subtasks({1});
			Input
			({
				"24"
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
				"3"
			});
			Output
			({
				"NO"
			});
		}
		void SampleTestCase3()
		{
			Subtasks({1});
			Input
			({
				"131"
			});
			Output
			({
				"YES"
			});
		}
		void TestGroup1()
		{
			Subtasks({1});
			
			CASE(n=mxn); //NO
			
			CASE(n=baseTen("1103440004110344341044")); //YES
			CASE(n=baseTen("0100343444034343441011")); //YES
			CASE(n=baseTen("0040401010034440103343")); //NO
			CASE(n=baseTen("1111111111111111111111")); //YES
			CASE(n=baseTen("0341004034344434411011")); //YES
			
			CASE(n=1); //YES
			CASE(n=2); //NO
			
			CASE(n=baseTen("0443404340403433441012")); //NO
			CASE(n=baseTen("2010110443434000044411")); //NO
			CASE(n=baseTen("1010200411004041041100")); //NO
			CASE(n=baseTen("0333333333333333333333")); //NO
			CASE(n=baseTen("0401434043410341004110")); //NO
			
			CASE(n=4); //YES
			CASE(n=5); //YES
			
			CASE(n=baseTen("0333333333333333333334")); //YES
			CASE(n=baseTen("1041011000400040044404")); //YES
			CASE(n=baseTen("0441104110443303404334")); //NO
			CASE(n=baseTen("1010300344030104344404")); //NO
			CASE(n=baseTen("1040110044401004331004")); //NO
			
			CASE(n=6); //YES
			CASE(n=9); //NO
			CASE(n=10); //NO
			
			CASE(n=baseTen("1040104343440034044441")); //YES
			CASE(n=baseTen("0340133404333404034010")); //NO
			CASE(n=baseTen("0340000433401011110004")); //YES
			CASE(n=baseTen("0444444444444444444444")); //YES
			CASE(n=baseTen("1444004041110010101110")); //NO
		}
	
	private:
		long long baseTen(string x)
		{
			int i,sz=x.length();
			long long sm=0;
			
			for(i=0;i<sz;i++)
			{
				sm=sm*5+(x[i]-'0');
			}
			return sm;
		}
};
