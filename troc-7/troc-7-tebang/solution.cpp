#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define pb push_back
#define reset(a,b) memset(a,b,sizeof a);
#define ALL(x) x.begin(),x.end()
#define debug(x) cout<<#x<<" = "<<(x)<<endl
#define sz(x) (int)(x.size())
#define lt(x) (int)(x.length())
#define MOD 1000000007 
#define mx 100003

set<int> g[mx];
int n, u, v, s, e;

int maks, jauh;

void dfs(int now, int par, int dist){
	if(maks < dist){
		maks = dist;
		jauh = now;
	}
	for(int i : g[now]){
		if(i != par)
			dfs(i, now, dist + 1);
	}
}

int jarak[2][mx];

void cariJarak(int t, int now, int par, int dist){
	jarak[t][now] = dist;
	for(int i : g[now]){
		if(i != par)
			cariJarak(t, i, now, dist + 1);
	}
}

int main(){
	cin >> n;
	for(int i = 1; i < n; i++){
		cin >> u >> v;
		g[u].insert(v);
		g[v].insert(u);
	}
	maks = -1;
	dfs(1, 0, 0);
	s = jauh;
	maks = -1;
	dfs(s, 0, 0);
	e = jauh;
	cariJarak(0, s, 0, 0);
	cariJarak(1, e, 0, 0);
	if(maks % 2 == 0){
		int mid;
		for(int i = 1; i <= n; i++){
			if(jarak[0][i] == jarak[1][i] && jarak[0][i] * 2 == jarak[0][e]){
				mid = i;
				break;
			}
		}
		int mid1, mid2;
		for(int i : g[mid]){
			if(jarak[0][i] + jarak[1][i] == jarak[0][e] && jarak[0][i] > jarak[1][i])
				mid1 = i;
			if(jarak[0][i] + jarak[1][i] == jarak[0][e] && jarak[0][i] < jarak[1][i])
				mid2 = i;
		}
		g[mid].erase(mid1);
		g[mid1].erase(mid);
		maks = -1;
		dfs(mid1, 0, 0);
		maks = -1;
		dfs(jauh, 0, 0);
		int ans1 = maks;
		maks = -1;
		dfs(mid2, 0, 0);
		maks = -1;
		dfs(jauh, 0, 0);
		ans1 = max(ans1, maks);
		g[mid].insert(mid1);
		g[mid1].insert(mid);


		g[mid].erase(mid2);
		g[mid2].erase(mid);
		maks = -1;
		dfs(mid1, 0, 0);
		maks = -1;
		dfs(jauh, 0, 0);
		int ans2 = maks;
		maks = -1;
		dfs(mid2, 0, 0);
		maks = -1;
		dfs(jauh, 0, 0);
		ans2 = max(ans2, maks);
		cout << min(ans1, ans2) << '\n';
		return 0;
	}
	int mid1, mid2;
	for(int i = 1; i <= n; i++){
		if(jarak[0][i] + 1 == jarak[1][i] && jarak[0][i] + jarak[1][i] == jarak[0][e])
			mid1 = i;
		if(jarak[0][i] == jarak[1][i] + 1 && jarak[0][i] + jarak[1][i] == jarak[0][e])
			mid2 = i;
	}
	assert(g[mid1].count(mid2));
	g[mid1].erase(mid2);
	g[mid2].erase(mid1);
	maks = -1;
	dfs(mid1, 0, 0);
	maks = -1;
	dfs(jauh, 0, 0);
	int ans = maks;
	maks = -1;
	dfs(mid2, 0, 0);
	maks = -1;
	dfs(jauh, 0, 0);
	ans = max(ans, maks);
	cout << ans << '\n';
}