#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
#include <tcrand/graph.hpp>

using namespace std;
using namespace tcframe;
using namespace tcrand;

#define mp make_pair
#define fr first
#define sc second

const int mxn=1e5,mxm=2e5,mxk=1e5,mxw=1e4,mxa=1e9,ub=2e5;

class ProblemSpec : public BaseProblemSpec
{
	protected:
		int n,m,k,z;
		vector<int> u,v,w,p,a;
		
		void InputFormat()
		{
			LINE(n,m);
			LINES(u,v,w)%SIZE(m);
			LINE(k);
			LINES(p,a)%SIZE(k);
		}
		void OutputFormat()
		{
			LINE(z);
		}
		void GradingConfig()
		{
			TimeLimit(5);
			MemoryLimit(512);
		}
		void Constraints()
		{
			CONS(1<=n&&n<=mxn);
			CONS(n-1<=m&&m<=min((long long)n*(n-1)/2,(long long)mxm));
			CONS(1<=k&&k<=mxk);
			CONS(eachElementBetween(u,1,n));
			CONS(eachElementBetween(v,1,n));
			CONS(noSelfLoopPlus());
			CONS(noMultiEdge());
			CONS(eachElementBetween(w,1,mxw));
			CONS(isConnected());
			CONS(eachElementBetween(p,1,n));
			CONS(eachElementBetween(a,1,mxa));
		}
		void Subtask1()
		{
			Points(100);
		}
	
	private:
		int dsu[mxn+69];
		
		bool eachElementBetween(vector<int> cv,int lh,int rh)
		{
			int i,sz=cv.size();
			
			for(i=0;i<sz;i++)
			{
				if(cv[i]<lh||cv[i]>rh)
				{
					return 0;
				}
			}
			return 1;
		}
		bool noSelfLoopPlus()
		{
			int i;
			
			for(i=0;i<m;i++)
			{
				if(u[i]>=v[i])
				{
					return 0;
				}
			}
			return 1;
		}
		bool noMultiEdge()
		{
			int i;
			pair<int,int> as[mxm+69];
			
			for(i=1;i<=m;i++)
			{
				as[i]={u[i-1],v[i-1]};
			}
			sort(as+1,as+m+1);
			for(i=1;i<m;i++)
			{
				if(as[i]==as[i+1])
				{
					return 0;
				}
			}
			return 1;
		}
		int unionFind(int x)
		{
			if(dsu[x]!=x)
			{
				dsu[x]=unionFind(dsu[x]);
			}
			return dsu[x];
		}
		bool isConnected()
		{
			int i,c=0;
			
			for(i=1;i<=n;i++)
			{
				dsu[i]=i;
			}
			for(i=0;i<m;i++)
			{
				c+=unionFind(u[i])!=unionFind(v[i]);
				dsu[unionFind(v[i])]=unionFind(u[i]);
			}
			return c==n-1;
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
				"4 5",
				"1 2 2",
				"2 4 4",
				"3 4 2",
				"2 3 3",
				"1 3 6",
				"4",
				"4 3",
				"3 2",
				"4 6",
				"2 1"
			});
			Output
			({
				"2"
			});
		}
		void BeforeTestCase()
		{
			u.clear();
			v.clear();
			w.clear();
			p.clear();
			a.clear();
		}
		void AfterTestCase()
		{
			int i,x;
			
			for(i=0;i<m;i++)
			{
				if(u[i]>v[i])
				{
					swap(u[i],v[i]);
				}
				x=rnd.nextInt(0,i);
				swap(u[i],u[x]);
				swap(v[i],v[x]);
				swap(w[i],w[x]);
			}
		}
		void TestGroup1()
		{
			Subtasks({1});
			
			//random
			CASE(n=rnd.nextInt(mxn/2,mxn),m=rnd.nextInt(n-1,mxm),k=rnd.nextInt(mxk/2,mxk),randomGraph(),p=randomArray(k,1,n),a=randomArray(k,1,mxa));
			CASE(n=mxn,m=mxm,k=mxk,randomGraph(),p=randomArray(k,1,n),a=randomArray(k,1,mxa));
			
			//random with A upperbound
			CASE(n=mxn,m=mxm,k=mxk,randomGraph(),p=randomArray(k,1,n),a=randomArray(k,1,ub*5),add1(69));
			CASE(n=mxn,m=mxm,k=mxk,randomGraph(),p=randomArray(k,1,n),a=randomArray(k,1,ub*3/2),add1(69));
			CASE(n=mxn,m=mxm,k=mxk,randomGraph(),p=randomArray(k,1,n),a=randomArray(k,1,ub/2),add1(69));
			
			//random with optimal A upperbound
			CASE(n=rnd.nextInt(mxn/2,mxn),m=rnd.nextInt(n-1,mxm),k=rnd.nextInt(mxk/2,mxk),randomGraph(),p=randomArray(k,1,n),a=randomArray(k,1,ub),add1(69));
			CASE(n=mxn,m=mxm,k=mxk,randomGraph(),p=randomArray(k,1,n),a=randomArray(k,1,ub),add1(69));
			
			//tree
			CASE(n=mxn,m=n-1,k=mxk,randomGraph(),p=randomArray(k,1,n),a=randomArray(k,1,ub),add1(69));
			
			//line plus additional edges
			CASE(n=mxn,m=mxm,k=mxk,linePlusGraph(),p=randomArray(k,1,n),a=randomArray(k,1,mxw/3*n),add1(69));
			
			//line
			CASE(n=mxn,m=n-1,k=mxk,lineGraph(),p=randomArray(k,1,n),a=randomArray(k,1,mxw*n),add1(69));
			CASE(n=mxn,m=n-1,k=mxk,lineGraph(),permuteGraph(),p=randomArray(k,1,n),a=randomArray(k,1,mxw*n),add1(69));
			CASE(n=mxn,m=n-1,k=mxk,lineGraph(),w=randomArray(m,mxw,mxw),p=randomArray(k,1,n),lineMaxArray(),add1(69));
			
			//ribbon
			CASE(n=mxn,m=mxm,k=mxk,ribbonGraph(),p=randomArray(k,1,n),a=randomArray(k,mxw*3/2+1,mxw*3/2+1+mxw/3*9),add1(69));
			
			//pyqe graph
			CASE(n=mxn,m=mxm,k=mxk,pyqeGraph(),p=randomArray(k,1,n),a=randomArray(k,2,mxw),add1(69),addPyqe());
			
			//prabowo counter
			CASE(n=mxn,m=n*2-3,k=mxk,prabowoGraph(),p=randomArray(k,1,n),a=randomArray(k,1,mxw/3*n),add1(69));
			
			//same P
			CASE(n=mxn,m=mxm,k=mxk,randomGraph(),p=randomArray(k,rnd.nextInt(1,n),0),a=randomArray(k,1,ub),add1Same(69));
			
			//many students who go to the same schools
			CASE(n=mxn,m=mxm,k=mxk,randomGraph(),w=randomArray(m,mxw/2+1,mxw),p=randomArray(k,rnd.nextInt(n/2,n),0),a=randomArray(k,1,mxw/2),add1(69));
			CASE(n=mxn,m=mxm,k=mxk,randomGraph(),w=randomArray(m,mxw/2+1,mxw),p=randomArray(k,n/2,n/2+69),a=randomArray(k,1,mxw/2),add1(69));
			
			//there is a student who go to school N
			CASE(n=mxn,m=mxm,k=mxk,randomGraph(),w=randomArray(m,mxw/2+1,mxw),p=randomArray(k,1,n),a=randomArray(k,1,ub),add1(69),addN(69));
			
			//all students go to school 1
			CASE(n=mxn,m=mxm,k=mxk,randomGraph(),p=randomArray(k,1,n),a=randomArray(k,mxw*(n-1),mxa));
			
			//unbalanced N K
			CASE(n=mxn/5,m=mxm,k=mxk,randomGraph(),p=randomArray(k,1,n),a=randomArray(k,1,ub/5),add1(69));
			CASE(n=mxn,m=mxm,k=mxk/5,randomGraph(),p=randomArray(k,1,n),a=randomArray(k,1,ub),add1(69));
			
			//tiny N
			CASE(n=1,m=0,k=mxk,randomGraph(),p=randomArray(k,1,n),a=randomArray(k,1,mxa));
			CASE(n=2,m=1,k=mxk,randomGraph(),w=randomArray(m,mxw/2+1,mxw),p=randomArray(k,1,n),a=randomArray(k,1,mxw),add1(69));
			
			//star
			CASE(n=mxn,m=n-1,k=mxk,starGraph(),p=randomArray(k,1,n),a=randomArray(k,1,mxw*2),add1(69));
			
			//star plus additional edges
			CASE(n=mxn,m=mxm,k=mxk,starPlusGraph(),p=randomArray(k,1,n),a=randomArray(k,1,mxw*2),add1(69));
			
			//complete graph
			CASE(n=632,m=n*(n-1)/2,k=mxk,randomGraph(),p=randomArray(k,1,n),a=randomArray(k,1,mxw/2),add1(69));
			
			//K=1
			CASE(n=mxn,m=mxm,k=1,randomGraph(),p=randomArray(k,1,n),a=randomArray(k,1,ub/10));
		}
	
	private:
		void randomGraph()
		{
			GraphRandomizer graph_rand;
			tie(u,v)=graph_rand.node_count(n).edge_count(m).index_base(1).next().edges();
			w=randomArray(m,1,mxw);
		}
		void linePlusGraph()
		{
			int i;
			
			for(i=1;i<n;i++)
			{
				u.push_back(i);
				v.push_back(i+1);
			}
			w=randomArray(n-1,1,mxw/3);
			for(i=1;i<=n-2;i++)
			{
				u.push_back(i);
				v.push_back(i+2);
				w.push_back(rnd.nextInt(mxw/3*2,mxw));
			}
			for(i=1;i<=3;i++)
			{
				u.push_back(i);
				v.push_back(i+3);
				w.push_back(rnd.nextInt(mxw/3*3,mxw));
			}
		}
		void lineGraph()
		{
			int i;
			
			for(i=1;i<n;i++)
			{
				u.push_back(i);
				v.push_back(i+1);
			}
			w=randomArray(m,1,mxw);
		}
		void ribbonGraph()
		{
			int i;
			
			for(i=1;i<10;i++)
			{
				u.push_back(i);
				v.push_back(i+1);
			}
			w=randomArray(9,1,mxw/3);
			for(i=1;i<=8;i++)
			{
				u.push_back(i);
				v.push_back(i+2);
				w.push_back(rnd.nextInt(mxw/3*2,mxw));
			}
			for(i=1;i<=mxw/2;i++)
			{
				u.push_back(10);
				v.push_back(10+i);
				w.push_back(i);
				u.push_back(10+i);
				v.push_back(mxw/2+11);
				w.push_back(mxw+1-i*2);
			}
			for(i=mxw/2+12;i<=n;i++)
			{
				u.push_back(mxw/2+11);
				v.push_back(i);
				w.push_back(rnd.nextInt(1,mxw));
				if(i<n)
				{
					u.push_back(i);
					v.push_back(i+1);
					w.push_back(rnd.nextInt(1,mxw));
				}
				if(i<=mxw/2+17)
				{
					u.push_back(i);
					v.push_back(i+2);
					w.push_back(rnd.nextInt(1,mxw));
				}
			}
		}
		void pyqeGraph()
		{
			int i;
			
			for(i=1;i<=mxw-1;i++)
			{
				u.push_back(i);
				v.push_back(mxw);
				w.push_back(mxw-i);
				if(i<mxw-1)
				{
					u.push_back(i);
					v.push_back(i+1);
					w.push_back(mxw);
				}
			}
			for(i=mxw+1;i<=n;i++)
			{
				u.push_back(mxw);
				v.push_back(i);
				w.push_back(1);
				if(i<n)
				{
					u.push_back(i);
					v.push_back(i+1);
					w.push_back(rnd.nextInt(1,mxw));
				}
				if(i<=mxw+4)
				{
					u.push_back(i);
					v.push_back(i+2);
					w.push_back(rnd.nextInt(1,mxw));
				}
			}
		}
		void prabowoGraph()
		{
			int i;
			
			for(i=1;i<n;i++)
			{
				u.push_back(i);
				v.push_back(i+1);
			}
			w=randomArray(n-1,1,mxw/3);
			sort(w.begin(),w.end(),greater<int>());
			for(i=1;i<=n-2;i++)
			{
				u.push_back(i);
				v.push_back(i+2);
				w.push_back(rnd.nextInt(mxw/3*2,mxw));
			}
		}
		void starGraph()
		{
			int i;
			
			for(i=1;i<n;i++)
			{
				u.push_back(i);
			}
			v=randomArray(m,n,n);
			w=randomArray(m,1,mxw);
		}
		void starPlusGraph()
		{
			int i;
			
			for(i=1;i<n;i++)
			{
				u.push_back(i);
			}
			v=randomArray(n-1,n,n);
			w=randomArray(n-1,1,mxw);
			for(i=2;i<=n-2;i++)
			{
				u.push_back(i);
				v.push_back(i+1);
				w.push_back(rnd.nextInt(1,mxw));
			}
			for(i=2;i<=5;i++)
			{
				u.push_back(i);
				v.push_back(i+2);
				w.push_back(rnd.nextInt(1,mxw));
			}
		}
		void permuteGraph()
		{
			int i,pm[mxn+69];
			
			for(i=1;i<=n;i++)
			{
				pm[i]=i;
				swap(pm[i],pm[rnd.nextInt(1,i)]);
			}
			for(i=0;i<m;i++)
			{
				u[i]=pm[u[i]];
				v[i]=pm[v[i]];
			}
		}
		vector<int> randomArray(int sz,int lh,int rh)
		{
			int i;
			vector<int> cv;
			
			if(!rh)
			{
				rh=lh;
			}
			for(i=0;i<sz;i++)
			{
				cv.push_back(rnd.nextInt(lh,rh));
			}
			return cv;
		}
		void lineMaxArray()
		{
			int i,x;
			
			for(i=0;i<k;i++)
			{
				x=rnd.nextInt(1,2);
				a.push_back(max(rnd.nextInt(mxw*(p[i]-x),mxw*(p[i]-x+1)-1),1));
			}
		}
		void add1(int sz)
		{
			int i,x;
			
			for(i=0;i<sz;i++)
			{
				x=rnd.nextInt(0,k-1);
				p[x]=rnd.nextInt(1,n);
				a[x]=rnd.nextInt(mxw*(n-1),mxa);
			}
		}
		void addPyqe()
		{
			int x=rnd.nextInt(0,k-1);
			
			p[x]=mxw;
			a[x]=1;
		}
		void add1Same(int sz)
		{
			int i,x;
			
			for(i=0;i<sz;i++)
			{
				x=rnd.nextInt(0,k-1);
				a[x]=rnd.nextInt(mxw*(n-1),mxa);
			}
		}
		void addN(int sz)
		{
			int i,x;
			
			for(i=0;i<sz;i++)
			{
				x=rnd.nextInt(0,k-1);
				p[x]=n;
				a[x]=rnd.nextInt(1,mxw/2);
			}
		}
};
