#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

#define ii pair<int,int>
#define fi first
#define se second

class ProblemSpec : public BaseProblemSpec {
 protected:
  int n;
  vector<int> X,Y;
 
  void InputFormat() {
	LINE(n);
	LINES(X,Y)%SIZE(n*n-1);
  }
  
  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }
  void Constraints() {
	  CONS(eachElementBetween(X,1,n));
	  CONS(eachElementBetween(Y,1,n));
	  CONS(isLoop(X,Y));
  }
  void StyleConfig() {
    InteractiveEvaluator();
  }
  
 private:
  bool isLoop(vector<int> vx,vector<int> vy){
	  vector<pair<int,int> > v;
	  for (int x=0;x<n*n-1;x++) v.push_back({vx[x],vy[x]});
	  
	  //check that all elements are distinct;
	  set<pair<int,int> > s;
	  for (int x=0;x<n*n-1;x++) s.insert(v[x]);
	  if (s.size()!=n*n-1) return false;
	  
	  v.push_back(v[0]);
	  for (int x=0;x<n*n-1;x++){
		  int dist=abs(v[x+1].first-v[x].first)
						+abs(v[x+1].second-v[x].second);
		  if (dist!=1) return false;
	  }
	  
	  return true;
  }
  
  bool eachElementBetween(vector<int> v,int l,int r){
	  for (auto it:v){
	  	  if (it<l || r<it) return false;
	  }
	  return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
	void SampleTestCase1(){
		Input({ //bruh when i have to input this by hand :clown:
			"5",
			"1 1",
			"2 1",
			"2 2",
			"3 2",
			"3 1",
			"4 1",
			"5 1",
			"5 2",
			"4 2",
			"4 3",
			"5 3",
			"5 4",
			"5 5",
			"4 5",
			"4 4",
			"3 4",
			"3 3",
			"2 3",
			"2 4",
			"2 5",
			"1 5",
			"1 4",
			"1 3",
			"1 2",
		});
	}
	
	void BeforeTestCase() {
		X.clear();
		Y.clear();
	}
	
	void TestGroup1() {
		CASE(n=3,gen_snake(3,2,2));
		
		CASE(n=3,grid_shuffle(3,1,1));
		CASE(n=3,grid_shuffle(3,1,3));
		CASE(n=3,grid_shuffle(3,3,3));
		CASE(n=3,grid_shuffle(3,3,1));
		
		for (int x=0;x<2;x++){
			int a,b;
			do {
				a=rnd.nextInt(2,998);
				b=rnd.nextInt(2,998);
			} while (a%2!=b%2);
			
			CASE(n=999,gen_snake(999,a,b));
		}
		
		for (int x=0;x<10;x++){
			int a,b;
			do {
				a=rnd.nextInt(2,998);
				b=rnd.nextInt(2,998);
			} while (a%2!=b%2);
			
			CASE(n=999,grid_shuffle(999,a,b));
		}
		
		//border cases
		CASE(n=999,grid_shuffle(999,1,1));
		CASE(n=999,grid_shuffle(999,1,999));
		CASE(n=999,grid_shuffle(999,999,999));
		CASE(n=999,grid_shuffle(999,999,1));
		
		CASE(n=999,grid_shuffle(999,1,rnd.nextInt(0,449)*2+1));
		CASE(n=999,grid_shuffle(999,n,rnd.nextInt(0,449)*2+1));
		CASE(n=999,grid_shuffle(999,rnd.nextInt(0,449)*2+1,1));
		CASE(n=999,grid_shuffle(999,rnd.nextInt(0,449)*2+1,n));
		
		//idk 69
		CASE(n=69,grid_shuffle(69,42,42));
	}
	
  private:
	void snake(int ax,int ay,int bx,int by){
		//find path from (ax,ay) to (bx,by)
		
		if ((ax-bx)%2==0){
			while (true){
				if (ay<by){
					for (int y=ay;y<=by;y++){
						X.push_back(ax);
						Y.push_back(y);
					}
				}
				else{
					for (int y=ay;y>=by;y--){
						X.push_back(ax);
						Y.push_back(y);
					}
				}
				
				swap(ay,by);
				
				if (ax==bx) break;
				
				if (ax<bx) ax++;
				else ax--;
			}
		}
		else{
			while (true){
				if (ax<bx){
					for (int x=ax;x<=bx;x++){
						X.push_back(x);
						Y.push_back(ay);
					}
				}
				else{
					for (int x=ax;x>=bx;x--){
						X.push_back(x);
						Y.push_back(ay);
					}
				}
				
				swap(ax,bx);
				
				if (ay==by) break;
				
				if (ay<by) ay++;
				else ay--;
			}
		}
	}
	
	void gen_snake(int n,int a,int b){
		//the missing point cannot be on borders, also respect parity
		snake(1,b,a-1,1);
		snake(a,1,n,b-1);
		snake(n,b,a+1,n);
		snake(a,n,1,b+1);
	}
	
	const static int W=1005;
	
	int id(int i,int j){
		return i*W+j;
	}
	
	void dfs(int i,vector<int> *al,bool *vis){
		vis[i]=true;
		X.push_back(i/W),Y.push_back(i%W);
		for (auto &it:al[i]){
			if (!vis[it]) dfs(it,al,vis);
		}
	}
		
	void grid_shuffle(int n,int a,int b){
		struct UFDS{
			int p[W*W];
			
			UFDS(){
				for (int x=0;x<W*W;x++) p[x]=x;
			}
			
			int par(int i){
				if (p[i]==i) return i;
				else return p[i]=par(p[i]);
			}
			
			void unions(int i,int j){
				i=par(i),j=par(j);
				p[i]=j;
			}
		} ufds;
		
		bool hor[W][W];
		bool ver[W][W];
		bool vis[W][W];
		
		memset(hor,0,sizeof(hor));
		memset(ver,0,sizeof(ver));
		
		memset(vis,false,sizeof(vis));
		vis[a][b]=true;
		
		int dx[]={1,0,-1,0};
		int dy[]={0,1,0,-1};
		
		for (int x=1;x<=n;x++){
			for (int y=1;y<=n;y++){
				if (vis[x][y]) continue;
				
				int dir=0;
				
				int px=x,py=y;
				do{
					for (int z=3;z<6;z++){
						int px2=px+dx[(dir+z)%4],py2=py+dy[(dir+z)%4];
						if (px2<1 || n<px2 || py2<1 || n<py2) continue;
						if (vis[px2][py2]) continue;
						
						vis[px2][py2]=true;
						dir=(dir+z)%4;
						
						break;
					}
					
					if (dir==0) ver[px+1][py]=1;
					if (dir==1) hor[px][py+1]=1;
					if (dir==2) ver[px][py]=1;
					if (dir==3) hor[px][py]=1;
					
					px+=dx[dir];
					py+=dy[dir];
				} while (px!=x || py!=y);
			}
		}
		
		do{
			//sometimes ufds cannot connect stuff using 2 edge flips
			//so we just do rng bash until it works lol
			
			ufds=UFDS();
			
			int SHOTS=3000000;
			for (int x=0;x<SHOTS;x++){
				int a=rnd.nextInt(2,n),b=rnd.nextInt(2,n);
				
				if (hor[a-1][b] && hor[a][b] && !ver[a][b-1] && !ver[a][b]){
					hor[a-1][b]=hor[a][b]=false;
					ver[a][b-1]=ver[a][b]=true;
				}
				else if (ver[a][b-1] && ver[a][b] && !hor[a-1][b] && !hor[a][b]){
					hor[a-1][b]=hor[a][b]=true;
					ver[a][b-1]=ver[a][b]=false;
				}
			}
			
			for (int x=1;x<=n;x++){
				for (int y=1;y<=n;y++){
					if (hor[x][y]) ufds.unions(id(x,y-1),id(x,y));
					if (ver[x][y]) ufds.unions(id(x-1,y),id(x,y));
				}
			}
			
			vector<ii> pos;
			for (int x=2;x<=n;x++){
				for (int y=2;y<=n;y++) pos.push_back({x,y});
			}
			
			rnd.shuffle(pos.begin(),pos.end());
			
			for (auto [a,b]:pos){
				if (hor[a-1][b] && hor[a][b] && !ver[a][b-1] && !ver[a][b]){
					if (ufds.par(id(a-1,b)) != ufds.par(id(a,b))){
						hor[a-1][b]=hor[a][b]=false;
						ver[a][b-1]=ver[a][b]=true;
						ufds.unions(id(a-1,b),id(a,b));
					}
				}
				if (ver[a][b-1] && ver[a][b] && !hor[a-1][b] && !hor[a][b]){
					if (ufds.par(id(a,b-1)) != ufds.par(id(a,b))){
						hor[a-1][b]=hor[a][b]=true;
						ver[a][b-1]=ver[a][b]=false;
						ufds.unions(id(a,b-1),id(a,b));
					}
				}
			}
			
			vector<int> al[W*W];
			bool vis[W*W];
			memset(vis,0,sizeof(vis));
			
			for (int x=1;x<=n;x++){
				for (int y=1;y<=n;y++) if (hor[x][y]){
					al[id(x,y)].push_back(id(x,y-1));
					al[id(x,y-1)].push_back(id(x,y));
				}
			}
			for (int x=1;x<=n;x++){
				for (int y=1;y<=n;y++) if (ver[x][y]){
					al[id(x,y)].push_back(id(x-1,y));
					al[id(x-1,y)].push_back(id(x,y));
				}
			}
			
			int root;
			if (a==1 && b==1) root=id(1,2);
			else root=id(1,1);
			
			X.clear();
			Y.clear();
			dfs(root,al,vis);
			
			//cout<<X.size()<<endl;
		} while (X.size()!=n*n-1);
	}
};
