#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int mxn=300,mxa=1e9,mxq=1e5;

class ProblemSpec : public BaseProblemSpec
{
	protected:
		int n,q;
		vector<int> x,y,c,a,b,p,sq;
		
		void InputFormat()
		{
			LINE(n);
			LINES(x,y)%SIZE(n*n);
			LINE(q);
			LINES(c,a,b)%SIZE(q);
		}
		void OutputFormat()
		{
			LINE(p%SIZE(n*n));
			LINES(sq)%SIZE(q);
		}
		void GradingConfig()
		{
			TimeLimit(1);
			MemoryLimit(64);
		}
		void Constraints()
		{
			CONS(2<=n&&n<=mxn);
			CONS(eachElementBetween(x,0,mxa));
			CONS(eachElementBetween(y,0,mxa));
			CONS(1<=q&&q<=mxq);
			CONS(eachElementBetween(c,1,n*n));
			CONS(eachElementBetween(a,0,mxa));
			CONS(eachElementBetween(b,0,mxa));
		}
		void StyleConfig()
		{
			CustomScorer();
		}
		void Subtask1()
		{
			Points(100);
		}
	
	private:
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
};

class TestSpec : public BaseTestSpec<ProblemSpec>
{
	protected:
		void SampleTestCase1()
		{
			Subtasks({1});
			Input
			({
				"3",
				"0 0",
				"1 3",
				"7 7",
				"5 3",
				"4 2",
				"2 5",
				"5 5",
				"9 5",
				"12 9",
				"2",
				"9 11 0",
				"5 3 6"
			});
			Output
			({
				"1 2 5 4 7 6 3 8 9",
				"9",
				"6"
			});
		}
		void SampleTestCase2()
		{
			Subtasks({1});
			Input
			({
				"3",
				"0 0",
				"1 1000000000",
				"1 0",
				"2 1000000000",
				"2 0",
				"3 1000000000",
				"3 0",
				"4 1000000000",
				"4 0",
				"1",
				"2 1000000000 1000000000"
			});
			Output
			({
				"1 3 5 7 9 8 6 4 2",
				"2"
			});
		}
		void BeforeTestCase()
		{
			x.clear();
			y.clear();
			c.clear();
			a.clear();
			b.clear();
		}
		void TestGroup1()
		{
			Subtasks({1});
			
			// random to random
			CASE(n=rnd.nextInt(1,mxn),randomPoints(),q=rnd.nextInt(1,mxq),randomQueries());
			CASE(n=mxn,randomPoints(),q=mxq,randomQueries());
			CASE(n=mxn,randomPoints(),q=mxq,randomQueries());
			CASE(n=rnd.nextInt(4,100),randomPoints(),q=mxq,randomQueries());
			CASE(n=rnd.nextInt(4,100),randomPoints(),q=mxq,randomQueries());
			CASE(n=3,randomPoints(),q=mxq,randomQueries());
			CASE(n=2,randomPoints(),q=mxq,randomQueries());
			
			// gridded to random
			CASE(n=mxn,griddedPoints(),q=mxq,randomQueries());
			CASE(n=rnd.nextInt(4,100),griddedPoints(),q=mxq,randomQueries());
			
			// gridded to gridded
			CASE(n=mxn,griddedPoints(),q=mxq,griddedQueries());
			CASE(n=rnd.nextInt(4,100),griddedPoints(),q=mxq,griddedQueries());
			
			// random to gridded
			CASE(n=mxn,randomPoints(),q=mxq,griddedQueries());
			CASE(n=rnd.nextInt(4,100),randomPoints(),q=mxq,griddedQueries());
			
			// always gridded
			CASE(n=mxn,q=mxq,alwaysGridded());
			CASE(n=rnd.nextInt(4,100),q=mxq,alwaysGridded());
			CASE(n=3,q=mxq,alwaysGridded());
			CASE(n=2,q=mxq,alwaysGridded());
			
			// corner points
			CASE(n=mxn,cornerPoints(),q=mxq,cornerQueries());
			CASE(n=2,cornerPoints(),q=mxq,cornerQueries());
			
			// edge points
			CASE(n=mxn,edgePoints(0),q=mxq,edgeQueries(0));
			CASE(n=mxn,edgePoints(0),q=mxq,uniqueEdgeQueries(1));
			CASE(n=rnd.nextInt(4,100),edgePoints(1),q=mxq,uniqueEdgeQueries(0));
			CASE(n=mxn,edgePoints(1),q=mxq,edgeQueries(1));
			
			// anti Unbalanced Binary Search Tree
			CASE(n=mxn,q=mxq,antiUBST(0));
			CASE(n=mxn,q=mxq,antiUBST(1));
			
			// same points
			CASE(n=mxn,randomPoints(),q=mxq,sameQueries());
			CASE(n=mxn,samePoints(),q=mxq,scatterQueries());
			CASE(n=mxn,samePoints(),q=mxq,stayQueries());
			
			// the same points move many times
			CASE(n=mxn,randomPoints(),q=mxq,fewPointsQueries());
			CASE(n=rnd.nextInt(4,100),randomPoints(),q=mxq,fewPointsQueries());
		}
	
	private:
		void randomPoints()
		{
			int i;
			
			for(i=0;i<n*n;i++)
			{
				x.push_back(rnd.nextInt(0,mxa));
				y.push_back(rnd.nextInt(0,mxa));
			}
		}
		void griddedPoints()
		{
			int i,j,k;
			
			for(i=0;i<n;i++)
			{
				for(j=0;j<n;j++)
				{
					x.push_back(rnd.nextInt((long long)i*mxa/n,(long long)(i+1)*mxa/n));
					y.push_back(rnd.nextInt((long long)j*mxa/n,(long long)(j+1)*mxa/n));
				}
			}
			for(i=0;i<n*n;i++)
			{
				k=rnd.nextInt(0,i);
				swap(x[i],x[k]);
				swap(y[i],y[k]);
			}
		}
		void cornerPoints()
		{
			int i;
			
			for(i=0;i<n*n;i++)
			{
				x.push_back(mxa*rnd.nextInt(0,1));
				y.push_back(mxa*rnd.nextInt(0,1));
			}
		}
		void edgePoints(bool e)
		{
			int i;
			
			for(i=0;i<n*n;i++)
			{
				x.push_back(mxa*rnd.nextInt(0,1));
				y.push_back(rnd.nextInt(0,mxa));
				if(e)
				{
					swap(x[i],y[i]);
				}
			}
		}
		void samePoints()
		{
			int i,cx=rnd.nextInt(0,mxa),cy=rnd.nextInt(0,mxa);
			
			for(i=0;i<n*n;i++)
			{
				x.push_back(cx);
				y.push_back(cy);
			}
		}
		void uniqueC()
		{
			int i,sz=max(q-n*n,0);
			
			for(i=0;i<sz;i++)
			{
				c.push_back(rnd.nextInt(1,n*n));
			}
			for(i=sz;i<q;i++)
			{
				c.push_back(rnd.nextInt(1,max(n*n-q,0)+1));
			}
			sort(c.begin()+sz,c.end());
			for(i=sz;i<q;i++)
			{
				c[i]+=i-sz;
				swap(c[i],c[rnd.nextInt(sz,i)]);
			}
		}
		void randomQueries()
		{
			int i;
			
			for(i=0;i<q;i++)
			{
				c.push_back(rnd.nextInt(1,n*n));
				a.push_back(rnd.nextInt(0,mxa));
				b.push_back(rnd.nextInt(0,mxa));
			}
		}
		void griddedQueries()
		{
			int i,k,cx,cy,sz=max(q-n*n,0);
			
			uniqueC();
			for(i=0;i<sz;i++)
			{
				a.push_back(rnd.nextInt(0,mxa));
				b.push_back(rnd.nextInt(0,mxa));
			}
			for(i=sz;i<q;i++)
			{
				a.push_back(rnd.nextInt(0,max(n*n-q,0)));
			}
			sort(a.begin()+sz,a.end());
			for(i=sz;i<q;i++)
			{
				a[i]+=i-sz;
				cx=a[i]/n;
				cy=a[i]%n;
				a[i]=rnd.nextInt((long long)cx*mxa/n,(long long)(cx+1)*mxa/n);
				b.push_back(rnd.nextInt((long long)cy*mxa/n,(long long)(cy+1)*mxa/n));
				k=rnd.nextInt(sz,i);
				swap(a[i],a[k]);
				swap(b[i],b[k]);
			}
		}
		void cornerQueries()
		{
			int i;
			
			for(i=0;i<q;i++)
			{
				c.push_back(rnd.nextInt(1,n*n));
				a.push_back(mxa*rnd.nextInt(0,1));
				b.push_back(mxa*rnd.nextInt(0,1));
			}
		}
		void edgeQueries(bool e)
		{
			int i;
			
			for(i=0;i<q;i++)
			{
				c.push_back(rnd.nextInt(1,n*n));
				a.push_back(mxa*rnd.nextInt(0,1));
				b.push_back(rnd.nextInt(0,mxa));
				if(e)
				{
					swap(a[i],b[i]);
				}
			}
		}
		void uniqueEdgeQueries(bool e)
		{
			int i,sz=max(q-n*n,0);
			
			uniqueC();
			for(i=0;i<sz;i++)
			{
				a.push_back(rnd.nextInt(0,mxa));
				b.push_back(rnd.nextInt(0,mxa));
			}
			for(i=sz;i<q;i++)
			{
				a.push_back(mxa*rnd.nextInt(0,1));
				b.push_back(rnd.nextInt(0,mxa));
				if(e)
				{
					swap(a[i],b[i]);
				}
			}
		}
		void sameQueries()
		{
			int i,cx=rnd.nextInt(0,mxa),cy=rnd.nextInt(0,mxa),sz=max(q-n*n,0);
			
			uniqueC();
			for(i=0;i<sz;i++)
			{
				a.push_back(rnd.nextInt(0,mxa));
				b.push_back(rnd.nextInt(0,mxa));
			}
			for(i=sz;i<q;i++)
			{
				a.push_back(cx);
				b.push_back(cy);
			}
		}
		void scatterQueries()
		{
			int i;
			
			uniqueC();
			for(i=0;i<q;i++)
			{
				a.push_back(rnd.nextInt(0,mxa));
				b.push_back(rnd.nextInt(0,mxa));
			}
		}
		void stayQueries()
		{
			int i;
			
			for(i=0;i<q;i++)
			{
				c.push_back(rnd.nextInt(1,n*n));
				a.push_back(x[c[i]-1]);
				b.push_back(y[c[i]-1]);
			}
		}
		void fewPointsQueries()
		{
			int i;
			vector<int> ky;
			
			for(i=0;i<5;i++)
			{
				ky.push_back(rnd.nextInt(1,n*n-4));
			}
			sort(ky.begin(),ky.end());
			for(i=0;i<5;i++)
			{
				ky[i]+=i;
			}
			for(i=0;i<q;i++)
			{
				c.push_back(ky[rnd.nextInt(0,4)]);
				a.push_back(rnd.nextInt(0,mxa));
				b.push_back(rnd.nextInt(0,mxa));
			}
		}
		void alwaysGridded()
		{
			int i,j,k,lx,ly;
			vector<int> cx,cy;
			
			for(i=0;i<n;i++)
			{
				for(j=0;j<n;j++)
				{
					cx.push_back(i);
					cy.push_back(j);
					x.push_back(rnd.nextInt((long long)i*mxa/n,(long long)(i+1)*mxa/n));
					y.push_back(rnd.nextInt((long long)j*mxa/n,(long long)(j+1)*mxa/n));
				}
			}
			for(i=0;i<n*n;i++)
			{
				k=rnd.nextInt(0,i);
				swap(cx[i],cx[k]);
				swap(cy[i],cy[k]);
				swap(x[i],x[k]);
				swap(y[i],y[k]);
			}
			lx=rnd.nextInt(0,n-1);
			ly=rnd.nextInt(0,n-1);
			for(i=0;i<q;i++)
			{
				c.push_back(rnd.nextInt(1,n*n));
				a.push_back(rnd.nextInt((long long)lx*mxa/n,(long long)(lx+1)*mxa/n));
				b.push_back(rnd.nextInt((long long)ly*mxa/n,(long long)(ly+1)*mxa/n));
				swap(lx,cx[c[i]-1]);
				swap(ly,cy[c[i]-1]);
			}
		}
		void antiUBST(bool e)
		{
			int i,cy=rnd.nextInt(0,mxa);
			vector<int> as;
			
			for(i=0;i<n*n+q;i++)
			{
				as.push_back(rnd.nextInt(0,mxa));
			}
			sort(as.begin(),as.end());
			for(i=0;i<n*n;i++)
			{
				x.push_back(as[i]);
				swap(x[i],x[rnd.nextInt(0,i)]);
				y.push_back(cy);
			}
			if(e)
			{
				for(i=0;i<n*n;i++)
				{
					swap(x[i],y[i]);
				}
			}
			for(i=0;i<q;i++)
			{
				c.push_back(rnd.nextInt(1,n*n));
				a.push_back(as[n*n+i]);
				b.push_back(cy);
				if(e)
				{
					swap(a[i],b[i]);
				}
			}
		}
};
