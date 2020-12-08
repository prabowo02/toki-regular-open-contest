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

bool validQuery(const vector<vector<int> > &V) {
	bool B;
	int sum;
	sum=0;
	
	for (vector <int> x : V) {
		if (x.empty()) {
			return 0;
		}
		
		if (x.size()!=x[0]+1||x[0]<2) {
			return 0;
		}
		
		B=1;
		sum+=x[0];
		
		for (int y : x) {
			if (B) {
				B=0;
				continue;
			}
			
			if (y<0||y>1023) {
				return 0;
			}
		}
	}
	
	if (sum>40000) {
		return 0;
	}
	
	return 1;
}

class ProblemSpec : public BaseProblemSpec {
protected:
	int N, Q;
	vector <vector <int> > V;
	vector <int> A, ans;
	
	void InputFormat() {
		LINE(N,Q);
		LINE(A%SIZE(N));
		LINES(V)%SIZE(Q);
	}
	
	void OutputFormat() {
		LINES(ans)%SIZE(Q+1);
	}
	
	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(64);
    }
	
	void Constraints() {
		CONS(2<=N&&N<=40000);
		CONS(1<=Q&&Q<=20000);
		CONS(eachElementBetween(A,0,1023));
		CONS(validQuery(V));
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
			"7 4",
			"1 0 3 1 2 0 1",
			"3 2 1 3",
			"2 3 2",
			"3 0 2 1",
			"2 2 2"
		});
		Output({
			"1",
			"2",
			"1",
			"0",
			"3"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		CASE(N=2,Q=1,A={28,41},V={{2,37,75}});
		CASE(N=2,Q=1,A={32,64},V={{2,64,32}});
		CASE(N=2,Q=1,A={0,0},V={{2,0,0}});
		CASE(N=4,Q=1,A={0,0,0,0},V={{2,0,0}});
		CASE(N=12,Q=2,A={0,0,1,1,3,3,1,1,3,3,2,2},V={{4,0,0,1,1},{4,0,0,2,2}});
		
		CASE(N=2,Q=1024,A={0,0},V=typeA());
		CASE(N=40000,Q=1,A=randomBetween(N,0,1023),V=typeB(A));
		CASE(N=40000,Q=1,A=randomBetween(N,0,1023),V=typeB(randomBetween(N,0,1023)));
		CASE(N=40000,Q=20000,A=randomBetween(N,0,1023),V=typeC());
		CASE(N=40000,Q=281,A=randomBetween(N,0,1023),V=typeD(A));
		CASE(N=40000,A=period(1,39999,0),V=typeD(A),Q=V.size());
		
		CASE(N=40000,A=period(201,199,58),V=typeE(A),Q=V.size());
		CASE(N=40000,A=period(3,13333,101),V=typeE(A),Q=V.size());
		CASE(N=40000,A=period(597,67,14),V=typeE(A),Q=V.size());
		CASE(N=40000,A=period(1,39999,0),V=typeF(A),Q=V.size());
		CASE(N=40000,A=period(13333,3,0),V=typeG(A),Q=V.size());
		CASE(N=40000,A=period(67,597,203),V=typeH(A),Q=V.size());
		CASE(N=40000,A=period(1,39999,3),V=typeI(A),Q=V.size());
		CASE(N=40000,A=period(67,597,34),V=typeJ(A),Q=V.size());
		CASE(N=40000,A=period(1,39999,0),V=typeJ(A),Q=V.size());
	}
	
	vector <vector<int> > typeA() {
		vector <vector<int> > ret;
		ret.clear();
		
		for (int i=0;i<1024;i++) {
			ret.push_back({2,0,i});
		}
		
		return ret;
	}
	
	vector <vector<int> > typeB(vector <int> x) {
		vector <vector<int> > ret;
		ret.clear();
		
		int dif;
		dif=rnd.nextInt(1,1023);
		ret.push_back({(int) x.size()});
		
		for (int y : x) {
			ret[0].push_back(y^dif);
		}
		
		return ret;
	}
	
	vector <vector<int> > typeC() {
		vector <vector<int> > ret;
		ret.clear();
		
		for (int i=0;i<20000;i++) {
			ret.push_back({2,rnd.nextInt(0,1023),rnd.nextInt(0,1023)});
		}
		
		return ret;
	}
	
	vector <vector<int> > typeD(vector <int> x) {
		vector <vector<int> > ret;
		ret.clear();
		
		int now, pos;
		
		for (int i=0;i<281;i++) {
			now=i+2;
			pos=rnd.nextInt(0,40000-now);
			ret.push_back({now,rnd.nextInt(0,1023)});
			
			for (int j=1;j<now;j++) {
				ret[i].push_back(ret[i][j]^x[pos+j-1]^x[pos+j]);
			}
		}
		
		return ret;
	}
	
	vector <vector<int> > typeE(vector <int> x) {
		vector <vector<int> > ret;
		ret.clear();
		
		int left, now, pos;
		left=40000;
		
		for (int i=0;left>1;i++) {
			now=min(left,rnd.nextInt(2,rnd.nextInt(2,1000)));
			pos=rnd.nextInt(0,40000-now);
			left-=now;
			ret.push_back({now,rnd.nextInt(0,1023)});
			
			for (int j=1;j<now;j++) {
				ret[i].push_back(ret[i][j]^x[pos+j-1]^x[pos+j]);
			}
		}
		
		return ret;
	}
	
	vector <vector<int> > typeF(vector <int> x) {
		vector <vector<int> > ret;
		ret.clear();
		
		int now, pos;
		
		for (int i=0;i<20000;i++) {
			now=2;
			pos=0;
			ret.push_back({now,rnd.nextInt(0,1023)});
			
			for (int j=1;j<now;j++) {
				ret[i].push_back(ret[i][j]^x[pos+j-1]^x[pos+j]);
			}
		}
		
		return ret;
	}
	
	vector <vector<int> > typeG(vector <int> x) {
		vector <vector<int> > ret;
		ret.clear();
		
		int now, pos;
		
		for (int i=0;i<=10000;i++) {
			if (i) {
				now=2;
				pos=rnd.nextInt(0,40000-now);
			}
			else {
				now=20000;
				pos=5;
			}
			
			ret.push_back({now,rnd.nextInt(0,1023)});
			
			for (int j=1;j<now;j++) {
				ret[i].push_back(ret[i][j]^x[pos+j-1]^x[pos+j]);
			}
		}
		
		return ret;
	}
	
	vector <vector<int> > typeH(vector <int> x) {
		vector <vector<int> > ret;
		ret.clear();
		
		int now, pos;
		
		for (int i=0;i<13333;i++) {
			if (i) {
				now=3;
				pos=rnd.nextInt(0,40000-now);
			}
			else {
				now=4;
				pos=rnd.nextInt(0,40000-now);
			}
			
			ret.push_back({now,rnd.nextInt(0,1023)});
			
			for (int j=1;j<now;j++) {
				ret[i].push_back(ret[i][j]^x[pos+j-1]^x[pos+j]);
			}
		}
		
		return ret;
	}
	
	vector <vector<int> > typeI(vector <int> x) {
		vector <vector<int> > ret;
		ret.clear();
		
		int now, pos;
		
		for (int i=0;i<19999;i++) {
			if (i) {
				now=2;
				pos=0;
			}
			else {
				now=4;
				pos=0;
			}
			
			ret.push_back({now,rnd.nextInt(0,1023)});
			
			for (int j=1;j<now;j++) {
				ret[i].push_back(ret[i][j]^x[pos+j-1]^x[pos+j]);
			}
		}
		
		return ret;
	}
	
	vector <vector<int> > typeJ(vector <int> x) {
		vector <vector<int> > ret;
		ret.clear();
		
		int now, pos;
		
		for (int i=0;i<5000;i++) {
			now=8;
			pos=rnd.nextInt(0,40000-now);
			ret.push_back({now,rnd.nextInt(0,1023)});
			
			for (int j=1;j<now;j++) {
				ret[i].push_back(ret[i][j]^x[pos+j-1]^x[pos+j]);
			}
		}
		
		return ret;
	}

	vector <int> period(int size,int rep,int dif) {
		vector <int> ret;
		ret.clear();
		
		for (int i=0;i<=size;i++) {
			ret.push_back(rnd.nextInt(0,1023));
		}
		
		for (int i=1;i<rep;i++) {
			for (int j=0;j<size;j++) {
				ret.push_back(ret[i*size+j]^ret[j]^ret[j+1]);
			}
		}
		
		for (int i=0;i<dif;i++) {
			ret[rnd.nextInt(0,size*rep)]=rnd.nextInt(0,1023);
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
