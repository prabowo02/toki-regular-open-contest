#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const long long mxn=1e5;

class ProblemSpec:public BaseProblemSpec
{
	protected:
		long long n;
		vector<long long> a,p,sq;
		
		void InputFormat()
		{
			LINE(n);
			LINES(a,p)%SIZE(n);
		}
		void OutputFormat()
		{
			LINE(sq);
		}
		void GradingConfig()
		{
			TimeLimit(1);
			MemoryLimit(64);
		}
		void Constraints()
		{
			CONS(1<=n&&n<=mxn);
			CONS(eachElementBetween(a,1,n));
			CONS(eachElementBetween(p,0,1));
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
};

class TestSpec:public BaseTestSpec<ProblemSpec>
{
	protected:
		void SampleTestCase1()
		{
			Subtasks({1});
			Input
			({
				"6",
				"5 0",
				"5 1",
				"6 0",
				"3 0",
				"1 0",
				"1 1"
			});
			Output
			({
				"1 3 1 0 1 0"
			});
		}
		void SampleTestCase2()
		{
			Subtasks({1});
			Input
			({
				"4",
				"1 1",
				"1 1",
				"1 1",
				"1 1"
			});
			Output
			({
				"3 2 1 0"
			});
		}
		void BeforeTestCase()
		{
			a.clear();
			p.clear();
		}
		void TestGroup1()
		{
			long long i,ii;
			Subtasks({1});
			
			CASE(n=rnd.nextLongLong(mxn/2,mxn),randomArray(1,n));
			CASE(n=rnd.nextLongLong(mxn/2,mxn),randomArray(1,n));
			CASE(n=mxn,randomArray(1,n));
			CASE(n=mxn,randomArray(1,n));
			
			CASE(n=mxn,randomArray(n/2,n/2+300),randomAdd(10,1,n));
			
			for(ii=0;ii<2;ii++)
			{
				CASE(n=mxn,sameArray(rnd.nextLongLong(1,n),ii));
				CASE(n=mxn,sameArray(rnd.nextLongLong(1,n),ii),randomAdd(10,1,n));
			}
			
			CASE(n=mxn,endpointArray(0,rnd.nextLongLong(1,n)));
			CASE(n=mxn,endpointArray(1,rnd.nextLongLong(1,n)));
			
			for(i=1;i<=3;i++)
			{
				for(ii=0;ii<2;ii++)
				{
					CASE(n=mxn,antiharamArray(i,ii,rnd.nextLongLong(1,n)));
				}
			}
			
			CASE(n=1,randomArray(1,n));
			CASE(n=2,a={2,2},p={0,1});
			
			CASE(n=mxn,antiharamBothWaysArray(0,rnd.nextLongLong(1,n)));
			CASE(n=mxn,antiharamBothWaysArray(1,rnd.nextLongLong(1,n)));
		}
	
	private:
		void randomArray(long long lh,long long rh)
		{
			long long i;
			
			for(i=0;i<n;i++)
			{
				a.push_back(rnd.nextLongLong(lh,rh));
				p.push_back(rnd.nextLongLong(0,1));
			}
		}
		void randomAdd(long long sz,long long lh,long long rh)
		{
			long long i,k;
			
			for(i=0;i<sz;i++)
			{
				k=rnd.nextLongLong(1,n);
				a[k-1]=rnd.nextLongLong(lh,rh);
				p[k-1]=rnd.nextLongLong(0,1);
			}
		}
		void sameArray(long long x,long long xx)
		{
			long long i;
			
			for(i=0;i<n;i++)
			{
				a.push_back(x);
				p.push_back(xx);
			}
		}
		void endpointArray(long long ky,long long x)
		{
			long long i,ii,u,k,lr[2]={x,x},sz[2]={n,n};
			
			if(ky)
			{
				for(ii=0;ii<2;ii++)
				{
					sz[ii]=n/2;
				}
			}
			for(i=0;i<n;i++)
			{
				k=rnd.nextLongLong(0,1);
				k^=!sz[k];
				sz[k]--;
				u=!k*2-1;
				a.push_back(lr[!k]);
				p.push_back(k);
				if(i)
				{
					lr[k]=(lr[k]+n-u-1)%n+1;
				}
			}
			for(i=0;i<n-1-i;i++)
			{
				swap(a[i],a[n-1-i]);
				swap(p[i],p[n-1-i]);
			}
		}
		void antiharamArray(long long ky,long long xx,long long w)
		{
			long long i,u=!xx*2-1,k,l;
			
			for(i=1;i<=n;i++)
			{
				l=xx;
				if(ky==1)
				{
					k=(n-i)/2+1;
					if((n+1-i)%2)
					{
						l=rnd.nextLongLong(0,1);
					}
				}
				else if(ky==2)
				{
					k=min(i,n+1-i);
					if(i>n/2)
					{
						l=rnd.nextLongLong(0,1);
					}
				}
				else
				{
					k=(i-1)%(n/2)+1;
					if(i>n/2)
					{
						l=rnd.nextLongLong(0,1);
					}
				}
				k=(w+n+k*u-1)%n+1;
				a.push_back(k);
				p.push_back(l);
			}
		}
		void antiharamBothWaysArray(long long ky,long long w)
		{
			long long i,ii,u,k,l,sz[2],od[2]={0,0},e;
			
			sz[0]=rnd.nextLongLong(2,n-1)/2*2;
			if(ky)
			{
				sz[0]=n/2;
			}
			sz[1]=n-sz[0];
			for(i=1;i<=n;i++)
			{
				e=rnd.nextLongLong(0,1);
				e^=od[e]==sz[e];
				u=!e*2-1;
				k=(sz[e]-od[e])%(sz[e]/2)+1;
				l=e;
				if(od[e]>sz[e]/2)
				{
					l=rnd.nextLongLong(0,1);
				}
				od[e]++;
				a.push_back((w+n-k*u-1)%n+1);
				p.push_back(l);
			}
		}
};
