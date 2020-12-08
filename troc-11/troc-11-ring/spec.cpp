#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const long long mxn=1e9,mxm=1e18;

class ProblemSpec:public BaseProblemSpec
{
	protected:
		long long n,l,r,d,m,z;
		
		void InputFormat()
		{
			LINE(n,l,r);
			LINE(d,m);
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
			CONS(3<=n&&n<=mxn);
			CONS(3<=l&&l<=r&&r<=mxm);
			CONS(0<=d&&d<m&&m<=mxm);
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
				"3 3 6",
				"2 4"
			});
			Output
			({
				"6"
			});
		}
		void SampleTestCase2()
		{
			Subtasks({1});
			Input
			({
				"4 4 9",
				"1 3"
			});
			Output
			({
				"192"
			});
		}
		void SampleTestCase3()
		{
			Subtasks({1});
			Input
			({
				"5 5 5",
				"0 9"
			});
			Output
			({
				"0"
			});
		}
		void TestGroup1()
		{
			Subtasks({1});

			CASE(n=rnd.nextLongLong(4,mxn),l=rnd.nextLongLong(mxn,mxm),r=l,d=0,m=1);
			CASE(n=rnd.nextLongLong(4,mxn),l=3,r=3,d=0,m=1);
			CASE(n=rnd.nextLongLong(4,mxn),l=mxm,r=mxm,d=0,m=1);

			CASE(n=rnd.nextLongLong(4,mxn),rnd2(l,r,mxn,mxm),d=0,m=1);
			CASE(n=rnd.nextLongLong(4,mxn),l=rnd.nextLongLong(3,100000),r=rnd.nextLongLong(mxm-100000,mxm),d=0,m=1);
			CASE(n=mxn,rnd2(l,r,mxn,mxm),d=0,m=1);
			CASE(n=rnd.nextLongLong(4,mxn),l=3,r=mxm,d=0,m=1);
			CASE(n=mxn,l=3,r=mxm,d=0,m=1);

			CASE(n=3,rnd2(l,r,mxn,mxm),d=0,m=1);

			CASE(n=rnd.nextLongLong(4,mxn),rnd2(l,r,mxn,mxm),d=0,m=2);
			CASE(n=rnd.nextLongLong(4,mxn),rnd2(l,r,mxn,mxm),d=1,m=2);

			CASE(n=rnd.nextLongLong(4,mxn),rnd2(l,r,mxn,mxm-mxn+1),r+=mxn-1,m=rnd.nextLongLong(mxn,r-l+1),d=rnd.nextLongLong(0,m-1));
			CASE(n=mxn,rnd2(l,r,mxn,mxm-mxn+1),r+=mxn-1,m=rnd.nextLongLong(mxn,r-l+1),d=rnd.nextLongLong(0,m-1));
			CASE(n=rnd.nextLongLong(4,mxn),l=rnd.nextLongLong(3,100000),r=rnd.nextLongLong(mxm-100000,mxm),m=rnd.nextLongLong(mxn,r-l+1),d=rnd.nextLongLong(0,m-1));
			CASE(n=rnd.nextLongLong(4,mxn),l=3,r=mxm,m=rnd.nextLongLong(mxn,mxm-2),d=rnd.nextLongLong(0,m-1));

			CASE(n=rnd.nextLongLong(4,mxn),rnd2(l,r,mxn,mxm-99999),r+=99999,rnd2(d,m,3,100000),d--);
			CASE(n=rnd.nextLongLong(4,mxn),l=3,r=mxm,rnd2(d,m,3,100000),d--);

			CASE(n=rnd.nextLongLong(4,mxn),l=rnd.nextLongLong(3,100000),r=rnd.nextLongLong(mxm-100000,mxm),m=rnd.nextLongLong(mxn-100000,mxn+100000),d=rnd.nextLongLong(0,m-1));
			CASE(n=rnd.nextLongLong(4,mxn),l=3,r=mxm,m=rnd.nextLongLong(mxn-100000,mxn+100000),d=rnd.nextLongLong(0,m-1));

			CASE(n=3,rnd2(l,r,mxn,mxm-mxn+1),r+=mxn-1,m=rnd.nextLongLong(mxn,r-l+1)/3*3,d=0);

			CASE(n=rnd.nextLongLong(4,mxn),rnd2(l,r,mxn,mxm-1),d=l,m=mxm);
			CASE(n=rnd.nextLongLong(4,mxn),rnd2(l,r,mxn,mxm-1),d=l-1,m=mxm);
			CASE(n=rnd.nextLongLong(4,mxn),rnd2(l,r,mxn,mxm-1),d=r,m=mxm);
			CASE(n=rnd.nextLongLong(4,mxn),rnd2(l,r,mxn,mxm-2),d=r+1,m=mxm);
			CASE(n=rnd.nextLongLong(4,mxn),l=mxm,r=mxm,d=0,m=mxm);
			CASE(n=rnd.nextLongLong(4,mxn),l=mxm,r=mxm,d=1,m=mxm);
			CASE(n=rnd.nextLongLong(4,mxn),l=3,r=3,d=mxm-1,m=mxm);

			CASE(n=rnd.nextLongLong(4,mxn),l=rnd.nextLongLong(mxn,mxm),r=l,m=rnd.nextLongLong(mxn,mxm),d=l%m);

			CASE(n=3,rnd2(l,r,mxn,mxm-mxn+1),r+=mxn-1,m=rnd.nextLongLong(3,100000)/3*3+rnd.nextLongLong(1,2),d=rnd.nextLongLong(0,m-1));
		}

	private:
		void rnd2(long long &x,long long &y,long long lh,long long rh)
		{
			x=rnd.nextLongLong(lh,rh);
			y=rnd.nextLongLong(lh,rh);
			if(x>y)
			{
				swap(x,y);
			}
		}
};

/*
Summary tc:
l=r, m=1
1 -
2 min lr
3 max lr

l!=r, m=1
4 -
5 big range lr
6 max n
7 max range lr
8 max n, max range lr

n<=3, m=1
9  n=3

m=2
10  d=0
11  d=1

big m
12  -
13  max n
14  big range lr
15  max range lr

m<=1e5
16  -
17  max range lr

m around 1e9
18  big range lr
19  max range lr

n<=3, big m
20  n=3, d=0, m%3=0

max m
21  d=l
22  d=l-1
23  d=r
24  d=r+1
25  max lr, d=0
26  max lr, d=1
27  min lr, max d

l=r, big m
28  d=l%m

29 n=3 m%3!=0
*/
