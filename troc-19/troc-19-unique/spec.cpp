#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

const int MX = 500;

class ProblemSpec : public BaseProblemSpec{
protected:
	int n;
	vector<int> a;

	vector<int> ans;

	void InputFormat(){
		LINE(n);
		LINE(a % SIZE(n));
	}
	void OutputFormat(){
		
	}

	void GradingConfig(){
		TimeLimit(1);
		MemoryLimit(64);
	}

	void StyleConfig(){
		InteractiveEvaluator();
	}

	void Constraints(){
		CONS(2 <= n && n <= MX);
		CONS(eachElementBetween(a, 1, MX));
	}

	void Subtask1(){
		Points(100);
	}

private:
	bool eachElementBetween(vector<int> v, int lf, int rg){
		for(int i : v)
			if(i < lf || i > rg) return 0;
		return 1;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec>{
protected:
	void SampleTestCase1(){
		Subtasks({1});
		Input({
			"6",
			"1 3 2 2 1 4",
		});
	}

	void TestGroup1(){
		Subtasks({1});

		// all unique
		CASE(n = 2, a = {6, 9});
		CASE(n = 4, a = {1, 2, 7, 3});
		CASE(n = MX, a = allUnique(n));
		CASE(n = rnd.nextInt(2, MX), a = allUnique(n));;

		// all equal
		CASE(n = 3, a = {6, 6, 6});
		CASE(n = MX, a = allEqual(n));
		CASE(n = rnd.nextInt(2, MX), a = allEqual(n));

		// all element frequency >1
		CASE(n = 6, a = {1, 2, 3, 1, 2, 3});
		CASE(n = MX, a = noUnique(n, n / 2));
		CASE(n = MX, a = noUnique(n, n / 7));
		CASE(n = MX, a = noUnique(n, 2));
		CASE(n = MX, a = noUnique(n));
		CASE(n = rnd.nextInt(2, MX), a = noUnique(n, 2));
		CASE(n = rnd.nextInt(2, MX), a = noUnique(n));

		// random
		CASE(n = MX, a = pureRandom(n));
		CASE(n = rnd.nextInt(2, MX), a = pureRandom(n));

		// control number of unique elements
		CASE(n = MX, a = dup(n, 10));
		CASE(n = MX, a = dup(n, rnd.nextInt(1, MX / 20)));
		CASE(n = MX, a = dup(n, rnd.nextInt(1, MX / 5)));
		CASE(n = MX, a = dup(n));
		CASE(n = rnd.nextInt(2, MX), a = dup(n));

		// special testcases
		CASE(n = MX, a = pyqe1(n, 0));
		CASE(n = MX, a = pyqe1(n, 1));
		CASE(n = MX, a = pyqe1(n, 2));
		CASE(n = rnd.nextInt(1, MX / 2) * 2, a = pyqe1(n, 0));
		CASE(n = MX, a = pyqe2(0));
		CASE(n = MX, a = pyqe2(1));
	}

private:
	vector<int> allUnique(int sz){
		vector<int> v(MX);
		iota(v.begin(), v.end(), 1);
		rnd.shuffle(v.begin(), v.end());

		vector<int> rs;
		for(int i = 0; i < sz; i ++) rs.push_back(v[i]);
		return rs;
	}

	vector<int> allEqual(int sz){
		int get = rnd.nextInt(1, MX);
		vector<int> rs;
		for(int i = 0; i < sz; i ++) rs.push_back(get);
		return rs;
	}

	vector<int> noUnique(int sz, int maxFreq = -1){
		if(maxFreq == -1) maxFreq = rnd.nextInt(2, sz);
		vector<int> freq;
		int cr = sz;
		for(; cr > 0;){
			if(cr == 1){
				freq[freq.size() - 1] ++;
				break;
			}
			int nw = rnd.nextInt(2, min(cr, maxFreq));
			freq.push_back(nw);
			cr -= nw;
		}

		vector<int> v(MX);
		iota(v.begin(), v.end(), 1);
		rnd.shuffle(v.begin(), v.end());

		vector<int> rs;
		for(int i = 0; i < freq.size(); i ++)
			for(int j = 0; j < freq[i]; j ++)
				rs.push_back(v[i]);
		rnd.shuffle(rs.begin(), rs.end());
		return rs;
	}

	vector<int> pureRandom(int sz){
		vector<int> rs;
		for(int i = 0; i < sz; i ++)
			rs.push_back(rnd.nextInt(1, MX));
		return rs;
	}

	vector<int> dup(int sz, int cnt = -1){
		if(cnt == -1) cnt = rnd.nextInt(0, sz - 1);
		vector<int> v(MX);
		iota(v.begin(), v.end(), 1);
		rnd.shuffle(v.begin(), v.end());

		vector<int> rs;
		for(int i = 0; i < sz - cnt; i ++) rs.push_back(v[i]);
		for(int j = 0; j < cnt; j ++) rs.push_back(v[rnd.nextInt(0, sz - cnt - 1)]);
		return rs;
	}

	vector<int> pyqe1(int sz, int type){
		vector<int> v(MX);
		iota(v.begin(), v.end(), 1);
		rnd.shuffle(v.begin(), v.end());

		vector<int> a;
		for(int i = 0; i < sz / 2; i ++) a.push_back(v[i]);
		
		vector<int> rs;
		for(int tp = 0; tp < 2; tp ++){
			if(type == 0) rnd.shuffle(a.begin(), a.end());
			else if(type == 1) sort(a.begin(), a.end());
			else if(type == 2){
				if(tp == 0) sort(a.rbegin(), a.rend());
				else sort(a.begin(), a.end());
			}
			for(int i = 0; i < a.size(); i ++)
				rs.push_back(a[i]);
		}
		return rs;
	}

	vector<int> pyqe2(bool big){
		vector<int> v(MX);
		iota(v.begin(), v.end(), 1);
		rnd.shuffle(v.begin(), v.end());

		vector<int> a, b;
		for(int i = 0; i < 4 * MX / 5; i ++) a.push_back(v[i]);
		for(int i = 0; i < MX - static_cast<int>(a.size()); i ++) b.push_back(v[i]);
		rnd.shuffle(a.begin(), a.end());
		rnd.shuffle(b.begin(), b.end());

		vector<int> rs;
		if(big){
			for(int i : a) rs.push_back(i);
			for(int i : b) rs.push_back(i);
		}else{
			for(int i : b) rs.push_back(i);
			for(int i : a) rs.push_back(i);
		}

		return rs;
	}
};
