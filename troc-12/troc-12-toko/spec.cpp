#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const long long mxn=1e5;
long long n,d;
vector<long long> al[100069],w,sq;
vector<vector<long long>> p;
bool shf,rv,r0;
bitset<100069> vtd,vtd2;

class ProblemSpec:public BaseProblemSpec
{
	protected:
		void InputFormat()
		{
			LINE(n,d);
			LINES(w,p)%SIZE(n);
		}
		void OutputFormat()
		{
			LINE(sq%SIZE(n));
		}
		void GradingConfig()
		{
			TimeLimit(1);
			MemoryLimit(64);
		}
		void Constraints()
		{
			CONS(0<=d&&d<n&&n<=mxn);
			CONS(eeb(w,0,n-1));
			CONS(sm(w)<=mxn);
			CONS(eeb2(p,1,n));
			CONS(asc(p));
			CONS(dag());
			CONS(chk());
		}
		void Subtask1()
		{
			Points(100);
		}
	
	private:
		bool eeb(vector<long long> v,long long lh,long long rh)
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
		long long sm(vector<long long> v)
		{
			long long i,sz=v.size(),z=0;
			
			for(i=0;i<sz;i++)
			{
				z+=v[i];
			}
			return z;
		}
		bool eeb2(vector<vector<long long>> v,long long lh,long long rh)
		{
			long long i,sz=v.size();
			
			for(i=0;i<sz;i++)
			{
				if(!eeb(v[i],lh,rh))
				{
					return 0;
				}
			}
			return 1;
		}
		bool asc(vector<vector<long long>> v)
		{
			long long i,j,sz=v.size(),szz;
			
			for(i=0;i<sz;i++)
			{
				szz=v[i].size();
				for(j=1;j<szz;j++)
				{
					if(v[i][j]<=v[i][j-1])
					{
						return 0;
					}
				}
			}
			return 1;
		}
		void dfs(long long x)
		{
			long long i,sz=al[x].size(),l;
			
			vtd[x]=1;
			vtd2[x]=1;
			for(i=0;i<sz;i++)
			{
				l=al[x][i];
				if(!vtd[l])
				{
					dfs(l);
					if(r0)
					{
						return;
					}
				}
				else if(vtd2[l])
				{
					r0=1;
					return;
				}
			}
			vtd2[x]=0;
		}
		bool dag()
		{
			long long i;
			
			for(i=1;i<=n;i++)
			{
				al[i]=p[i-1];
				vtd[i]=0;
				vtd2[i]=0;
			}
			for(i=1;i<=n;i++)
			{
				if(!vtd[i])
				{
					r0=0;
					dfs(i);
					if(r0)
					{
						
						return 0;
					}
				}
			}
			return 1;
		}
		bool chk()
		{
			long long i,sz;
			
			for(i=0;i<n;i++)
			{
				sz=p[i].size();
				if(sz!=w[i])
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
				"4 1",
				"1 2",
				"0",
				"2 2 4",
				"1 2"
			});
			Output
			({
				"1 0 0 3"
			});
		}
		void SampleTestCase2()
		{
			Subtasks({1});
			Input
			({
				"10 3",
				"1 2",
				"0",
				"2 5 7",
				"3 1 2 9",
				"0",
				"1 9",
				"0",
				"0",
				"1 2",
				"1 4"
			});
			Output
			({
				"1 0 0 5 0 0 0 1 7 6"
			});
		}
		void BeforeTestCase()
		{
			long long i;
			
			for(i=1;i<=mxn;i++)
			{
				al[i].clear();
			}
			w.clear();
			p.clear();
			shf=1;
			rv=0;
		}
		void AfterTestCase()
		{
			long long i,j,sz,pm[100069];
			vector<long long> tmp[100069];
			
			for(i=1;i<=n;i++)
			{
				pm[i]=i;
			}
			if(rv)
			{
				for(i=1;i<=n;i++)
				{
					pm[i]=n+1-i;
				}
			}
			else if(shf)
			{
				rnd.shuffle(pm+1,pm+n+1);
			}
			for(i=1;i<=n;i++)
			{
				sz=al[i].size();
				for(j=0;j<sz;j++)
				{
					al[i][j]=pm[al[i][j]];
				}
				sort(al[i].begin(),al[i].end());
				tmp[pm[i]]=al[i];
			}
			for(i=1;i<=n;i++)
			{
				al[i]=tmp[i];
				sz=al[i].size();
				w.push_back(sz);
				p.push_back(al[i]);
			}
		}
		void TestGroup1()
		{
			Subtasks({1});
			
			CASE(n=rnd.nextLongLong(mxn/2,mxn),d=0,rnddag(rnd.nextLongLong(mxn/2,mxn)));
			CASE(n=mxn,d=0,rnddag(mxn));
			
			CASE(n=rnd.nextLongLong(mxn/2,mxn),d=rnd.nextLongLong(1,n-1),rnddag(rnd.nextLongLong(mxn/2,mxn)));
			CASE(n=mxn,d=rnd.nextLongLong(1,n-1),rnddag(mxn));
			CASE(n=mxn,d=1,rnddag(mxn));
			CASE(n=mxn,d=n-1,rnddag(mxn));
			
			CASE(n=rnd.nextLongLong(1000,5000),d=rnd.nextLongLong(1,n-1),rnddag(rnd.nextLongLong(mxn/2,mxn)));
			
			CASE(n=rnd.nextLongLong(mxn/2,mxn),d=rnd.nextLongLong(1,n-1));
			CASE(n=rnd.nextLongLong(mxn/2,mxn),d=0);
			CASE(n=rnd.nextLongLong(mxn/2,mxn),d=1);
			CASE(n=rnd.nextLongLong(mxn/2,mxn),d=n-1);
			CASE(n=mxn,d=rnd.nextLongLong(1,n-1));
			
			CASE(n=rnd.nextLongLong(mxn/2,mxn),d=rnd.nextLongLong(1,n-1),rnddag(1));
			CASE(n=rnd.nextLongLong(mxn/2,mxn),d=rnd.nextLongLong(1,n-1),rnddag(rnd.nextLongLong(1000,5000)));
			
			CASE(n=447,d=rnd.nextLongLong(1,n-1),rnddag(n*(n-1)/2));
			CASE(n=447,d=rnd.nextLongLong(1,n-1),rnddag(n*(n-1)/2),shf=0);
			CASE(n=447,d=rnd.nextLongLong(1,n-1),rnddag(n*(n-1)/2),rv=1);
			
			CASE(n=447,rnddag(n*(n-1)/2),n=mxn,d=rnd.nextLongLong(1,n-1));
			
			CASE(n=mxn,d=rnd.nextLongLong(1,n-1),lndag());
			CASE(n=mxn,d=0,lndag(),shf=0);
			CASE(n=mxn,d=rnd.nextLongLong(1,n-1),lndag(),shf=0);
			CASE(n=mxn,d=0,lndag(),rv=1);
			CASE(n=mxn,d=1,lndag(),rv=1);
			
			CASE(n=rnd.nextLongLong(1000,5000),lndag(),n=mxn,d=rnd.nextLongLong(1,n-1));
			
			CASE(n=mxn,d=rnd.nextLongLong(1,n-1),stdag(0));
			CASE(n=mxn,d=rnd.nextLongLong(1,n-1),stdag(1));
			CASE(n=mxn,d=rnd.nextLongLong(1,n-1),stdag(2));
			
			CASE(n=mxn,d=rnd.nextLongLong(1,n-1),ln2dag());
			
			CASE(n=mxn,d=rnd.nextLongLong(1,n-1),trdag(0));
			CASE(n=mxn,d=rnd.nextLongLong(1,n-1),trdag(1));
			
			CASE(n=1,d=0);
		}
	
	private:
		void rnddag(long long x)
		{
			long long ed[100069],i,j,rb=n*(n-1)/2;
			
			for(i=0;i<x;i++)
			{
				ed[i]=rnd.nextLongLong(0,rb-1);
			}
			sort(ed,ed+x);
			for(i=1;i<x*2;i++)
			{
				ed[i%x]=max(ed[i%x]+i/x*rb,ed[(i-1)%x]+(i-1)/x*rb+1)-i/x*rb;
			}
			for(i=0;i<x;i++)
			{
				ed[i]%=rb;
			}
			sort(ed,ed+x);
			for(j=1,i=0;i<x;i++)
			{
				for(;j*(j-1)/2<=ed[i];j++);
				al[j].push_back(j*(j-1)/2-ed[i]);
			}
		}
		void lndag()
		{
			long long i;
			
			for(i=2;i<=n;i++)
			{
				al[i].push_back(i-1);
			}
		}
		void stdag(long long x)
		{
			long long i,k,l;
			
			for(i=2;i<=n;i++)
			{
				k=i;
				l=1;
				if(x==1||(x==2&&i%2))
				{
					swap(k,l);
				}
				al[k].push_back(l);
			}
		}
		void ln2dag()
		{
			long long i;
			
			for(i=1;i<=n;i++)
			{
				al[min(i+1,n)].push_back(max(i-1,1ll));
			}
		}
		void trdag(long long x)
		{
			long long i,k,l;
			
			for(i=2;i<=n;i++)
			{
				k=i;
				l=rnd.nextLongLong(1,i-1);
				if(x)
				{
					swap(k,l);
				}
				al[k].push_back(l);
			}
		}
};
