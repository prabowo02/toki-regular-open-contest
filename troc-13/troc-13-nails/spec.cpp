#include<bits/stdc++.h>
#include<tcframe/spec.hpp>
using namespace std;
using namespace tcframe;
const int mx=10000;

class ProblemSpec : public BaseProblemSpec{
protected:
	int n;
	vector<int>a;
	int ans;

	void InputFormat(){
		LINE(n);
		LINE(a%SIZE(n));
	}
	void OutputFormat(){
		LINE(ans);
	}

	void GradingConfig(){
		TimeLimit(1);
		MemoryLimit(64);
	}
	void Constraints(){
		CONS(1<=n && n<=mx);
		CONS(eachElementBetween(a, 1, mx));
	}
	void Subtask1(){
		Points(100);
	}

private:
	bool eachElementBetween(vector<int>a, int lf, int rg){
		for(int i:a) if(i<lf || i>rg) return false;
		return true;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec>{
protected:
	void SampleTestCase1(){
		Subtasks({1});
		Input({
			"6",
			"1 2 3 1 2 3",
		});
		Output({
			"2",
		});
	}
	void SampleTestCase2(){
		Subtasks({1});
		Input({
			"6",
			"10 10 10 10 10 10",
		});
		Output({
			"0",
		});
	}
	void SampleTestCase3(){
		Subtasks({1});
		Input({
			"2",
			"1 1",
		});
		Output({
			"-1",
		});
	}
	void BeforeTestCase(){
		a.clear();
	}

	void TestGroup1(){
		Subtasks({1});
		//small tc
		CASE(n=1; a.push_back(69);); //no
		CASE(n=2; a.push_back(420); a.push_back(420);); //no
		CASE(n=3; a.push_back(42); a.push_back(69); a.push_back(111);); //x+y=z, no
		CASE(n=4; a.push_back(4); a.push_back(4); a.push_back(2); a.push_back(2);); //x+y=z=w, yes
		CASE(n=4; a.push_back(4); a.push_back(3); a.push_back(2); a.push_back(5);); //x+y=z+w, no
		CASE(n=6; a.push_back(2); a.push_back(3); a.push_back(1); a.push_back(2); a.push_back(3); a.push_back(1);); //yea, expected 2, this anti owo tc
		CASE(n=7; a.push_back(1); a.push_back(1); a.push_back(1); a.push_back(1); a.push_back(1); a.push_back(3); a.push_back(1);); //kill kak rapel's WA sol
		CASE(n=mx; allSame(n);); //yes
		CASE(n=mx; mostSame(n, rnd.nextInt(1, 10));); //most likely no
		CASE(n=mx; pureRand(n);); //most likely no?

		//highly composite perimeter >1e7, all yes
		CASE(n=rnd.nextInt(8001, mx); splitPeri(n, 3696, 14414400); cycshift(n););
		CASE(n=rnd.nextInt(9001, mx); splitPeri(n, 4200, 14414400); cycshift(n););
		CASE(n=rnd.nextInt(9501, mx); splitPeri(n, 4680, 21621600); cycshift(n););
		CASE(n=rnd.nextInt(9501, mx); splitPeri(n, 4620, 21621600); cycshift(n););
		CASE(n=mx; splitPeri(n, 4420, 36756720); cycshift(n););
		CASE(n=rnd.nextInt(9001, mx); splitPeri(n, 3510, 43243200); cycshift(n););
		CASE(n=rnd.nextInt(9501, mx); splitPeri(n, 4004, 43243200); cycshift(n););
		CASE(n=mx; splitPeri(n, 2142, 61261200); cycshift(n););
		CASE(n=mx; splitPeri(n, 3400, 61261200); cycshift(n););
		CASE(n=mx; splitPeri(n, 1785, 73513440); cycshift(n););
		CASE(n=mx; splitPeri(n, 2970, 73513440); cycshift(n););
		CASE(n=mx; splitPeri(n, 2772, 73513440); cycshift(n););

		//side exactly sqrt, yes
		CASE(n=mx; splitPeri(n, 3879, 15046641); cycshift(n););
		
		//shift small number from cases above, most likely no
		CASE(n=rnd.nextInt(8001, mx); splitPeri(n, 3696, 14414400); shiftrand(n); cycshift(n););
		CASE(n=mx; splitPeri(n, 1785, 73513440); shiftrand(n); cycshift(n););
		CASE(n=mx; splitPeri(n, 2772, 73513440); shiftrand(n); cycshift(n););
	}		

private:
	void allSame(int sz){
		int val=rnd.nextInt(100, mx);
		for(int i=0; i<sz; i++)
			a.push_back(val);
	}
	void mostSame(int sz, int d){
		int val=rnd.nextInt(100, mx);
		for(int i=0; i<sz-d; i++)
			a.push_back(val);
		for(int i=0; i<d; i++)
			a.push_back(rnd.nextInt(1, mx));
		rnd.shuffle(a.begin(), a.end());
	}
	void pureRand(int sz){
		for(int i=0; i<sz; i++) a.push_back(rnd.nextInt(1, mx));
	}
	void cycshift(int sz){
		int times=rnd.nextInt(0, sz-1);
		vector<int>nw(sz);
		for(int i=0; i<sz; i++){
			nw[(i+times)%sz]=a[i];
		}
		a=nw;
	}
	vector<int> split(int sm, int sz, int lf, int rg){
		priority_queue<int>pq;
		pq.push(sm);
		while(pq.top()>rg){
			int nw=pq.top(); pq.pop();
			int n1=nw/2, n2=nw-n1;
			if(nw>2*rg){
				pq.push(n1); pq.push(n2); continue;
			}
			int gifdif=rnd.nextInt(0, min(min(n1, n2), rg-max(n1, n2)));
			n1-=gifdif; n2+=gifdif;
			pq.push(n1); pq.push(n2);
		}
		while(pq.size()<sz){
			int nw=pq.top(); pq.pop();
			int rd=rnd.nextInt(1, nw-1);
			pq.push(nw-rd);  pq.push(rd);
		}
		int cnt=0;
		priority_queue<int, vector<int>, greater<int> >pq2;
		while(!pq.empty()){
			cnt++; pq2.push(pq.top()); pq.pop();
		}
		while(cnt>sz){
			int nw1=pq2.top(); pq2.pop();
			int nw2=pq2.top(); pq2.pop();
			int nww=nw1+nw2;
			if(nww<=rg){
				cnt--; pq2.push(nww);
			}else{
				int nw3=pq2.top();
				int rd=rnd.nextInt(nw3+1, rg);
				pq2.push(nww-rd); pq2.push(rd);
			}
		}
		vector<int>nw;
		while(!pq2.empty()){
			nw.push_back(pq2.top()); pq2.pop();
		}
		rnd.shuffle(nw.begin(), nw.end());
		return nw;
	}
	vector<int>split_more_than_need(int sm, int sz, int mor){
		priority_queue<int>pq;
		pq.push(sm);
		int cnt=1;
		while(cnt<sz){
			int nw=pq.top(); 
			if(nw<2*mor+2) break;
			pq.pop();
			int rd=rnd.nextInt(mor+1, nw-mor-1);
			pq.push(rd); pq.push(nw-rd);
			cnt++;
		}
		while(cnt<sz){
			int nw1=pq.top(); pq.pop(); int nw2=pq.top(); pq.pop();
			int nww=nw1+nw2;
			pq.push(mor+1); pq.push(mor+1); pq.push(nww-mor-mor-2);
			cnt++;
		}
		vector<int>rs;
		for(; !pq.empty(); pq.pop()) rs.push_back(pq.top());
		rnd.shuffle(rs.begin(), rs.end());
		return rs;
	}
	void splitPeri(int sz, int side, int peri){
		int len=peri/side;
		vector<int>partition=split_more_than_need(sz, side, max(1, len/sz));
		rnd.shuffle(partition.begin(), partition.end());
		for(int i:partition){
			vector<int>group=split(len, i, 1, 10000);
			rnd.shuffle(group.begin(), group.end());
			for(int j:group) a.push_back(j);
		}
	}
	void shiftrand(int sz){
		int n1=rnd.nextInt(0, sz-1), n2=rnd.nextInt(0, sz-1);
		int rv=rnd.nextInt(1, 10);
		while(n1==n2 || a[n2]<=rv) n2=rnd.nextInt(0, sz-1);
		a[n1]+=rv; a[n2]-=rv;
	}
};
