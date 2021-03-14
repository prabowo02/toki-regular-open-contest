#include <stdio.h>
#include <vector>
#include <bitset>
using namespace std;

const int MX = 2005;
int n, t[MX], x[MX], y[MX], z[MX];

bool contradiction(int a1, int b1, int c1, int t1, 
					int a2, int b2, int c2, int t2){
	// t = 1 -> (a == c) && (b <= c)
	// t = 2 -> (a == c) && (b >= c)

	if(a1 == a2 && c1 != c2) return true;
	if(a1 == b2){
		if(t2 == 1){
			if(c1 > c2) return true;
		}else{
			if(c1 < c2) return true;
		}
	}
	if(b1 == a2){
		if(t1 == 1){
			if(c1 < c2) return true;
		}else{
			if(c1 > c2) return true;
		}
	}
	if(b1 == b2){
		if(t1 == 1 && t2 == 2){
			if(c1 < c2) return true;
		}else if(t1 == 2 && t2 == 1){
			if(c1 > c2) return true;
		}
	}

	return false;
}

vector<int> adj[MX * 4], rev[MX * 4], st;
int nSCC[MX * 4], nc = 0;
bitset<8005> vis;

void put_order(int nw){
	vis[nw] = 1;
	for(int nx : adj[nw])
		if(!vis[nx])
			put_order(nx);
	st.push_back(nw);
}

void dfs(int nw){
	vis[nw] = 1;
	nSCC[nw] = nc;
	for(int nx : rev[nw])
		if(!vis[nx]) dfs(nx);
}

void proc_scc(){
	vis.reset();
	for(int i = 0; i < 4 * n; i ++)
		if(!vis[i]) put_order(i);
	vis.reset();
	while(!st.empty()){
		int nw = st.back();
		st.pop_back();
		if(!vis[nw]){
			nc ++;
			dfs(nw);
		}
	}
}

int main(){
	scanf("%d %d", &n, &n);
	for(int i = 0; i < n; i ++)
		scanf("%d %d %d %d", &t[i], &x[i], &y[i], &z[i]);

	for(int i = 0; i < n; i ++){
		int a = 2 * i, b = 2 * i + 1;
		adj[2 * a + 1].push_back(2 * b);
		rev[2 * b].push_back(2 * a + 1);
		adj[2 * b + 1].push_back(2 * a);
		rev[2 * a].push_back(2 * b + 1);

		for(int j = i + 1; j < n; j ++){
			int c = 2 * j, d = 2 * j + 1;

			if(contradiction(x[i], y[i], z[i], t[i], x[j], y[j], z[j], t[j])){
				adj[2 * a].push_back(2 * c + 1);
				rev[2 * c + 1].push_back(2 * a);
				adj[2 * c].push_back(2 * a + 1);
				rev[2 * a + 1].push_back(2 * c);
			}
			if(contradiction(y[i], x[i], z[i], t[i], x[j], y[j], z[j], t[j])){
				adj[2 * b].push_back(2 * c + 1);
				rev[2 * c + 1].push_back(2 * b);
				adj[2 * c].push_back(2 * b + 1);
				rev[2 * b + 1].push_back(2 * c);
			}
			if(contradiction(x[i], y[i], z[i], t[i], y[j], x[j], z[j], t[j])){
				adj[2 * a].push_back(2 * d + 1);
				rev[2 * d + 1].push_back(2 * a);
				adj[2 * d].push_back(2 * a + 1);
				rev[2 * a + 1].push_back(2 * d);
			}
			if(contradiction(y[i], x[i], z[i], t[i], y[j], x[j], z[j], t[j])){
				adj[2 * b].push_back(2 * d + 1);
				rev[2 * d + 1].push_back(2 * b);
				adj[2 * d].push_back(2 * b + 1);
				rev[2 * b + 1].push_back(2 * d);
			}
		}
	}

	proc_scc();

	bool ans = 1;
	for(int i = 0; i < 4 * n; i += 2)
		if(nSCC[i] == nSCC[i + 1]) ans = 0;

	if(ans) printf("YES\n");
	else printf("NO\n");
	return 0;
}
