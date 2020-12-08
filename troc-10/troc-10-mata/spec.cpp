#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
	string S, T;
	string ans;

	void InputFormat() {
		LINE(S);
		LINE(T);
	}

	void OutputFormat() {
		LINE(ans);
	}

	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
	}

	void Constraints() {
		CONS(1 <= S.size() && S.size() <= 100);
		CONS(S.size() == T.size());
		CONS(all_of(S.begin(), S.end(), isalpha));
		CONS(all_of(T.begin(), T.end(), isalpha));
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
			"Prabowo",
			"patriCK"
		});
		Output({
			"x_x"
		});
	}

	void SampleTestCase2() {
		Subtasks({1});
		Input({
			"hOCkY",
			"HOcKY"
		});
		Output({
			"20/20"
		});
	}

	void TestGroup1() {
		Subtasks({1});
		CASE(S = "A", T = "a");
		CASE(S = "b", T = "a");
		CASE(S = "z", T = "Z");
		CASE(S = "z", T = "y");
		for(int j = 10;j --;){
			string randS, randT;
			for(int i = 0;i < 100;i ++){
				randS.push_back(rnd.nextInt(26)+'A'+(rnd.nextInt(2)?32:0));
				randT.push_back(randS.back()^(rnd.nextInt(2)?32:0));
			}
			CASE(S = randS, T = randT);
			int ind=rnd.nextInt(100);
			randS[ind] = ((randS[ind]&31)+rnd.nextInt(25))%26+'A'+(rnd.nextInt(2)?32:0);
			CASE(S = randS, T = randT);
		}
	}
};