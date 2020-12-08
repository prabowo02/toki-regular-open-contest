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
	int T, MA, MB;
	vector <int> X, Y, A, B;
	vector <int> P, Q;
	vector <string> ans;
	
	void InputFormat() {
		LINE(T,MA,MB);
		LINES(X,Y,A,B)%SIZE(T);
	}
	
	void OutputFormat() {
		LINES(ans)%SIZE(T);
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
    }
	
	void Constraints() {
		CONS(1<=T&&T<=100000);
		CONS(1<=MA&&1<=MB&&MA*MB<=100000);
		CONS(eachElementBetween(X,1,1000000));
		CONS(eachElementBetween(Y,1,1000000));
		CONS(eachElementBetween(A,1,MA));
		CONS(eachElementBetween(B,1,MB));
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
			"4 2 4",
			"5 7 2 3",
			"5 8 2 3",
			"4 5 1 4",
			"4 6 1 4"
		});
		Output({
			"AMNU",
			"YOGA",
			"SALMAN",
			"SALMAN"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		for (int i=1;i<=10;i++) {
			CASE(T=100000,MA=10,MB=10,A=fillAll(T,i),B=fillPeriod(1,10,10000),X=fillPeriod(10,100,100),Y=fillPeriod(1000,100,1));
		}
		
		for (int i=1;i<=3;i++) {
			CASE(T=rnd.nextInt(90000,100000),MA=10,MB=10,A=randomBetween(T,1,MA),B=randomBetween(T,1,MB),P=randomBetween(T,1,100),Q=randomBetween(T,1,100),X=transformX(T,P,Q),Y=transformY(T,P,Q));
		}
		
		for (int i=1;i<=3;i++) {
			CASE(T=rnd.nextInt(90000,100000),MA=300,MB=300,A=randomBetween(T,1,MA),B=randomBetween(T,1,MB),Y=randomBetween(T,1,1000000),X=fillAlmost(T,Y));
		}
		
		CASE(T=rnd.nextInt(1,100000),MA=1,MB=100000,A=randomBetween(T,1,MA),B=randomBetween(T,1,MB),X=randomBetween(T,1,1000000),Y=randomBetween(T,1,1000000));
		CASE(T=rnd.nextInt(1,100000),MA=100000,MB=1,A=randomBetween(T,1,MA),B=randomBetween(T,1,MB),X=randomBetween(T,1,1000000),Y=randomBetween(T,1,1000000));
		
		CASE(T=92793,MA=100,MB=100,A=randomBetween(T,1,MA),B=randomBetween(T,1,MB),X=randomBetween(T,1,10000),Y=randomBetween(T,1,10000));
		CASE(T=71920,MA=300,MB=300,A=randomBetween(T,1,MA),B=randomBetween(T,1,MB),X=randomBetween(T,1,100000),Y=randomBetween(T,1,100000));
		CASE(T=81923,MA=rnd.nextInt(10,316),MB=100000/MA,A=randomBetween(T,1,MA),B=randomBetween(T,1,MB),X=randomBetween(T,1,1000000),Y=randomBetween(T,1,1000000));
		CASE(T=100000,MB=rnd.nextInt(10,316),MA=100000/MB,A=randomBetween(T,1,MA),B=randomBetween(T,1,MB),X=randomBetween(T,1,1000000),Y=randomBetween(T,1,1000000));
	}
	
	vector <int> reverseAB(vector <int> ref,int C) {
		vector <int> ret;
		ret.clear();
		
		for (int x : ref) {
			ret.push_back(rnd.nextInt(1,C/x));
		}
		
		return ret;
	}
	
	vector <int> transformX(int size,vector <int> p,vector <int> q) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			int x, y;
			x=p[i];
			y=q[i];
			
			while (x+2*y<=1000000) {
				x+=y;
				y+=x;
			}
			
			ret.push_back(x);
		}
		
		return ret;
	}
	
	vector <int> transformY(int size,vector <int> p,vector <int> q) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			int x, y;
			x=p[i];
			y=q[i];
			
			while (x+2*y<=1000000) {
				x+=y;
				y+=x;
			}
			
			ret.push_back(y);
		}
		
		return ret;
	}
	
	vector <int> fillAlmost(int size,vector <int> ref) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			int save;
			save=round(0.618*ref[i])+rnd.nextInt(-30000,30000);
			save=max(1,save);
			
			ret.push_back(save);
		}
		
		return ret;
	}
	
	vector <int> fillPeriod(int ulang,int sampai,int panjang) {
		vector <int> ret;
		ret.clear();
		
		for (int i=1;i<=ulang;i++) {
			for (int j=1;j<=sampai;j++) {
				for (int k=1;k<=panjang;k++) {
					ret.push_back(j);
				}
			}
		}
		
		return ret;
	}
	
	vector <int> fillAll(int size,int fill) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<size;i++) {
			ret.push_back(fill);
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
