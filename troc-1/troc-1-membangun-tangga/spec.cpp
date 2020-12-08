#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAX_N = 100000;
const int MAX_A = 1000000000;

class ProblemSpec : public BaseProblemSpec {
protected:
	int N;
	vector<int> A;
	long long ANS;

	void InputFormat() { 
		LINE(N);
		LINE(A%SIZE(N)); 
	}

	void OutputFormat() { 
		LINE(ANS); 
	}

	void Constraints() {
		CONS(Between(N,1,MAX_N));
		CONS(AllBetween(A,1,MAX_A));
	}

	void Subtask1() {}

private:
	bool Between(int x,int l,int r) {
		return (l<=x && x<=r);
	}
	bool AllBetween(vector<int> &V,int l,int r) {
		for (int data:V) if (!Between(data,l,r)) return false; return true;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Subtasks({1});

		Input({
			"5",
			"5 4 3 2 1"
		});
    
		Output({
			"0"
		});
	}

	void SampleTestCase2() {
		Subtasks({1});

		Input({
			"5",
			"5 4 1 2 1"
		});
    
		Output({
			"2"
		});
	}
	
	void SampleTestCase3() {
		Subtasks({1});

		Input({
			"5",
			"4 4 2 2 1"
		});
    
		Output({
			"15"
		});
	}

	void BeforeTestCase() {
		A.clear();
	}

	void TestGroup1() {
		Subtasks({1});
		
		SmallTC();
		LargeTC();
	}
private:
	void SmallTC() {	//1<=N<=10, 1<=Ai<=1E9
		//N=1
		CASE(N=1, A={1});
		CASE(N=1, RandomArray(1,2,MAX_A));
		
		//N=2
		CASE(N=2, A={1,1});
		CASE(N=2, A={1,MAX_A});
		CASE(N=2, A={MAX_A,1});
		CASE(N=2, A={MAX_A,MAX_A});
		CASE(N=2, SortedIncreasing(N,3,MAX_A-1));
		CASE(N=2, SortedDecreasing(N,3,MAX_A-1));
		CASE(N=2, Box(N,3,MAX_A-1));
		
		//N=3
		CASE(N=3, A={1,1,1});
		CASE(N=3, A={1,2,3});
		CASE(N=3, A={3,2,1});
		CASE(N=3, A={1,1,MAX_A});
		CASE(N=3, A={1,MAX_A,1});
		CASE(N=3, A={MAX_A,1,1});
		CASE(N=3, A={MAX_A,MAX_A,1});
		CASE(N=3, A={MAX_A,1,MAX_A});
		CASE(N=3, A={1,MAX_A,MAX_A});
		CASE(N=3, A={MAX_A,MAX_A,MAX_A});
		CASE(N=3, RandomArray(N,3,MAX_A-1));
		CASE(N=3, SortedIncreasing(N,3,MAX_A-1));
		CASE(N=3, SortedDecreasing(N,3,MAX_A-1));
		CASE(N=3, Box(N,3,MAX_A-1));
		
		//4<=N<=10
		CASE(N=rnd.nextInt(4,10), RandomArray(N,3,MAX_A-1));
		CASE(N=rnd.nextInt(4,10), SortedDecreasing(N,3,MAX_A-1));
		CASE(N=rnd.nextInt(4,10), Box(N,3,MAX_A-1));
		CASE(N=rnd.nextInt(4,10), OneHoleStairs(N));
		CASE(N=rnd.nextInt(4,10), Stairs(N));
		CASE(N=rnd.nextInt(4,10), LargestAnswer(N));
	}
	
	void LargeTC() {	//11<=N<=1E5, 1<=Ai<=1E9
		//11<=N<=100
		CASE(N=rnd.nextInt(11,100), RandomArray(N,1,MAX_A));
		CASE(N=rnd.nextInt(11,100), SortedDecreasing(N,1,MAX_A));
		CASE(N=rnd.nextInt(11,100), OneHoleStairs(N));
		
		//101<=N<=10000
		CASE(N=rnd.nextInt(101,10000), RandomArray(N,1,MAX_A));
		CASE(N=rnd.nextInt(101,10000), SortedDecreasing(N,1,MAX_A));
		CASE(N=rnd.nextInt(101,10000), OneHoleStairs(N));
		
		//10001<=N<=99999
		CASE(N=rnd.nextInt(10001,99999), RandomArray(N,1,MAX_A));
		CASE(N=rnd.nextInt(10001,99999), SortedDecreasing(N,1,MAX_A));
		CASE(N=rnd.nextInt(10001,99999), Box(N,1,MAX_A));
		CASE(N=rnd.nextInt(10001,99999), Stairs(N));
		CASE(N=rnd.nextInt(10001,99999), OneHoleStairs(N));
		
		//N=100000
		CASE(N=100000, RandomArray(N,1,MAX_A));
		CASE(N=100000, SortedIncreasing(N,1,MAX_A));
		CASE(N=100000, SortedDecreasing(N,1,MAX_A));
		CASE(N=100000, Box(N,1,1));
		CASE(N=100000, Box(N,2,MAX_A-1));
		CASE(N=100000, Box(N,MAX_A,MAX_A));
		CASE(N=100000, OneHoleStairs(N));
		CASE(N=100000, LargestAnswer(N));
	}
	
	void LargestAnswer(int n) {	//A={1, 1, 1, ..., 1, MAX_A}
		for (int i=0;i<n-1;i++) A.push_back(1);
		A.push_back(MAX_A);
	}
	
	void RandomArray(int n,int l,int r) {
		for (int i=0;i<n;i++) A.push_back(rnd.nextInt(l,r));
	}
	
	void SortedIncreasing(int n,int l,int r) {
		RandomArray(n,l,r);
		sort(A.begin(),A.end());
	}
	
	void SortedDecreasing(int n,int l,int r) {
		SortedIncreasing(n,l,r);
		reverse(A.begin(),A.end());
	}
	
	void Box(int n,int l,int r) {	//A={x, x, x, ..., x}
		int x=rnd.nextInt(l,r);
		for (int i=0;i<n;i++) A.push_back(x);
	}
	
	void Stairs(int n) {	//A={n, n-1, n-2, ..., 1}
		int cur=n;
		for (int i=0;i<n;i++) A.push_back(cur--);
	}
	
	void OneHoleStairs(int n) {
		Stairs(n);
		int start=rnd.nextInt(0,n-2);
		int end=rnd.nextInt(start+1,n-1);
		for (int i=start;i<=end;i++) {
			if (A[i]>1) A[i]=rnd.nextInt(1,A[i]-1);
		}
	}
};
