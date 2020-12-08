#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

template<typename data>
bool eachElementBetween(const vector<data> &V,data mins,data maks) {
	for (data x : V) {
		if (x<mins||x>maks) {
			return 0;
		}
	}
	
	return 1;
}

class ProblemSpec : public BaseProblemSpec {
protected:
	int N, M;
	vector <int> A, B;
	
	void InputFormat() {
		LINE(N);
		LINE(A%SIZE(N));
	}
	
	void OutputFormat() {
		LINE(M);
		LINE(B%SIZE(M));
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
    }
	
	void Constraints() {
		CONS(1<=N&&N<=100000);
		CONS(eachElementBetween(A,1,1000000));
    }

  void StyleConfig() {
  	CustomScorer();
  }
	
	void Subtask1() {
		Points(100);
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Subtasks({1});
		Input({
			"4",
			"3 1 2 3"
		});
		Output({
			"3",
			"3 2 3"
		});
	}
	
	void SampleTestCase2() {
		Subtasks({1});
		Input({
			"5",
			"2 2 2 2 2"
		});
		Output({
			"1",
			"2"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		CASE(N=1,A=randomBetween(N,1,1000000));
		CASE(N=2,A=randomBetween(N,1,1000000));
		CASE(N=2,fillAll(N,rnd.nextInt(1,1000000)));
		
		CASE(N=68030,A=fillAll(N,rnd.nextInt(1,1000000)));
		CASE(N=100000,A=fillAll(N,rnd.nextInt(1,1000000)));
		
		CASE(N=70477,A=randomBetween(N,1,1000000),sort(A.begin(),A.end()),reverse(A.begin(),A.end()));
		CASE(N=100000,A=randomBetween(N,1,1000000),sort(A.begin(),A.end()),reverse(A.begin(),A.end()));
		
		CASE(N=81029,A=randomBetween(N,1,1000000),sort(A.begin(),A.end()));
		CASE(N=100000,A=randomBetween(N,1,1000000),sort(A.begin(),A.end()));
		
		CASE(N=94637,A=randomBetween(N,1,1000000));
		CASE(N=100000,A=randomBetween(N,1,1000000));
		
		for (int i=1;i<=5;i++) {
			CASE(N=rnd.nextInt(1,100000),A=randomBetween(N,1,1000000));
		}
		for(int i = 0; i < 5; i++)
			CASE(N = rnd.nextInt(50000, 100000),A = zigZagCase(N, 1, 1000000));
	}

	vector<int> zigZagCase(int n, int l, int r){
		vector<int> ret(n);
		if(rnd.nextInt(0, 1) == 0){
			ret[0] = rnd.nextInt(l, r - 1);
			ret[1] = rnd.nextInt(ret[0] + 1, r);
		}
		else{
			ret[0] = rnd.nextInt(l + 1, r);
			ret[1] = rnd.nextInt(l, ret[0] - 1);
		}
		for(int i = 2; i < n; i++){
			if(ret[i - 1] > ret[i - 2]){
				ret[i] = rnd.nextInt(l, ret[i - 1] - 1);
			}
			else{
				ret[i] = rnd.nextInt(ret[i - 1] + 1, r);
			}
		}
		return ret;
	}
	
	vector <int> fillAll(int size,int val) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			ret.push_back(val);
		}
		
		return ret;
	}
	
	vector <int> randomBetween(int size,int mins,int maks) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			ret.push_back(rnd.nextInt(mins,maks));
		}
		
		return ret;
	}
};
