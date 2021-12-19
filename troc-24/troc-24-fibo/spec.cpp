#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
 protected:
  string s;
 
  void InputFormat() {
	LINE(s);
  }
  
  void GradingConfig() {
    TimeLimit(10);
    MemoryLimit(256);
  }
  void Constraints() {
  }
  void StyleConfig() {
    InteractiveEvaluator();
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
	void SampleTestCase1(){
		Input({
			"sample"
		});
	}
	
	void TestGroup1() {
		CASE(s="full");
	}
};
