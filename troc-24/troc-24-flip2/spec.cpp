#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int maxn=100000;
const int INF=1000000000;

class ProblemSpec : public BaseProblemSpec {
  protected:
	int n;
	vector<int> arr;
	long long ans;
	
	void InputFormat() {
		LINE(n);
		LINE(arr % SIZE(n));
	}
	void OutputFormat() {
		LINE(ans);
	}
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(256);
	}
	void Constraints() {
		CONS(2<=n && n<=maxn);
		CONS(n%2==0); //n is even
		CONS(eachElementBetween(arr,-INF,INF));
	}
	
  private:
    bool eachElementBetween(vector<int> v,int l,int r){
		for (auto it:v){
			if (it<l || r<it) return false;
		}
		return true;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
  protected:
	void SampleTestCase1(){
		Input({
			"2",
			"123 456"
		});
		
		Output({
			"-333"
		});
	}
	
	void SampleTestCase2(){
		Input({
			"4",
			"-1 1 -1 1"
		});
		
		Output({
			"4"
		});
	}
	
	void TestGroup1() {
		int r=rnd.nextInt(maxn/2)*2+2;
		CASE(n=r,arr=randomBounded(r));
		
		CASE(n=maxn,arr=randomBounded(maxn));
		CASE(n=maxn,arr=randomBounded(maxn,-100,100));
		CASE(n=maxn,arr=randomBounded(maxn,-1,1));
		
		CASE(n=maxn,arr=maxAns(maxn));
		
		CASE(n=maxn,arr=randomFromSet(maxn,{-INF}));
		CASE(n=maxn,arr=randomFromSet(maxn,{INF}));
		CASE(n=maxn,arr=randomFromSet(maxn,{-INF,INF}));
		CASE(n=maxn,arr=randomFromSet(maxn,{-INF,0,INF}));
		
		//n=2
		CASE(n=2,arr={-INF,INF});
		CASE(n=2,arr={INF,-INF});
		
		//idk in case they do nothing for n=4
		CASE(n=4,arr={-INF,INF,-INF,INF});
		CASE(n=4,arr={INF,-INF,INF,-INF});
	}
	
  private:
	vector<int> randomBounded(int n,int l=-INF,int r=INF){
		vector<int> res;
		for (int x=0;x<n;x++){
			res.push_back(rnd.nextInt(l,r));
		}
		return res;
	}
	
	vector<int> randomFromSet(int n,vector<int> val){
		vector<int> res;
		for (int x=0;x<n;x++){
			res.push_back(val[rnd.nextInt(val.size())]);
		}
		return res;
	}
	
	vector<int> maxAns(int n){
		vector<int> res;
		for (int x=0;x<n;x++){
			if (x%2==0) res.push_back(INF);
			else res.push_back(-INF);
		}
		
		vector<int> shift;
		int idx=rnd.nextInt(n);
		for (int x=0;x<n;x++){
			shift.push_back(res[(x+idx)%n]);
		}
		return shift;
	}
};
