#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const long long mxn=2e5,ma=1e8,sqn=447;

class ProblemSpec:public BaseProblemSpec
{
	protected:
		long long n,q;
		vector<long long> a,l,r,w,sq;
		
		void InputFormat()
		{
			LINE(n,q);
			LINE(a%SIZE(n));
			LINES(l,r,w)%SIZE(q);
		}
		void OutputFormat()
		{
			LINES(sq)%SIZE(q);
		}
		void GradingConfig()
		{
			TimeLimit(1);
			MemoryLimit(64);
		}
		void Constraints()
		{
			CONS(1<=n&&n<=mxn);
			CONS(1<=q&&q<=mxn);
			CONS(eachElementBetween(a,-ma,ma));
			CONS(eachElementBetween(l,1,n));
			CONS(eachElementBetween(r,1,n));
			CONS(eachElementCompare(l,r));
			CONS(eachElementBetween(w,-ma,ma));
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
		bool eachElementCompare(vector<long long> x,vector<long long> y)
		{
			long long i,sz=x.size();
			
			for(i=0;i<sz;i++)
			{
				if(x[i]>y[i])
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
				"7 4",
				"-1 4 3 -5 -1 0 4",
				"1 7 0",
				"2 5 -2",
				"4 6 3",
				"2 2 -9"
			});
			Output
			({
				"7",
				"10",
				"14",
				"9"
			});
		}
		void SampleTestCase2()
		{
			Subtasks({1});
			Input
			({
				"3 2",
				"-2 -2 -2",
				"1 3 2",
				"2 2 7"
			});
			Output
			({
				"0",
				"5"
			});
		}
		void BeforeTestCase()
		{
			a.clear();
			l.clear();
			r.clear();
			w.clear();
		}
		void TestGroup1()
		{
			long long ii;
			Subtasks({1});
			
			CASE(n=rnd.nextLongLong(mxn/2,mxn),q=rnd.nextLongLong(mxn/2,mxn),a=randomArray(n,-ma,ma),randomLR(1,n),w=randomArray(q,-ma,ma));
			CASE(n=rnd.nextLongLong(mxn/2,mxn),q=rnd.nextLongLong(mxn/2,mxn),a=randomArray(n,-ma,ma),randomLR(1,n),w=randomArray(q,-ma,ma));
			CASE(n=mxn,q=mxn,a=randomArray(n,-ma,ma),randomLR(1,n),w=randomArray(q,-ma,ma));
			CASE(n=mxn,q=mxn,a=randomArray(n,-ma,ma),randomLR(1,n),w=randomArray(q,-ma,ma));
			
			CASE(n=mxn,q=mxn,randomPrefixSum(-ma/2,ma/2),randomLR(1,n),w=randomArray(q,-ma,ma));
			CASE(n=mxn,q=mxn,a=randomArray(n,-1e6,1e6),randomLR(1,n),w=randomArray(q,-1e6,1e6));
			CASE(n=mxn,q=mxn,randomPrefixSum(-1e6,1e6),randomLR(1,n),w=randomArray(q,-1e6,1e6));
			
			CASE(n=mxn,q=mxn,a=randomArray(n,-ma/2,ma),randomLR(1,n),w=randomArray(q,-ma,ma/2));
			
			CASE(n=mxn,q=mxn,a=randomArray(n,ma,ma),randomLR(1,n),w=randomArray(q,-ma,ma),addMaxQuery());
			CASE(n=mxn,q=mxn,a=randomArray(n,-ma,-ma),randomLR(1,n),w=randomArray(q,-ma,ma),addMaxQuery());
			
			CASE(n=mxn,q=mxn,wrongCHT(1,0));
			CASE(n=mxn,q=mxn,wrongCHT(1,1));
			CASE(n=mxn,q=mxn,wrongCHT(2,0));
			CASE(n=mxn,q=mxn,wrongCHT(2,1));
			
			CASE(n=mxn,q=mxn,a=randomArray(n,-ma,ma),moLR(0),w=randomArray(q,-ma,ma));
			CASE(n=mxn,q=mxn,a=randomArray(n,-ma,ma),moLR(1),w=randomArray(q,-ma,ma));
			
			for(ii=0;ii<2;ii++)
			{
				CASE(n=mxn,q=mxn,sortedArray(ii),randomLR(1,n),w=randomArray(q,-ma,ma));
				
				CASE(n=mxn,q=mxn,sortedArray(ii),moLR(0),w=randomArray(q,-ma,ma));
				CASE(n=mxn,q=mxn,sortedArray(ii),moLR(1),w=randomArray(q,-ma,ma));
				
				CASE(n=mxn,q=mxn,sortedArray(ii),l=randomArray(q,1,1),r=randomArray(q,n,n),randomAddLR(10,1,n),w=randomArray(q,-ma,ma));
				
				CASE(n=mxn,q=mxn,sortedArray(ii),l=randomArray(q,2,2),r=randomArray(q,n-1,n-1),w=randomArray(q,-ma,ma));
				CASE(n=mxn,q=mxn,sortedArray(ii),l=randomArray(q,2,3),r=randomArray(q,n-2,n-1),randomAddLR(10,1,n),w=randomArray(q,-ma,ma));
				CASE(n=mxn,q=mxn,sortedArray(ii),l=randomArray(q,2,sqn+1),r=randomArray(q,n-sqn,n-1),w=randomArray(q,-ma,ma));
			}
			
			CASE(n=1,q=mxn,a=randomArray(n,-ma,ma),randomLR(1,n),w=randomArray(q,-ma,ma));
			CASE(n=2,q=mxn,a=randomArray(n,-ma,ma),randomLR(1,n),w=randomArray(q,-ma,ma));
			
			CASE(n=mxn,q=mxn,randomPrefixSum(-ma/2,ma/2),l=randomArray(q,1,n),r=l,randomAddLR(10,1,n),w=randomArray(q,-ma,ma));
		}
	
	private:
		vector<long long> randomArray(long long sz,long long lh,long long rh)
		{
			long long i;
			vector<long long> v;
			
			for(i=0;i<sz;i++)
			{
				v.push_back(rnd.nextLongLong(lh,rh));
			}
			return v;
		}
		void randomLR(long long lh,long long rh)
		{
			long long i;
			
			for(i=0;i<q;i++)
			{
				l.push_back(rnd.nextLongLong(lh,rh));
				r.push_back(rnd.nextLongLong(lh,rh));
				if(l[i]>r[i])
				{
					swap(l[i],r[i]);
				}
			}
		}
		void randomPrefixSum(long long lh,long long rh)
		{
			long long i,k,l=0;
			
			for(i=0;i<n;i++)
			{
				k=rnd.nextLongLong(lh,rh);
				a.push_back(k-l);
				l=k;
			}
		}
		void addMaxQuery()
		{
			long long ii,u;
			
			for(ii=0;ii<2;ii++)
			{
				u=!ii*2-1;
				l[q-1-ii]=1;
				r[q-1-ii]=n;
				w[q-1-ii]=ma*u;
			}
		}
		void randomAddW(long long sz,long long lh,long long rh)
		{
			long long i;
			
			for(i=0;i<sz;i++)
			{
				w[rnd.nextLongLong(0,q)]=rnd.nextLongLong(lh,rh);
			}
		}
		void randomAddLR(long long sz,long long lh,long long rh)
		{
			long long i,k;
			
			for(i=0;i<sz;i++)
			{
				k=rnd.nextLongLong(1,q);
				l[k-1]=rnd.nextLongLong(lh,rh);
				r[k-1]=rnd.nextLongLong(lh,rh);
				if(l[k-1]>r[k-1])
				{
					swap(l[k-1],r[k-1]);
				}
			}
		}
		void sortedArray(bool ky)
		{
			long long i;
			
			for(i=0;i<n;i++)
			{
				a.push_back(rnd.nextLongLong(-ma,ma-(n-1)));
			}
			sort(a.begin(),a.end());
			for(i=0;i<n;i++)
			{
				a[i]+=i;
			}
			if(ky)
			{
				for(i=0;i<n;i++)
				{
					a[i]*=-1;
				}
			}
		}
		void moLR(bool ky)
		{
			long long i,k;
			
			for(i=1;i<=q;i++)
			{
				l.push_back(i);
				if(i%2)
				{
					r.push_back(i);
				}
				else
				{
					r.push_back(n);
				}
			}
			if(ky)
			{
				for(i=0;i<q;i++)
				{
					l[i]=n+1-l[i];
					r[i]=n+1-r[i];
					swap(l[i],r[i]);
				}
			}
			for(i=0;i<q;i++)
			{
				k=rnd.nextLongLong(0,i);
				swap(l[i],l[k]);
				swap(r[i],r[k]);
			}
		}
		void wrongCHT(long long ky,bool g)
		{
			long long i,k,p;
			
			randomLR(1,n);
			w=randomArray(q,-ma,ma);
			if(ky==1)
			{
				for(i=1;i<=n;i++)
				{
					k=0;
					if(i==1)
					{
						k=5e7;
					}
					if(i==1e5+51)
					{
						k=-8e7;
					}
					if(i>1e5+51&&i<=1e5+60)
					{
						k=-(22-(i-(1e5+50)));
					}
					if(i==1e5+61)
					{
						k=8e7+144;
					}
					if(i==1e5+150)
					{
						k=-8e7-1050;
					}
					if(i==1e5+151)
					{
						k=8e7+1050;
					}
					a.push_back(k);
				}
				for(i=1;i<=20;i++)
				{
					l[q-i]=2;
					r[q-i]=n-1;
					w[q-i]=i;
				}
			}
			else
			{
				for(i=1;i<=n;i++)
				{
					k=0;
					if(i==1)
					{
						k=5e7;
					}
					if(i==1e5+51)
					{
						k=-8e7;
					}
					if(i>1e5+51&&i<=1e5+60)
					{
						k=-(12-(i-(1e5+50)));
					}
					if(i==1e5+61)
					{
						k=8e7+54;
					}
					if(i==1e5+1050)
					{
						k=-8e7-11111;
					}
					if(i==1e5+1051)
					{
						k=8e7+11111;
					}
					a.push_back(k);
				}
				for(i=1;i<=20;i++)
				{
					l[q-i]=2;
					r[q-i]=n-1;
					w[q-i]=i;
				}
			}
			for(i=0;i<n;i++)
			{
				if(a[i])
				{
					p=i;
				}
				if(i-p>1)
				{
					k=rnd.nextLongLong(-mxn,mxn);
					a[i-1]+=k;
					a[i]-=k;
				}
			}
			if(g)
			{
				for(i=0;i<n-1-i;i++)
				{
					swap(a[i],a[n-1-i]);
				}
				for(i=0;i<q;i++)
				{
					l[i]=n+1-l[i];
					r[i]=n+1-r[i];
					swap(l[i],r[i]);
				}
			}
		}
};
