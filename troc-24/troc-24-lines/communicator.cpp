#include <bits/stdc++.h>
using namespace std;

#define ii pair<int,int>
#define fi first
#define se second

const int Q=42;

void WA(){
	cerr<<"WA"<<endl;
	exit(0);
}

void AC(){
	cerr<<"AC"<<endl;
	exit(0);
}

int n;
vector<ii> v;
int hor[1005][1005];
int ver[1005][1005];

int query(int arr[1005][1005],int l,int r,int d,int u){
	return arr[r][u]-arr[l-1][u]-arr[r][d-1]+arr[l-1][d-1];
}

int query(int l,int r,int d,int u){
	return query(hor,l,r+1,d,u)+query(ver,l,r,d,u+1);
}


int main(int argc, char* argv[]) {
	ifstream tc_in(argv[1]);
	
	tc_in>>n;
	
	int a,b;
	for (int x=0;x<n*n-1;x++){
		tc_in>>a>>b;
		v.push_back(ii(a,b));
	}
	
	//begin preprocessing
	
	v.push_back(v[0]);
	
	for (int x=0;x<n*n-1;x++){
		if (v[x].fi==v[x+1].fi){
			ver[v[x].fi][max(v[x].se,v[x+1].se)]++;
		}
		else{
			hor[max(v[x].fi,v[x+1].fi)][v[x].se]++;
		}
	}
	
	for (int x=0;x<1005;x++)
		for (int y=1;y<1005;y++)
			hor[x][y]+=hor[x][y-1],ver[x][y]+=ver[x][y-1];
	
	for (int y=0;y<1005;y++)
		for (int x=1;x<1005;x++)
			hor[x][y]+=hor[x-1][y],ver[x][y]+=ver[x-1][y];
	
	//begin interaction
	
	cout<<n<<endl;
	
	int queries=0;
	
	while (true){
		char c;
		if (!(cin >> c)) {
			WA();
		}
		if (c == '?'){
			queries++;
			
			if (queries > Q) WA();
			
			int l,r,d,u;
			if (!(cin>>l>>r>>d>>u)) {
				WA();
			}
			
			if (1>l || l>r || r>n || 1>d || d>u || u>n) WA();
			
			cout<<query(l,r,d,u)<<endl;
		} else if (c == '!'){
			int x,y;
			if (!(cin>>x>>y)) {
				WA();
			}
			
			if (query(x,x,y,y)==0) AC();
			else WA();
		}
		else{
			WA();
		}
	}
}
