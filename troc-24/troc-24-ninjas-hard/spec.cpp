#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int maxn=50000;
const int maxq=50000;

class ProblemSpec : public BaseProblemSpec {
  protected:
	int n,q;
	string moves;
	string claps;
	vector<int> v;
	
	void InputFormat() {
		LINE(n,q);
		LINE(moves);
		LINE(claps);
	}
	void OutputFormat() {
		LINES(v)%SIZE(n);
	}
	void GradingConfig() {
		TimeLimit(3);
		MemoryLimit(256);
	}
	void Constraints() {
		CONS(1<=n && n<=maxn);
		CONS(1<=q && q<=maxq);
		CONS(moves.length()==q);
		CONS(claps.length()==q);
		CONS(noCollisions(moves));
		CONS(isBinaryString(claps));
	}
	
  private:
    bool isBinaryString(string s){
		for (auto it:s) if (it<'0' || '1'<it) return false;
		return true;
	}
	
	bool noCollisions(string s){
		#define ii pair<int,int>
		#define fi first
		#define se second
		
		static const int dx[]={0,0,-1,1};
		static const int dy[]={1,-1,0,0};
		
		deque<ii> dq;
		set<ii> pos;
		
		for (int x=n;x>0;x--){
			pos.insert({x,0});
			dq.push_back({x,0});
		}
		
		for (auto &it:s){
			auto temp=dq.back();
			
			pos.erase(dq.front());
			dq.pop_front();
			
			if (it=='U') temp.se++;
			else if (it=='D') temp.se--;
			else if (it=='R') temp.fi++;
			else if (it=='L') temp.fi--;
			else return false;
			if (pos.count(temp)) return false;
			
			pos.insert(temp);
			dq.push_back(temp);
		}
		
		return true;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
  protected:
	void SampleTestCase1(){
		Input({
			"4 4",
			"LURD",
			"0101"
		});
		
		Output({
			"3",
			"4",
			"4",
			"3"
		});
	}
	
	void SampleTestCase2(){
		Input({
			"3 1",
			"U",
			"1"
		});
		
		Output({
			"1",
			"2",
			"1"
		});
	}
	
	void TestGroup1() {
		CASE(n=1,q=1,moves="L",claps="0");
		CASE(n=1,q=1,moves="L",claps="1");
		
		CASE(n=4,q=2,moves="UR",claps="00");
		CASE(n=4,q=2,moves="UR",claps="01");
		CASE(n=4,q=2,moves="UR",claps="10");
		CASE(n=4,q=2,moves="UR",claps="11");
		
		CASE(n=20,q=10,moves="URRRRRRRRR",claps=genString(q));
		
		CASE(n=maxn,q=maxq,moves=string(maxq,'L'),claps=genString(q));
		CASE(n=maxn,q=maxq,moves="U"+string(maxq-1,'R'),claps=genString(q));
		
		CASE(n=maxn,q=maxq,moves=genHilbert(q),claps=genString(q));

		CASE(n = maxn, q = maxq, moves = genSnake(q), claps = genString(q));
		CASE(n = maxn, q = maxq, moves = genSnake(q), claps = genString(q));
		CASE(n = maxn, q = maxq, moves = genSnake(q, 1000), claps = genString(q));
		CASE(n = maxn, q = maxq, moves = genSnake(q, maxn / 5, 2), claps = genString(q));
		CASE(n = maxn, q = maxq, moves = genSnake(q, 1000, 2), claps = genString(q));
		CASE(n = maxn, q = maxq, moves = genSnake(q, 100, 2), claps = genString(q));
		CASE(n = maxn, q = maxq, moves = genSnake(q, 10, 2), claps = genString(q));
		CASE(n = maxn, q = maxq, moves = genSnake(q, 100, 3), claps = genString(q));
		CASE(n = maxn, q = maxq, moves = genSnake(q, maxn / 5, 10), claps = genString(q));
	
		CASE(n = maxn, q=maxq, moves=genPeano(maxn/4,maxq,1e9), claps=genString(q));
		CASE(n = maxn, q=maxq, moves=genPeano(maxn/4,maxq,1000), claps=genString(q));
		CASE(n = maxn, q=maxq, moves=genPeano(maxn/4,maxq,100), claps=genString(q));
		CASE(n = maxn, q=maxq, moves=genPeano(maxn/4,maxq,50), claps=genString(q));
		CASE(n = maxn, q=maxq, moves=genPeano(maxn/4,maxq,10), claps=genString(q));
		CASE(n = maxn, q=maxq, moves=genPeano(maxn/4,maxq,5), claps=genString(q));
		
		CASE(n = rnd.nextInt(1,maxn/2), q=maxq, moves=genPeano(maxn/8,maxq,10), claps=genString(q));
		CASE(n = rnd.nextInt(1,maxn/2), q=maxq, moves=genPeano(maxn/8,maxq,5), claps=genString(q));
		
		CASE(n = rnd.nextInt(1,maxn/4), q=maxq, moves=genPeano(maxn/16,maxq,10), claps=genString(q));
		CASE(n = rnd.nextInt(1,maxn/4), q=maxq, moves=genPeano(maxn/16,maxq,5), claps=genString(q));
		
		CASE(n = maxn, q = 1, moves="L", claps="0");
		CASE(n = maxn, q = 1, moves="L", claps="1");
		
		CASE(n=1,q=maxq,moves=genHilbert(q),claps=genString(q));

		CASE(n = maxn, q = maxq, moves = genSnake(q), claps = genLot0String(q));
		CASE(n = maxn, q=maxq, moves=genPeano(maxn/4,maxq,10), claps=genLot0String(q));
		CASE(n = maxn, q = maxq, moves = genSnake(q), claps = genLot1String(q));
		CASE(n = maxn, q=maxq, moves=genPeano(maxn/4,maxq,10), claps=genLot1String(q));
	}
	
  private:

	string genSnake(int q, int bnd = maxn / 5, int width = 1) {
		string res = "";
		int rem = q;
		bool isl = 1;
		while (rem) {
			int use = min(rnd.nextInt(min(bnd, rem)), rnd.nextInt(min(bnd, rem)));
			rem -= use;
			bool isu = 1;
			int pos = 0;
			while (use) {
				int mv = 0;
				if (isu) {
					mv = rnd.nextInt(width - pos);
				} else {
					mv = rnd.nextInt(pos + 1);
				}
				mv = min(mv, use);
				use -= mv;
				for (int i = 0; i < mv; i++) {
					if (isu) {
						pos++;
						res += "U";
					} else {
						pos--;
						res += "D";
					}
				}
				mv = (use / 10 == 0 ? 0 : rnd.nextInt(use / 10)) + 1;
				mv = min(mv, use);
				use -= mv;
				for (int i = 0; i < mv; i++) {
					res += isl ? "L" : "R";
				}
				isu ^= 1;
			}
			if (rem) {
				res += isl ? "L" : "R";
				rem--;
			}
			while (pos != width && rem) {
				pos++;
				rem--;
				res += "U";
			}
			isl ^= 1;
		}
		return res;
	}

	// https://en.wikipedia.org/wiki/Hilbert_curve

	//rotate/flip a quadrant appropriately
	void rot(int n, int *x, int *y, int rx, int ry) {
		if (ry == 0) {
			if (rx == 1) {
				*x = n-1 - *x;
				*y = n-1 - *y;
			}

			//Swap x and y
			int t  = *x;
			*x = *y;
			*y = t;
		}
	}

	//convert d to (x,y)
	void d2xy(int n, int d, int *x, int *y) {
		int rx, ry, s, t=d;
		*x = *y = 0;
		for (s=1; s<n; s*=2) {
			rx = 1 & (t/2);
			ry = 1 & (t ^ rx);
			rot(s, x, y, rx, ry);
			*x += s * rx;
			*y += s * ry;
			t /= 4;
		}
	}
	
	string genHilbert(int q){
		#define ii pair<int,int>
		#define fi first
		#define se second
		
		vector<ii> v;
		for (int x=0;x<=q;x++){
			int a,b;
			d2xy(1<<17,x,&a,&b);
			a*=-1;
			
			v.push_back({a,b});
		}
		
		string res;
		for (int x=1;x<=q;x++){
			int a=v[x].fi-v[x-1].fi,b=v[x].se-v[x-1].se;
			
			if (a==-1 && b==0) res+="L";
			else if (a==1 && b==0) res+="R";
			else if (a==0 && b==-1) res+="D";
			else res+="U";
		}
		
		return res;
	}
	
	string genPeano(int n,int len,int hole){
		const int dx[]={0,-1,0,1};
		const int dy[]={1,0,-1,0};
		const char cdir[]={'U','L','D','R'};
		
		int IDX=0;
		map<ii,int> id;
		vector<tuple<int,int,int> > q;

		bool al[100005][4];

		set<ii> vis;
		
		memset(al,false,sizeof(al));
		
		id[{0,0}]=IDX;
		
		// 2 1
		// 3 0
		
		for (int x=0;x<4;x++){
			q.push_back({0,0,x});
			al[IDX*4+x][x]=al[IDX*4+x][(x+1)%4]=true;
		}
		
		IDX++;
		
		for (int x=1;x<n;x++){
			int px=-1,py=-1,dir=-1;
			int px2,py2;
			
			do{
				int idx=rnd.nextInt(q.size());
				swap(q[idx],q.back());
				tie(px,py,dir)=q.back();
				q.pop_back();
				
				px2=px+dx[dir],py2=py+dy[dir];
				
				if (px2>0 && py2==0) dir=-1;
				//dont intersect with original position
				
				if (id.count({px2,py2})) dir=-1;
				
				if (dir!=-1 && rnd.nextInt(hole)==0){
					id[{px2,py2}]=-1;
					dir=-1;
				}
			} while (dir==-1);
			
			id[{px2,py2}]=IDX;
			
			int IDX0=id[{px,py}];
			
			// cout<<px<<" "<<py<<" "<<px2<<" "<<py2<<endl;
			// cout<<IDX<<" "<<IDX0<<endl;
			
			//U L D R
			
			// 2 1
			// 3 0
			
			al[IDX0*4+(1+dir)%4][dir]=al[IDX0*4+(2+dir)%4][dir]=true;
			al[IDX*4+(3+dir)%4][(2+dir)%4]=al[IDX*4+(4+dir)%4][(2+dir)%4]=true;
			
			for (int x=0;x<4;x++){
				q.push_back({px2,py2,x});
				al[IDX*4+x][x]=al[IDX*4+x][(x+1)%4]=true;
			}
			
			IDX++;
		}
		
		int px=0,py=0;
		int dir=0;
		
		string s;
		
		do{
			int IDX=id[{(px+1)>>1,py>>1}]*4;
			
			if (px%2==0 && py%2==0) ;
			else if (px%2==0) IDX+=1;
			else if (py%2==0) IDX+=3;
			else IDX+=2;
			
			for (int z=3;z<=5;z++){
				int d2=(dir+z)%4;
				
				if (al[IDX][d2]){
					s+=cdir[d2];
					int px2=px+dx[d2],py2=py+dy[d2];
					if (vis.count({px2,py2})) continue;
					vis.insert({px2,py2});
					
					px=px2,py=py2;
					dir=d2;
					break;
				}
			}
		} while (px!=0 || py!=0);
		
		string res;
		for (int x=0;x<len;x++) res+=s[x%(4*n)];
		
		return res;
	}
	
	string genString(int q){
		string res;
		for (int x=0;x<q;x++){
			if (rnd.nextInt(2)) res+="0";
			else res+="1";
		}
		return res;
	}
	
	string genLot0String(int q){
		string res;
		for (int x=0;x<q;x++){
			if (rnd.nextInt(100) < 95) res+="0";
			else res+="1";
		}
		return res;
	}
	
	string genLot1String(int q){
		string res;
		for (int x=0;x<q;x++){
			if (rnd.nextInt(100) >= 95) res+="0";
			else res+="1";
		}
		return res;
	}
};
