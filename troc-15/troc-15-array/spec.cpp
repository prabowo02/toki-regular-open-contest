#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

const int MX = 100;

class ProblemSpec : public BaseProblemSpec{
protected:
	int N;
	vector<int> A;

	string ans;

	void InputFormat(){
		LINE(N);
		LINE(A % SIZE(N));
	}
	void OutputFormat(){
		LINE(ans);
	}

	void GradingConfig(){
		TimeLimit(1);
		MemoryLimit(64);
	}

	void Constraints(){
		CONS(1 <= N && N <= MX);
		CONS(eachElementBetween(A, 1, MX));
	}

	void Subtask1(){
		Points(100);
	}

private:
	bool eachElementBetween(vector<int> arr, int lf, int rg){
		for(int i : arr)
			if(i < lf || i > rg) return 0;
		return 1;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec>{
protected:
	void SampleTestCase1(){
		Subtasks({1});
		Input({
			"5",
			"2 2 2 2 2",
		});
		Output({
			"EQUAL",
		});
	}
	void SampleTestCase2(){
		Subtasks({1});
		Input({
			"4",
			"1 5 5 6",
		});
		Output({
			"NONDECREASING",
		});
	}
	void SampleTestCase3(){
		Subtasks({1});
		Input({
			"3",
			"3 2 1",
		});
		Output({
			"NONINCREASING",
		});
	}
	void SampleTestCase4(){
		Subtasks({1});
		Input({
			"5",
			"1 2 3 2 1",
		});
		Output({
			"NONE",
		});
	}

	void BeforeTestCase(){
		A.clear();
	}

	void TestGroup1(){
		Subtasks({1});

		CASE(N = 1, A = {1};);
		
		CASE(N = MX, A = genNonDec(MX););
		CASE(N = MX, A = genEq(MX, MX););
		CASE(N = MX, A = genNonInc(MX););
		CASE(N = MX, A = genZigZag(MX););
		CASE(N = MX, A = genRand(MX););

		CASE(N = rnd.nextInt(1, MX), A = genZigZag(N););
		CASE(N = rnd.nextInt(1, MX), A = genNonInc(N););
		CASE(N = rnd.nextInt(1, MX), A = genRand(N););
		CASE(N = rnd.nextInt(1, MX), A = genEq(N););
		CASE(N = rnd.nextInt(1, MX), A = genNonDec(N););

		CASE(N = 69, A = genEq(69, 69));
	}

private:
	vector<int> genEq(int n, int v = -1){
		vector<int> rs;
		int val = rnd.nextInt(1, MX);
		if(v != -1) val = v;
		for(int i = 0; i < n; i ++){
			rs.push_back(val);
		}
		return rs;
	}

	vector<int> genNonInc(int n){
		vector<int> rs;
		int last = MX;
		for(int i = 0; i < n; i ++){
			rs.push_back(rnd.nextInt(1, last));
			last = rs.back();
		}
		return rs;
	}

	vector<int> genNonDec(int n){
		vector<int> rs;
		int last = 1;
		for(int i = 0; i < n; i ++){
			rs.push_back(rnd.nextInt(last, MX));
			last = rs.back();
		}
		return rs;
	}

	vector<int> genZigZag(int n){
		vector<int> rs;
		int last = MX;
		for(int i = 0; i < n; i ++){
			if(i & 1) rs.push_back(rnd.nextInt(last, MX));
			else rs.push_back(rnd.nextInt(1, last));
			last = rs.back();
		}
		return rs;
	}

	vector<int> genRand(int n){
		vector<int> rs;
		for(int i = 0; i < n; i ++)
			rs.push_back(rnd.nextInt(1, MX));
		return rs;
	}
};
