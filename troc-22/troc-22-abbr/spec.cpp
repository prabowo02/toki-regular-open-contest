#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const long long mxn=1e5,mxk=9,mxf=1e4;

class ProblemSpec:public BaseProblemSpec
{
	protected:
		long long n,k,z;
		string s;
		vector<vector<long long>> f;
		
		void InputFormat()
		{
			LINE(n,k);
			LINE(s);
			GRID(f)%SIZE(k,k);
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
			CONS(1<=k&&k<=mxk);
			CONS(s.length()==n);
			CONS(eachElementBetweenString(s,'1','0'+k));
			CONS(eachElementBetweenGrid(f,-mxf,mxf));
		}
		void Subtask1()
		{
			Points(100);
		}
	
	private:
		bool eachElementBetweenString(string s,long long lh,long long rh)
		{
			long long i,ln=s.length();
			
			for(i=0;i<ln;i++)
			{
				if(s[i]<lh||s[i]>rh)
				{
					return 0;
				}
			}
			return 1;
		}
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
		bool eachElementBetweenGrid(vector<vector<long long>> vv,long long lh,long long rh)
		{
			long long i,sz=vv.size();
			
			for(i=0;i<sz;i++)
			{
				if(!eachElementBetween(vv[i],lh,rh))
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
				"6 3",
				"122313",
				"-3 2 1",
				"2 3 0",
				"6 2 -5"
			});
			Output
			({
				"16"
			});
		}
		void SampleTestCase2()
		{
			Subtasks({1});
			Input
			({
				"12 9",
				"657565451929",
				"10 -2 3 9 7 6 2 -10 9",
				"10 4 -5 3 -4 -3 -2 3 4",
				"8 8 -1 -1 7 -4 9 3 2",
				"-5 10 -2 -2 2 -2 -1 -10 -6",
				"-5 -3 -6 -7 7 10 9 -1 2",
				"-8 -10 -6 -2 -9 1 -2 -3 8",
				"-7 -3 -2 8 9 4 0 1 4",
				"5 5 3 0 7 -3 0 10 2",
				"4 -1 0 10 2 -10 2 10 -9"
			});
			Output
			({
				"43"
			});
		}
		void TestGroup1()
		{
			Subtasks({1});
			
			CASE(n=rnd.nextLongLong(mxn/2,mxn),k=rnd.nextLongLong(mxk/2,mxk),s=randomString(1,k),f=randomGrid(-mxf,mxf));
			CASE(n=rnd.nextLongLong(mxn/2,mxn),k=mxk,s=randomString(1,k),f=randomGrid(-mxf,mxf));
			CASE(n=mxn,k=rnd.nextLongLong(mxk/2,mxk),s=randomString(1,k),f=randomGrid(-mxf,mxf));
			CASE(n=mxn,k=mxk,s=randomString(1,k),f=randomGrid(-mxf,mxf));
			
			CASE(n=mxn,k=3,s=randomString(1,k),f=randomGrid(-mxf,mxf));
			CASE(n=mxn,k=2,s=randomString(1,k),f=randomGrid(-mxf,mxf));
			CASE(n=mxn,k=1,s=randomString(1,k),f=randomGrid(-mxf,mxf));
			
			CASE(n=3,k=mxk,s=randomString(1,k),f=randomGrid(-mxf/3,mxf));
			
			CASE(n=mxn,k=mxk,s=randomString(k,k),f=randomGrid(1,mxf));
			
			CASE(n=mxn,k=mxk,s=randomString(1,k),f=randomGrid(mxf,mxf));
			CASE(n=mxn,k=mxk,s=randomString(1,k),f=randomGrid(mxf/2,mxf));
			
			CASE(n=mxn,k=mxk,s=sequentialString(k),f=specificGrid());
			
			CASE(n=2,k=1,s="11",f={{mxf}});
			
			CASE(n=mxn,k=mxk,s=randomString(1,k),f=randomGrid(-mxf,mxf));
			CASE(n=mxn,k=mxk,s=randomString(1,k),f=randomGrid(-mxf,mxf));
			CASE(n=mxn,k=mxk,s=randomString(1,k),f=randomGrid(-mxf,mxf));
			CASE(n=mxn,k=mxk,s=randomString(1,k),f=randomGrid(-mxf,mxf));
		}
	
	private:
		string randomString(long long lh,long long rh)
		{
			long long i;
			string cs;
			
			for(i=0;i<n;i++)
			{
				cs+=(char)(rnd.nextLongLong(lh,rh)+'0');
			}
			return cs;
		}
		string sequentialString(long long x)
		{
			long long i;
			string cs;
			
			for(i=0;i<n;i++)
			{
				cs+=(char)(i%x+'1');
			}
			return cs;
		}
		vector<long long> randomArray(long long lh,long long rh)
		{
			long long i;
			vector<long long> v;
			
			for(i=0;i<k;i++)
			{
				v.push_back(rnd.nextLongLong(lh,rh));
			}
			return v;
		}
		vector<vector<long long>> randomGrid(long long lh,long long rh)
		{
			long long i;
			vector<vector<long long>> vv;
			
			for(i=0;i<k;i++)
			{
				vv.push_back(randomArray(lh,rh));
			}
			return vv;
		}
		vector<vector<long long>> specificGrid()
		{
			long long i,j,w;
			vector<long long> v;
			vector<vector<long long>> vv;
			
			for(i=0;i<k;i++)
			{
				v.clear();
				for(j=0;j<k;j++)
				{
					w=rnd.nextLongLong(1,mxf);
					if((i+1)%k==j)
					{
						w*=-1;
					}
					v.push_back(w);
				}
				vv.push_back(v);
			}
			return vv;
		}
};
