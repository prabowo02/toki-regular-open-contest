#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const long long mxn=1e5,ma=1e9;

class ProblemSpec:public BaseProblemSpec
{
	protected:
		long long n,d,z;
		vector<long long> a;
		
		void InputFormat()
		{
			LINE(n,d);
			LINE(a%SIZE(n));
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
			CONS(1<=d&&d<=ma);
			CONS(eachElementBetween(a,1,ma));
			CONS(ascendingArray(a));
		}
		void Subtask1()
		{
			Points(100);
		}
	
	private:
		bool eachElementBetween(vector<long long> v,long long lh,long long rh)
		{
			long long i,sz=v.size();
			
			for(i=0;i<sz;i++)
			{
				if(v[i]<lh||v[i]>rh)
				{
					return 0;
				}
			}
			return 1;
		}
		bool ascendingArray(vector<long long> v)
		{
			long long i,sz=v.size();
			
			for(i=1;i<sz;i++)
			{
				if(v[i]<=v[i-1])
				{
					return 0;
				}
			}
			return 1;
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
				"6 8",
				"3 5 7 10 13 18"
			});
			Output
			({
				"2"
			});
		}
		void SampleTestCase2()
		{
			Subtasks({1});
			Input
			({
				"4 1",
				"1 2 3 4"
			});
			Output
			({
				"3"
			});
		}
		void BeforeTestCase()
		{
			a.clear();
		}
		void AfterTestCase()
		{
			long long i;
			
			sort(a.begin(),a.end());
			for(i=1;i<n*2;i++)
			{
				a[i%n]=max(a[i%n]+i/n*ma,a[(i-1)%n]+(i-1)/n*ma+1)-i/n*ma;
			}
			for(i=0;i<n;i++)
			{
				a[i]=(a[i]-1)%ma+1;
			}
			sort(a.begin(),a.end());
		}
		void TestGroup1()
		{
			Subtasks({1});
			
			CASE(n=rnd.nextLongLong(mxn/2,mxn),d=rnd.nextLongLong(1,ma),randomArray(n,1,ma));
			CASE(n=mxn,d=rnd.nextLongLong(1,ma),randomArray(n,1,ma));
			
			CASE(n=mxn,d=rnd.nextLongLong(1,n*10),randomArray(n-10,ma/2-n*5,ma/2+n*5),randomArray(10,1,ma));
			
			CASE(n=mxn,d=rnd.nextLongLong(2,(ma-1)/(n-11)),sequentialArray(n-10,rnd.nextLongLong(1,ma-d*(n-11))),randomArray(10,1,ma));
			
			CASE(n=mxn,d=ma,randomArray(n-2,1,ma),randomArray(1,1,1),randomArray(1,ma,ma));
			CASE(n=mxn,d=ma-1,randomArray(n-2,1,ma),randomArray(1,1,1),randomArray(1,ma,ma));
			
			CASE(n=mxn,d=1,sequentialArray(n-10,rnd.nextLongLong(1,ma-n+11)),randomArray(10,1,ma));
			
			CASE(n=mxn,d=rnd.nextLongLong(2,(ma-1)/(n-1)),sequentialArray(n,rnd.nextLongLong(1,ma-d*(n-1))),d*=2);
			CASE(n=mxn,d=rnd.nextLongLong(2,(ma-1)/(n-11)),sequentialArray(n-10,rnd.nextLongLong(1,ma-d*(n-11))),randomArray(10,1,ma),d*=rnd.nextLongLong(3,10));
			
			CASE(n=1,d=rnd.nextLongLong(1,ma),randomArray(n,d,d));
			CASE(n=2,d=rnd.nextLongLong(1,ma/2),sequentialArray(n,d));
			
			CASE(n=mxn,d=rnd.nextLongLong(ma/2-100,ma/2+100),randomArray(1,d,d),randomArray(n-1,d-ma/10,d+ma/10));
			
			CASE(n=mxn,d=rnd.nextLongLong(1,ma/2),randomArray(n/2,1,ma-d),copyArray(n/2));
		}
	
	private:
		void randomArray(long long sz,long long lh,long long rh)
		{
			long long i;
			
			for(i=0;i<sz;i++)
			{
				a.push_back(rnd.nextLongLong(lh,rh));
			}
		}
		void sequentialArray(long long sz,long long x)
		{
			long long i;
			
			for(i=0;i<sz;i++)
			{
				a.push_back(x+i*d);
			}
		}
		void copyArray(long long sz)
		{
			long long i;
			
			for(i=0;i<sz;i++)
			{
				a.push_back(a[i]+d);
			}
		}
};
