#include<bits/stdc++.h>
using namespace std;

int n, m, n_scc;
vector<vector<int> >adj, rev;
vector<set<int> >scc;
vector<int>numSCC, dist;
bitset<100005>vis;
vector<bool>child;
stack<int>s;

void accept(){printf("YA\n"); exit(0);}
void reject(){printf("TIDAK\n"); exit(0);}

void put_order(int nw){
	vis[nw]=1;
	for(int nx:adj[nw])
		if(!vis[nx]) put_order(nx);
	s.push(nw);
}
void dfs_scc(int nw){
	vis[nw]=1;
	numSCC[nw]=n_scc;
	for(int nx:rev[nw])
		if(!vis[nx]) dfs_scc(nx);
}
void make_scc(){
	vis.reset();
	for(int i=1; i<=n; i++)
		if(!vis[i]) put_order(i);
	vis.reset();
	while(!s.empty()){
		int nw=s.top(); s.pop();
		if(!vis[nw]){
			n_scc++;
			dfs_scc(nw);
		}
	}
}

void put_order_2(int nw){
	vis[nw]=1;
	for(int nx:scc[nw])
		if(!vis[nx]) put_order_2(nx);
	s.push(nw);
}
int longestPath(int source){
	vis.reset();
	for(int i=1; i<=n_scc; i++)
		if(!vis[i]) put_order_2(i);
	dist.assign(n_scc+1, -2000000000);
	dist[source]=0;
	while(!s.empty()){
		int nw=s.top(); s.pop();
		if(dist[nw]!=-2000000000){
			for(int nx:scc[nw])
				if(dist[nx]<dist[nw]+1)
					dist[nx]=dist[nw]+1;
		}
	}
	int mx=-2000000005;
	for(int i=1; i<=n_scc; i++)
		mx=max(mx, dist[i]);
	return mx;
}

int main(){
	scanf("%d %d", &n, &m);
	adj.resize(n+1); rev.resize(n+1);
	numSCC.resize(n+1);
	for(int i=0, u, v; i<m; i++){
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		rev[v].push_back(u);
	}
	n_scc=0; make_scc();
	if(n_scc==1) accept();
	scc.resize(n_scc+1); child.assign(n_scc+1, false);
	for(int u=1; u<=n; u++){
		for(int v:adj[u]){
			int n1=numSCC[u], n2=numSCC[v];
			if(n1!=n2){
				//n1->n2
				scc[n1].insert(n2);
				child[n2]=true;
			}
		}
	}
	int sc=-1;
	for(int i=1; i<=n_scc; i++){
		if(!child[i]){
			if(sc==-1) sc=i;
			else reject();
		}
	}
	if(sc==-1) reject();
	int get_longest_path=longestPath(sc);
	if(get_longest_path==n_scc-1) accept();
	reject();
}