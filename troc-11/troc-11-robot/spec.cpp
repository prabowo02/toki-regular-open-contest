/* Author: maximath_1 */
#include <tcframe/spec.hpp>

using namespace tcframe;

const int maxs=100;
class ProblemSpec : public BaseProblemSpec{
protected:
	string s;
	
	int x, y;

	void InputFormat(){
		LINE(s);
	}
	void OutputFormat(){
		LINE(x, y);
	}

	void GradingConfig(){
		TimeLimit(1);
		MemoryLimit(64);
	}

	void Constraints(){
		CONS(1<=s.size() && s.size()<=100);
		CONS(all_of(s.begin(), s.end(), isupper));
	}

	void Subtask1(){
		Points(100);
	}
};
class TestSpec : public BaseTestSpec<ProblemSpec>{
protected:
	void SampleTestCase1(){
		Subtasks({1});
		Input({"RUDDLDUR"});
		Output({"1 -1"});
	}
	void SampleTestCase2(){
		Subtasks({1});
		Input({"ABRUMNURYZ"});
		Output({"2 2"});
	}
	void BeforeTestCase(){
		s.clear();
	}
	void TestGroup1(){
		Subtasks({1});

		CASE(s="DEBRET");
		CASE(s="KANTIPA");
		CASE(s="NEVEST");
		CASE(s="MARA");
		CASE(s="IVO");
		CASE(s="BLAIN");
		CASE(s="XIMA");
		CASE(s="PRABOWO");
		CASE(s="HOCKY");

		CASE(s="UPDOWNLEFTRIGHTFRONTBACK");
		CASE(s="TOKIREGULAROPENCONTESTNUMBERELEVEN");
		CASE(s="THEONEWHOISMAKINGTHETESTCASESFORTHISPROBLEMISHELLAGAY");
		CASE(s="UWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUWUW");
		CASE(s="LOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLO");
        
		CASE(randomAllRLUD(maxs));
		CASE(circle(maxs));
		CASE(diagonal(maxs));
		CASE(maxRLUD(maxs));
	}
private:
	void randomAllRLUD(int N){
		for(int i=0; i<N; i++){
			int nw=rnd.nextInt(1, 4);
			if(nw==1) s+='R';
			if(nw==2) s+='L';
			if(nw==3) s+='U';
			if(nw==4) s+='D';
		}
	}
	void circle(int N){
		for(int i=0; i<N; i++){
			if(i%4==0) s+='R';
			if(i%4==1) s+='D';
			if(i%4==2) s+='L';
			if(i%4==3) s+='U';
		}
	}
	void diagonal(int N){
		string use="RDLU";
		int nw=rnd.nextInt(0, 3);
		for(int i=0; i<N; i++){
			if(i%2==0) s+=use[nw];
			else s+=use[(nw+1)%4];
		}
	}
	void maxRLUD(int N){
		string use="RDLU";
		int nw=rnd.nextInt(0, 3);
		for(int i=0; i<N; i++) s+=use[nw];
	}
};
