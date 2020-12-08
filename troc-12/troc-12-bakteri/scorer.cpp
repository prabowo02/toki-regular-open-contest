#include<bits/stdc++.h>
using namespace std;
void WA(string reason){
	cout<<"WA"<<endl; exit(0);
}
void AC(){
	cout<<"AC"<<endl; exit(0);
}
int n, m, k;
bool ans_con;
char ans_con_config[1005][1005];
bool inhibit[1005][1005];
int x[]={1, 0, -1, 0};
int y[]={0, 1, 0, -1};
bool in_bound(int x, int y){return 0<=x && x<n && 0<=y && y<m;}
void check(){
	if(ans_con){
		if(k<(n+m+1)/2) WA("Configuration impossible but output YA");
		queue<pair<int, int> >bfs;
		int number_of_x=0;
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++)
				if(ans_con_config[i][j]=='X'){
				    number_of_x++;
					inhibit[i][j]=true;
					bfs.push(make_pair(i, j));
				}else inhibit[i][j]=false;
		if(number_of_x!=k) WA("Number of colonies used is not K");
		while(!bfs.empty()){
			int xnw=bfs.front().first, ynw=bfs.front().second;
			bfs.pop();
			for(int arah=0; arah<4; arah++){
				int xnx=xnw+x[arah], ynx=ynw+y[arah];
				if(!in_bound(xnx, ynx)) continue;
				if(inhibit[xnx][ynx]) continue;
				int infect_cnt=0;
				for(int surround=0; surround<4; surround++){
					int xs=xnx+x[surround], ys=ynx+y[surround];
					if(!in_bound(xs, ys)) continue;
					if(inhibit[xs][ys]) infect_cnt++;
				}
				if(infect_cnt>=2){
					inhibit[xnx][ynx]=true;
					bfs.push({xnx, ynx});
				}
			}
		}
		bool invalid=false;
		for(int i=0; i<n; i++) for(int j=0; j<m; j++)
			if(!inhibit[i][j]) {invalid=true; break;}
		if(invalid) WA("Configuration is invalid");
		AC();
	}else{
		if((n+m+1)/2<=k) WA("Configuration possible but output TIDAK");
		AC();
	}
}
void read_contestant(ifstream &is){
	string s;
	if(!(is>>s)) WA("No output");
	if(s!="YA" && s!="TIDAK") WA("No YA/TIDAK");
	if(s=="TIDAK")
		ans_con=false;
	else{
		ans_con=true;
		for(int i=0; i<n; i++){
			if(!(is>>s)) WA("Grid size is wrong");
			if(s.size()!=m) WA("Grid size is wrong");
			for(int j=0; j<m; j++){
				if(s[j]!='.' && s[j]!='X') WA("Abnormal data in grid");
				ans_con_config[i][j]=s[j];
			}
		}
	}
	if(is>>s) WA("Extra output");
}
int main(int argc, char *argv[]){
	ifstream tc_in(argv[1]);
	ifstream tc_out(argv[2]);
	ifstream con_out(argv[3]);
	tc_in>>n>>m>>k;
	read_contestant(con_out);
	check();
	return 0;
}
