#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

const int MX = 1000000;

vector<int> V = {0, 1, 9, 20, 4, 18, 33, 16, 31, 9, 29, 11, 27, 46, 25, 44, 16, 42, 18, 40, 20, 38, 22, 36, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 49, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49};
vector<int> noes = {2, 3, 5, 6, 7, 8, 10, 12, 13, 14, 15, 17, 19, 21, 23, 34};

class ProblemSpec : public BaseProblemSpec{
protected:
	int N, M;

	string ans;
	string moves;

	void InputFormat(){
		LINE(N, M);
	}
	void OutputFormat1(){
		LINE(ans);
	}
	void OutputFormat2(){
		LINE(ans);
		LINE(moves);
	}

	void StyleConfig() {
		CustomScorer();
	}

	void GradingConfig(){
		TimeLimit(1);
		MemoryLimit(64);
	}

	void Constraints(){
		CONS(1 <= M && M <= N && N <= MX);
	}

	void Subtask1(){
		Points(100);
	}

private:

};

class TestSpec : public BaseTestSpec<ProblemSpec>{
protected:
	void SampleTestCase1(){
		Subtasks({1});
		Input({
			"14 11",
		});
		Output({
			"YES",
			"RRRLR",
		});
	}
	void SampleTestCase2(){
		Subtasks({1});
		Input({
			"14 5",
		});
		Output({
			"NO",
		});
	}

	void BeforeTestCase(){
	}

	void TestGroup1(){
		Subtasks({1});

		//Big Testcases (ALL YES)
		CASE({N = MX, M = MX;});
		for(int i = 0; i < 4; i ++)
			CASE({N = rnd.nextInt(49, MX), M = rnd.nextInt(1, N);});

		//Small testcases
		CASE(no(););
		CASE(no(););
		CASE(yes(););
		CASE(no(););
		CASE(yes(););
		CASE(no(););
		CASE(no(););
		CASE(yes(););
		CASE({N = 1, M = 1;});
		
		// N large, M small
		CASE({N = MX, M = 2;});
		CASE({N = rnd.nextInt(1001, MX), M = rnd.nextInt(1, 49);});
		CASE({N = rnd.nextInt(1001, MX), M = rnd.nextInt(50, 100);});
		
		// N, M medium
		CASE({N = rnd.nextInt(49, 1000), M = rnd.nextInt(1, N);});
		CASE({N = rnd.nextInt(49, 1000), M = rnd.nextInt(1, N);});
	}

private:
	void no(){
		int id = rnd.nextInt(0, (int)noes.size() - 1);
		M = noes[id];
		N = rnd.nextInt(M, V[M] - 1);
	}
	void yes(){
		M = rnd.nextInt(1, 49);
		N = rnd.nextInt(V[M], 49);
	}
};
