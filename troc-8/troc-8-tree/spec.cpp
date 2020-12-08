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

bool isTree(vector<int> &V,int N,int depth) {
	if (V.size()!=N-1) {
		return 0;
	}
	
	int maks, D[N+1];
	maks=1;
	D[1]=1;
	
	for (int i=2;i<=N;i++) {
		if (V[i-2]>=i||V[i-2]<=0) {
			return 0;
		}
		
		D[i]=D[V[i-2]]+1;
		maks=max(maks,D[i]);
	}
	
	if (maks>depth) {
		return 0;
	}
	
	return 1;
}

bool validQuery(vector <vector<int> > &T,int N,int Q,int mins,int maks) {
	if (T.size()!=Q) {
		return 0;
	}
	
	for (int i=0;i<Q;i++) {
		if (T[i].empty()) {
			return 0;
		}
		
		if (T[i][0]==1) {
			if (T[i].size()!=4) {
				return 0;
			}
			
			if (T[i][1]<1||T[i][1]>N) {
				return 0;
			}
			
			if (T[i][2]<1||T[i][2]>N) {
				return 0;
			}
			
			if (T[i][3]<mins||T[i][3]>maks) {
				return 0;
			}
		}
		else if (T[i][0]==2) {
			if (T[i].size()!=3) {
				return 0;
			}
			
			if (T[i][1]<1||T[i][1]>N) {
				return 0;
			}
			
			if (T[i][2]<mins||T[i][2]>maks) {
				return 0;
			}
		}
		else if (T[i][0]==3) {
			if (T[i].size()!=3) {
				return 0;
			}
			
			if (T[i][1]<1||T[i][1]>N) {
				return 0;
			}
			
			if (T[i][2]<1||T[i][2]>N) {
				return 0;
			}
		}
		else if (T[i][0]==4) {
			if (T[i].size()!=2) {
				return 0;
			}
			
			if (T[i][1]<1||T[i][1]>N) {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	
	return 1;
}

class ProblemSpec : public BaseProblemSpec {
protected:
	int N, Q;
	vector <int> P, A;
	vector <vector<int> > T;
	vector <long long> H;
	
	void InputFormat() {
		LINE(N,Q);
		LINE(P%SIZE(N-1));
		LINE(A%SIZE(N));
		LINES(T)%SIZE(Q);
	}
	int query_count;
	void BeforeOutputFormat() {
		query_count = 0;
		for (int i = 0; i < Q; ++i) {
			if (T[i][0] == 3 || T[i][0] == 4) ++query_count;
		}
	}

	void OutputFormat() {
		LINES(H)%SIZE(query_count);
	}
	
	void GradingConfig() {
		TimeLimit(2);
		MemoryLimit(64);
    }
	
	void Constraints() {
		CONS(1<=N&&N<=100000);
		CONS(1<=Q&&Q<=100000);
		CONS(eachElementBetween(A,-1000000,1000000));
		CONS(isTree(P,N,20));
		CONS(validQuery(T,N,Q,-1000000,1000000));
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
			"5 6",
			"1 2 1 2",
			"3 8 5 5 1",
			"3 3 4",
			"4 2",
			"1 5 3 3",
			"2 1 -1",
			"3 3 1",
			"4 1"
		});
		Output({
			"21",
			"14",
			"19",
			"26"
		});
	}
	
	void TestGroup1() {
		Subtasks({1});
		
		CASE(N=1,Q=215,P={},A={35478},T=randomOperation(N,Q,".1234"));
		CASE(N=2,Q=308,P={1},A={-39475,202471},T=randomOperation(N,Q,".1234"));
		
		CASE(N=100000,Q=100000,P=shortBroom(N),A=randomBetween(N,-1000000,1000000),T=randomOperation(N,Q,".1234"));
		CASE(N=100000,Q=100000,P=longBroom(N),A=randomBetween(N,-1000000,1000000),T=randomOperation(N,Q,".1234"));
		CASE(N=100000,Q=100000,P=stickBroom(N),A=randomBetween(N,-1000000,1000000),T=randomOperation(N,Q,".1234"));
		CASE(N=100000,Q=100000,P=binaryTree(N),A=randomBetween(N,-1000000,1000000),T=randomOperation(N,Q,".1234"));
		CASE(N=100000,Q=100000,P=ternaryTree(N),A=randomBetween(N,-1000000,1000000),T=randomOperation(N,Q,".1234"));
		
		CASE(N=100000,Q=100000,P=randomTree(N,20),A=randomBetween(N,-1000000,1000000),T=randomOperation(N,Q,"...3."));
		CASE(N=100000,Q=100000,P=randomTree(N,20),A=randomBetween(N,-1000000,1000000),T=randomOperation(N,Q,"....4"));
		CASE(N=100000,Q=100000,P=randomTree(N,20),A=randomBetween(N,-1000000,1000000),T=randomOperation(N,Q,"...34"));
		CASE(N=100000,Q=100000,P=randomTree(N,20),A=randomBetween(N,-1000000,1000000),T=randomOperation(N,Q,"..2.4"));
		CASE(N=100000,Q=100000,P=randomTree(N,20),A=randomBetween(N,-1000000,1000000),T=randomOperation(N,Q,".1.3."));
		CASE(N=100000,Q=100000,P=randomTree(N,20),A=randomBetween(N,-1000000,1000000),T=randomOperation(N,Q,".123."));
		CASE(N=100000,Q=100000,P=randomTree(N,20),A=randomBetween(N,-1000000,1000000),T=randomOperation(N,Q,".12.4"));
		
		CASE(N=100000,Q=100000,P=randomTree(N,5),A=randomBetween(N,-1000000,1000000),T=randomOperation(N,Q,".1234"));
		CASE(N=100000,Q=100000,P=randomTree(N,10),A=randomBetween(N,-1000000,1000000),T=randomOperation(N,Q,".1234"));
		CASE(N=100000,Q=100000,P=randomTree(N,20),A=randomBetween(N,-1000000,1000000),T=randomOperation(N,Q,".1234"));
		
		for (int i=0;i<3;i++) {
			CASE(N=rnd.nextInt(1,100000),Q=rnd.nextInt(1,100000),P=randomTree(N,20),A=randomBetween(N,-1000000,1000000),T=randomOperation(N,Q,".1234"));
		}
	}
	
	vector <int> shortBroom(int N) {
		vector <int> ret;
		ret.clear();
		
		for (int i=2;i<=N;i++) {
			ret.push_back(1);
		}
		
		return ret;
	}
	
	vector <int> longBroom(int N) {
		vector <int> ret;
		ret.clear();
		
		for (int i=2;i<=N;i++) {
			if (i%19==2) {
				ret.push_back(1);
			}
			else {
				ret.push_back(i-1);
			}
		}
		
		return ret;
	}
	
	vector <int> stickBroom(int N) {
		vector <int> ret;
		ret.clear();
		
		for (int i=2;i<=N;i++) {
			ret.push_back(min(i-1,19));
		}
		
		return ret;
	}
	
	vector <int> binaryTree(int N) {
		vector <int> ret;
		ret.clear();
		
		for (int i=2;i<=N;i++) {
			ret.push_back(i/2);
		}
		
		return ret;
	}
	
	vector <int> ternaryTree(int N) {
		vector <int> ret;
		ret.clear();
		
		for (int i=2;i<=N;i++) {
			ret.push_back((i+1)/3);
		}
		
		return ret;
	}
	
	vector <int> randomTree(int N,int depth) {
		vector <int> ret;
		ret.clear();
		
		int D[N+1];
		D[1]=1;
		
		for (int i=2;i<=N;i++) {
			int P;
			P=rnd.nextInt(1,i-1);
			
			if (D[P]==depth) {
				i--;
			}
			else {
				ret.push_back(P);
				D[i]=D[P]+1;
			}
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
	
	vector <vector<int> > randomOperation(int N,int Q,string jenis) {
		vector <vector<int> > ret;
		ret.clear();
		
		for (int i=0;i<Q;i++) {
			int tipe;
			tipe=rnd.nextInt(1,4);
			
			if (jenis[tipe]=='.') {
				i--;
				continue;
			}
			
			if (tipe==1) {
				ret.push_back({1,rnd.nextInt(1,N),rnd.nextInt(1,N),rnd.nextInt(-1000000,1000000)});
			}
			
			if (tipe==2) {
				ret.push_back({2,rnd.nextInt(1,N),rnd.nextInt(-1000000,1000000)});
			}
			
			if (tipe==3) {
				ret.push_back({3,rnd.nextInt(1,N),rnd.nextInt(1,N)});
			}
			
			if (tipe==4) {
				ret.push_back({4,rnd.nextInt(1,N)});
			}
		}
		
		return ret;
	}
};
