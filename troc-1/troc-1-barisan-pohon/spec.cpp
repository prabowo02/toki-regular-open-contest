#include<bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace std;
using namespace tcframe;

const int MAX_N=300000;
const int MAX_A=1000000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N;
    vector<int> A;
    
    int ans;

    void InputFormat() {
        LINE(N);
        LINE(A%SIZE(N));
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }
    
    void Constraints() {
		CONS(Between(N,1,MAX_N));
		CONS(AllBetween(A,1,MAX_A));
	}

    void Subtask1() {
	}
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
            "5 7 9 17 22"
        });
        Output({
            "2"
        });
    }
    
    void BeforeTestCase() {
		A.clear();
	}

    void TestGroup1() {
		Subtasks({1});
		
		StrongTC();
		SmallTC();
		LargeTC();
	}
private:
	void StrongTC() {
		CASE(N=rnd.nextInt(1,10000), StrongIncreasing(N,rnd.nextInt(4,100)));
		CASE(N=rnd.nextInt(1,10000), StrongDecreasing(N,rnd.nextInt(4,100)));
		CASE(N=rnd.nextInt(1,10000), StrongSame(N,rnd.nextInt(4,100)));
		CASE(N=rnd.nextInt(1,10000), StrongIncreasing(N,2));
		CASE(N=rnd.nextInt(1,10000), StrongDecreasing(N,2));
		CASE(N=rnd.nextInt(1,10000), StrongIncreasing(N,3));
		CASE(N=rnd.nextInt(1,10000), StrongDecreasing(N,3));
		
		CASE(N=rnd.nextInt(MAX_N-100,MAX_N), StrongIncreasing(N,3));
		CASE(N=rnd.nextInt(MAX_N-100,MAX_N), StrongDecreasing(N,3));
		CASE(N=rnd.nextInt(MAX_N-100,MAX_N), StrongSame(N,3));
	}
	void SmallTC() {	//1<=N<=10000
		//N=1
		CASE(N=1, A={1});
		
		//N=2
		CASE(N=2, A={MAX_A,MAX_A});
		CASE(N=2, A={MAX_A-1,MAX_A});
		CASE(N=2, A={MAX_A,MAX_A-1});
		
		//N=5, 1<=Ai<=100
		CASE(N=5, A={2,2,3,4,5});
		CASE(N=5, A={2,3,4,5,5});
		CASE(N=5, A={5,4,3,2,2});
		CASE(N=5, A={5,5,4,3,2});
		CASE(N=5, A={1,1,2,3,4});
		CASE(N=5, A={1,2,4,6,8});
		CASE(N=5, A={4,3,2,1,1});
		CASE(N=5, A={8,6,4,2,1});
		CASE(N=5, A={MAX_A-3,MAX_A-2,MAX_A-1,MAX_A,MAX_A});
		CASE(N=5, A={MAX_A-7,MAX_A-5,MAX_A-3,MAX_A-1,MAX_A});
		CASE(N=5, A={MAX_A,MAX_A,MAX_A-1,MAX_A-2,MAX_A-3});
		CASE(N=5, A={MAX_A,MAX_A-1,MAX_A-3,MAX_A-5,MAX_A-7});
		
		CASE(N=rnd.nextInt(1,10000), squareNumber(N));
		CASE(N=rnd.nextInt(1,10000), reverseSquareNumber(N));
		CASE(N=rnd.nextInt(1,10000), arithmeticIncreasing(N,1,MAX_A));
		CASE(N=rnd.nextInt(1,10000), arithmeticDecreasing(N,1,MAX_A));
		CASE(N=rnd.nextInt(1,10000), allSame(N,rnd.nextInt(1,MAX_A)));
		CASE(N=rnd.nextInt(1,10000), generator1(N,1,MAX_A));
		CASE(N=rnd.nextInt(1,10000), generator2(N,1,MAX_A,30));
		CASE(N=rnd.nextInt(1,10000), generator3(N,MAX_A));
		CASE(N=rnd.nextInt(1,10000), generator4(N,1,MAX_A,rnd.nextInt(1,N)));
	}
	void LargeTC() {
		CASE(N=rnd.nextInt(10001,MAX_N/10), generator1(N,1,MAX_A));
		CASE(N=rnd.nextInt(10001,MAX_N/10), generator2(N,1,MAX_A,50));
		CASE(N=rnd.nextInt(10001,MAX_N/10), generator3(N,MAX_A));
		CASE(N=rnd.nextInt(10001,MAX_N/10), generator4(N,1,MAX_A,rnd.nextInt(10,100)));
		
		CASE(N=MAX_N, squareNumber(N));
		CASE(N=MAX_N, reverseSquareNumber(N));
		CASE(N=MAX_N, generator1(N,1,MAX_A));
		CASE(N=MAX_N, generator2(N,1,MAX_A,90));
		CASE(N=MAX_N, generator3(N,MAX_A));
		CASE(N=MAX_N, generator4(N,1,MAX_A,rnd.nextInt(10,100)));
	}
	
	bool between(int x,int l,int r) {
		return (l<=x && x<=r);
	}
	void squareNumber(int N) {
		for (int i=1;i<=N;i++) {
			if (i<=1000) A.push_back(i*i);
			else A.push_back(rnd.nextInt(1,9));
		}
	}
	void reverseSquareNumber(int N) {
		int cur=min(1000,N);
		for (int i=1;i<=N;i++) {
			if (i<=1000) A.push_back(cur*cur), cur--;
			else A.push_back(rnd.nextInt(1,9));
		}
	}
	void arithmeticIncreasing(int N,int l,int r) {
		int A0=rnd.nextInt(l,(l+r)/2);
		int D=rnd.nextInt(0,(r-A0)/N);
		int cur=A0;
		for (int i=0;i<N;i++) {
			A.push_back(cur); cur+=D;
		}
	}
	void arithmeticDecreasing(int N,int l,int r) {
		arithmeticIncreasing(N,l,r);
		reverse(A.begin(),A.end());
	}
	void allSame(int N,int x) {
		for (int i=0;i<N;i++) A.push_back(x);
	}
	void generator1(int N,int l,int r) {	//Totally Random
		for (int i=0;i<N;i++) A.push_back(rnd.nextInt(l,r));
	}
	void generator2(int N,int l, int r,int chance) {	//Arithmetic + Random (chance being change)
		int temp=rnd.nextInt(0,1);
		if (temp==0) arithmeticIncreasing(N,l,r);
		else arithmeticDecreasing(N,l,r);
		for (int i=0;i<N;i++) {
			int c=rnd.nextInt(0,100);
			if (c<=chance || !between(A[i],l,r)) A[i]=rnd.nextInt(l,r);
		}
	}
	void generator3(int N,int r) {	//High Density Random
		int l=max(1,r-N); generator1(N,l,r);
	}
	void generator4(int N,int l,int r,int K) {	//Arithmetic + Random (change random K number)
		int temp=rnd.nextInt(0,1);
		if (temp==0) arithmeticIncreasing(N,l,r);
		else arithmeticDecreasing(N,l,r);
		vector<int> pool; for (int i=1;i<=N;i++) pool.push_back(i);
		rnd.shuffle(pool.begin(),pool.end());
		for (int i=0;i<K;i++) {
			A[pool[i]]=rnd.nextInt(l,r);
		}
	}
	
	void GenerateStrong(int N,int K,vector<pair<int,int> > &ans) {	//ans = vector<A0,D>
		int cur=K;
		for (int i=0;i<N;i++) {
			if (cur==K) rnd.shuffle(ans.begin(),ans.end()), cur=0;
			A.push_back(ans[cur].first+ans[cur].second*i); cur++;
		}
	}
	void StrongIncreasing(int N,int K) {	//K candidates of answer, D>0
		vector<pair<int,int> > ans;
		for (int i=0;i<K;i++) {
			ans.push_back({rnd.nextInt(1,10),rnd.nextInt(1,(MAX_A-10)/N)});
		}
		GenerateStrong(N,K,ans);
	}
	void StrongDecreasing(int N,int K) {	//K candidates of answer, D<0
		vector<pair<int,int> > ans;
		for (int i=0;i<K;i++) {
			ans.push_back({MAX_A-rnd.nextInt(1,10),-rnd.nextInt(1,(MAX_A-10)/N)});
		}
		GenerateStrong(N,K,ans);
	}
	void StrongSame(int N,int K) {
		vector<pair<int,int> > ans;
		for (int i=0;i<K;i++) {
			ans.push_back({rnd.nextInt(1,MAX_A),0});
		}
		GenerateStrong(N,K,ans);
	}
};
