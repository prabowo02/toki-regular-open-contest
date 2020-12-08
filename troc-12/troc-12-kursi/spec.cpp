#include <tcframe/spec.hpp>
using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
	int T;
	vector <int> X, Y;
	vector <int> ans;
	void InputFormat() {
		LINE(T);
		LINES(X, Y) % SIZE(T);
	}

	void OutputFormat() {
		LINES(ans) % SIZE(T);
	}

	void GradingConfig() {
		TimeLimit(3);
		MemoryLimit(64);
	}

	void Constraints() {
		CONS(1 <= T && T <= 100000);
		CONS(eachElementBetween(X, 0, 1000000000));
		CONS(eachElementBetween(Y, 0, 1000000000));
	}

	void Subtask1() {
		Points(100);
	}
private:
	bool eachElementBetween(const vector<int>& X, int lo, int hi) {
		for (int x : X) {
			if (x < lo || x > hi) {
				return false;
			}
		}
		return true;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Subtasks({1});
		Input({
			"2",
			"1 1",
			"3 5"
		});
		Output({
			"4",
			"8"
		});
	}
	
	void AfterTestCase() {
		T=X.size();
	}
	void BeforeTestCase() {
		X.clear();
		Y.clear();
	}
	void TestGroup1() {
		Subtasks({1});
		//random
		{
			vector <int> x, y;
			for(int i = 0;i < 100000;i ++) {
				x.push_back(rnd.nextInt(1000000001));
				y.push_back(rnd.nextInt(1000000001));
			}
			CASE(X=x, Y=y);
		}
		//strategic
		CASE(strategic());
		//always manhattan+2
		{
			vector <int> x, y;
			//this loop runs about 12*100000 times
			while(x.size()<100000) {
				int testx, testy;
				testx=rnd.nextInt(1000000001);
				testy=rnd.nextInt(1000000001);
				if(testx+testy<solve(testx, testy)) {
					x.push_back(testx);
					y.push_back(testy);
				}
			}
			CASE(X=x, Y=y);
		}
	}

private:
	inline int solve(int x, int y) {
        if(x>y)
            swap(x, y);
        if(x==0)
            return x+y;
        if(x==y)
            return x+y+2;
        if(y-x&3)
            return x+y;
        int k=(x-y)&(y-x);
        if(x%k<k/2&&x%k)
            return x+y+2;
        else
            return x+y;
	}
	void strategic() {
		for(int i = 0;i <= 100;i ++)for(int j = 0;j <= 100;j ++) {
			//small-small
			X.push_back(i);
			Y.push_back(j);
			//large-large
			X.push_back(1000000000-100+i);
			Y.push_back(1000000000-100+j);
			X.push_back(536870912-50+i);
			Y.push_back(536870912-50+j);
			//small-large
			X.push_back(i);
			Y.push_back(1000000000-100+j);
			X.push_back(1000000000-100+i);
			Y.push_back(j);
			X.push_back(i);
			Y.push_back(536870912-50+j);
			X.push_back(536870912-50+i);
			Y.push_back(j);
		}
		for(int i = 0;i < 3177;i ++) {
			//small-random
			X.push_back(rnd.nextInt(5));
			Y.push_back(rnd.nextInt(1000000001));
			X.push_back(rnd.nextInt(1000000001));
			Y.push_back(rnd.nextInt(5));
			//large-random
			X.push_back(1000000000-rnd.nextInt(10));
			Y.push_back(rnd.nextInt(1000000001));
			X.push_back(rnd.nextInt(1000000001));
			Y.push_back(1000000000-rnd.nextInt(10));
			X.push_back(536870912-rnd.nextInt(10));
			Y.push_back(rnd.nextInt(1000000001));
			X.push_back(rnd.nextInt(1000000001));
			Y.push_back(536870912-rnd.nextInt(10));
			//close to diagonals
			int k;
			k=rnd.nextInt(999999992);
			X.push_back(k+rnd.nextInt(10));
			Y.push_back(k+rnd.nextInt(10));
			k=rnd.nextInt(536870908);
			X.push_back(536870907-k+rnd.nextInt(10));
			Y.push_back(k+rnd.nextInt(10));
			k=rnd.nextInt(999999992);
			X.push_back(999999991-k+rnd.nextInt(10));
			Y.push_back(k+rnd.nextInt(10));
		}
	}
};
