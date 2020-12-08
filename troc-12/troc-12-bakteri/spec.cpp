#include<tcframe/spec.hpp>
using namespace tcframe;
const int maxs=100;
class ProblemSpec: public BaseProblemSpec{
protected:
	int n, m, k;
	string s;
	vector<vector<char> >ans;
	void InputFormat(){
		LINE(n, m, k);
	}
	void OutputFormat1(){
		LINE(s);
		GRID(ans)%SIZE(n, m);
	}
	void OutputFormat2() {
		LINE(s);
	}
	void GradingConfig(){
		TimeLimit(1);
		MemoryLimit(64);
	}
	void Constraints(){
		CONS(1<=n && n<=100);
		CONS(1<=m && m<=100);
		CONS(0<=k && k<=n*m);
	}
	void StyleConfig(){
		CustomScorer();
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
			"4 5 6",
		});
		Output({
			"YA",
			"...X.",
			"X.X..",
			"...X.",
			".X..X",
		});
	}
	void SampleTestCase2(){
		Subtasks({1});
		Input({
			"5 5 1",
		});
		Output({
			"TIDAK",
		});
	}
	void SampleTestCase3(){
		Subtasks({1});
		Input({
			"1 3 2",
		});
		Output({
			"YA",
			"X.X",
		});
	}
	void TestGroup1(){
		Subtasks({1});
		
		CASE(n=2; m=4; k=3;); //yes
		CASE(n=4; m=7; k=5;); //no
		CASE(n=1; m=1; k=1;); //yes
		CASE(n=1; m=1; k=0;); //no

		CASE(n=91; m=99; k=(n+m+1)/2);
		CASE(n=98; m=91; k=(n+m+1)/2);
		CASE(n=91; m=100; k=(n+m+1)/2);
		CASE(n=100; m=90; k=(n+m+1)/2);

		CASE(n=97; m=99; k=(n+m-1)/2);
		CASE(n=98; m=99; k=(n+m-1)/2);
		CASE(n=93; m=96; k=(n+m-1)/2);
		CASE(n=100; m=98; k=(n+m-1)/2);

		CASE(n=rnd.nextInt(10, 100); m=n; k=n-1);
		CASE(n=rnd.nextInt(10, 100); m=n; k=n);
		CASE(n=rnd.nextInt(10, 100); m=n; k=n+1);
        
		CASE(n=rnd.nextInt(1, 100); m=rnd.nextInt(1, 100); k=rnd.nextInt(0, n*m)); //general tc
		CASE(n=rnd.nextInt(1, 100); m=rnd.nextInt(1, 100); k=0); //general tc, no
		CASE(n=rnd.nextInt(1, 100); m=rnd.nextInt(1, 100); k=n*m); //general tc, yes

		CASE(n=rnd.nextInt(1, 2); m=rnd.nextInt(1, 2); k=rnd.nextInt(0, n*m)); //very small tc
		CASE(n=rnd.nextInt(3, 7); m=rnd.nextInt(3, 7); k=rnd.nextInt(0, min(7, n*m))); //small tc, random ans
		CASE(n=rnd.nextInt(3, 7); m=rnd.nextInt(3, 7); k=rnd.nextInt(7, min(49, n*m))); //small tc, yes
		
		CASE(n=1; m=rnd.nextInt(20, 100); k=m/2); //one row no
		CASE(n=1; m=rnd.nextInt(20, 100); k=m/2+1); //one row yes
		CASE(n=rnd.nextInt(20, 100); m=1; k=n/2); //one col no
		CASE(n=rnd.nextInt(20, 100); m=1; k=n/2+1); //one col yes

		CASE(n=rnd.nextInt(51, 100); m=rnd.nextInt(1, 50); k=rnd.nextInt(0, n*m)); //n>m
		CASE(n=rnd.nextInt(1, 50); m=rnd.nextInt(51, 100); k=rnd.nextInt(0, n*m)); //n<m

		CASE(n=100; m=100; k=rnd.nextInt(9000, 10000)); //max tc yes
	}
};
