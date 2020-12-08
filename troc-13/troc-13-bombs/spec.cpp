#include<bits/stdc++.h>
#include<tcframe/spec.hpp>
using namespace std;
using namespace tcframe;
const int mx=1000;

class ProblemSpec : public BaseProblemSpec{
	protected:
		int n, m, r;
		int ans;

		void InputFormat(){
			LINE(n, m, r);
		}
		void OutputFormat(){
			LINE(ans);
		}

		void GradingConfig(){
			TimeLimit(1);
			MemoryLimit(64);
		}
		void Constraints(){
			CONS(1<=n && n<=mx);
			CONS(1<=m && m<=mx);
			CONS(0<=r && r<=mx);
		}
		void Subtask1(){
			Points(100);
		}
};

class TestSpec : public BaseTestSpec<ProblemSpec>{
	protected:
		void SampleTestCase1(){
			Subtasks({1});
			Input({
				"1 7 3",
			});
			Output({
				"1",
			});
		}
		void SampleTestCase2(){
			Subtasks({1});
			Input({
				"5 5 0",
			});
			Output({
				"5",
			});
		}
		void TestGroup1(){
			Subtasks({1});

			//small grid small rad
			CASE(n=6; m=4; r=1;);
			CASE(n=rnd.nextInt(1, 20); m=rnd.nextInt(1, 20); r=rnd.nextInt(0, 9););
			//small grid large rad
			CASE(n=5; m=7; r=10;);
			CASE(n=rnd.nextInt(1, 20); m=rnd.nextInt(1, 20); r=rnd.nextInt(10, mx););
			//large grid small rad
			CASE(n=420; m=666; r=69;);
			CASE(n=rnd.nextInt(500, mx); m=rnd.nextInt(500, mx); r=rnd.nextInt(0, 50););
			//large grid large rad
			CASE(n=835; m=982; r=263);
			CASE(n=rnd.nextInt(900, mx); m=rnd.nextInt(900, mx); r=rnd.nextInt(200, mx/2););

			//rad overflow grid (r=mx)
			CASE(n=rnd.nextInt(100, mx); m=rnd.nextInt(100, mx); r=mx;);
			CASE(n=mx; m=mx; r=mx;);
			CASE(n=mx; m=1; r=mx;); 

			//r=0
			CASE(n=rnd.nextInt(100, mx); m=rnd.nextInt(100, mx); r=0;);
			CASE(n=mx; m=mx; r=0;);
			CASE(n=1; m=mx; r=0;);
		}
};
