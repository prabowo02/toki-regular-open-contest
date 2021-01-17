#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

const int MXN = 1000;
const int MXB = 29;
const int MXA = (1 << MXB) - 1;

class ProblemSpec : public BaseProblemSpec{
protected:
	int n, x;
	vector<int> v;

	int ans;

	void InputFormat(){
		LINE(n, x);
		LINE(v % SIZE(n));
	}
	void OutputFormat(){
		LINE(ans);
	}

	void GradingConfig(){
		TimeLimit(1);
		MemoryLimit(64);
	}

	void Constraints(){
		CONS(1 <= n && n <= MXN);
		CONS(1 <= x && x <= MXA);
		CONS(eachElementBetween(v, 1, MXA));
	}

	void Subtask1(){
		Points(100);
	}

private:
	bool eachElementBetween(vector<int> v, int lf, int rg){
		for(int i : v)
			if(!(lf <= i && i <= rg))
				return false;
		return true;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec>{
protected:
	void SampleTestCase1(){
		Subtasks({1});
		Input({
			"3 3",
			"1 2 1",
		});
		Output({
			"2",
		});
	}

	void SampleTestCase2(){
		Subtasks({1});
		Input({
			"10 420",
			"666 1209 526 236 8 69 603 123 35 1001",
		});
		Output({
			"519622136",
		});
	}

	void BeforeTestCase(){
		v.clear();
	}

	void TestGroup1(){
		Subtasks({1});
		
		CASE(n = 1, x = rnd.nextInt(1, MXA), v = vector<int>(1, x));
		CASE(n = 1, x = rnd.nextInt(2, MXA), v = vector<int>(1, rnd.nextInt(1, x - 1)));
		CASE(n = 1, x = rnd.nextInt(1, MXA - 1), v = vector<int>(1, rnd.nextInt(x + 1, MXA)));
		
		CASE(n = MXN, x = rnd.nextInt(1, MXA), v = pure_random(n));
		CASE(n = rnd.nextInt(1, MXN), x = rnd.nextInt(1, MXA), v = pure_random(n));
		CASE(n = rnd.nextInt(1, MXN), x = MXA, v = pure_random(n));

		CASE(n = MXN, x = rnd.nextInt(1, MXA), v = msb_random(n));
		CASE(n = rnd.nextInt(1, MXN), x = rnd.nextInt(1, MXA), v = msb_random(n));
		CASE(n = rnd.nextInt(1, MXN), x = MXA, v = msb_random(n));

		CASE(n = MXN, x = 1, v = all_same(n, x, 1));
		
		CASE(n = MXN, x = rnd.nextInt(1, MXA), v = all_same(n, x, 1));
		CASE(n = MXN, x = rnd.nextInt(1, MXA - 1), v = v = vector<int>(n, MXA));
		CASE(n = rnd.nextInt(1, MXN), x = MXA, v = all_same(n, x, 1));
		CASE(n = rnd.nextInt(1, MXN), x = MXA, v = all_same(n, x, 0));
		CASE(n = rnd.nextInt(1, MXN), x = rnd.nextInt(1, MXA), v = all_same(n, x, 0));
		CASE(n = rnd.nextInt(1, MXN), x = rnd.nextInt(1, MXA), v = vector<int>(n, MXA));

		CASE(n = MXN, x = rnd.nextInt(1, MXA), v = make_impossible(n, x));
		CASE(n = rnd.nextInt(1, MXN), x = rnd.nextInt(1, MXA), v = make_impossible(n, x));

		CASE(n = MXN, x = MXA, v = alternating(n));
		CASE(n = rnd.nextInt(1, MXN), x = rnd.nextInt(1, MXA), v = alternating(n));

		CASE(n = MXN, x = MXA, v = prefixOn(n));
		CASE(n = rnd.nextInt(1, MXN), x = rnd.nextInt(1, MXA), v = prefixOn(n));

		CASE(n = MXN, x = MXA, v = suffixOn(n));
		CASE(n = rnd.nextInt(1, MXN), x = rnd.nextInt(1, MXA), v = suffixOn(n));
	}

private:
	vector<int> pure_random(int n){
		vector<int> res;
		for(int i = 0; i < n; i ++)
			res.push_back(rnd.nextInt(1, MXA));

		return res;
	}

	vector<int> msb_random(int n){
		vector<int> msb(MXB + 1);
		for(int i = 0; i < n; i ++)
			msb[rnd.nextInt(1, MXB)] ++;

		vector<int> res;
		for(int i = 1; i <= MXB; i ++){
			for(int j = 0; j < msb[i]; j ++){
				res.push_back(rnd.nextInt((1 << (i - 1)), (1 << i) - 1));
			}
		}

		return res;
	}

	vector<int> all_same(int n, int x, bool same_with_x){
		vector<int> res;
		int get = rnd.nextInt(1, MXA);

		if(same_with_x){
			for(int i = 0; i < n; i ++)
				res.push_back(x);
		}else{
			for(int i = 0; i < n; i ++)
				res.push_back(get);
		}

		return res;
	}

	vector<int> make_impossible(int n, int x){
		int msb = 1;
		while((1 << msb) - 1 <= x) msb ++;
		msb -= 2;

		vector<int> res;
		if(msb <= 0){
			for(int i = 0; i < n; i ++)
				res.push_back(1);
		}else{
			for(int i = 0; i < n; i ++)
				res.push_back(rnd.nextInt(1, (1 << msb) - 1));
		}

		return res;
	}

	vector<int> alternating(int n){
		vector<int> res;
		for(int i = 0; i < n; i ++){
			int msb = rnd.nextInt(1, MXB);

			int cr = 0;
			for(int j = msb - 1; j >= 0; j --)
				cr = cr * 2 + (msb - j) % 2;

			res.push_back(cr);
		}

		return res;
	}

	vector<int> prefixOn(int n){
		vector<int> res;
		for(int i = 0; i < n; i ++){
			int msb = rnd.nextInt(1, MXB);
			int ones = rnd.nextInt(1, msb);

			int cr = 0;
			for(int j = 0; j < ones; j ++) cr = cr * 2 + 1;
			for(int j = ones; j < msb; j ++) cr *= 2;

			res.push_back(cr);
		}

		return res;
	}

	vector<int> suffixOn(int n){
		vector<int> res;
		for(int i = 0; i < n; i ++){
			int msb = rnd.nextInt(1, MXB);

			int cr = 0;
			for(int j = 0; j < msb; j ++) cr = cr * 2 + 1;

			res.push_back(cr);
		}

		return res;
	}
};
