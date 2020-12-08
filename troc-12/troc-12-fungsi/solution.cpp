#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fst first
#define snd second
#define vi vector<int>
#define vpi vector<pii>
#define pub push_back
using namespace std;
const int LG = 18, SZ = 100001;
int n, a, b, ca, cb, da, db, q;
vector<vpi> adj;
pii ori[SZ] = {};
int node[SZ] = {}, h[SZ] = {};
ll sps[SZ][LG][2] = {}, sz[SZ] = {}, rootCyc[SZ]={};
int dfs(int u)
{
	int cyc = -1;
	node[u] = -2;
	if (node[ori[u].fst] == -1) {cyc = dfs(ori[u].fst);}
	if (u == ori[u].fst)
	{
		node[u] = adj.size();
		rootCyc[adj.size()] = ori[u].snd;
		adj.pub(vpi());
	}
	else if (cyc == -1)
	{
		node[u] = adj.size();
		adj.pub(vpi());
		if (node[ori[u].fst] >= 0) {adj[node[ori[u].fst]].pub({adj.size() - 1, ori[u].snd});}
	}
	else 
	{
		sz[u] = sz[ori[u].fst] + ori[u].snd;
		node[u] = adj.size() - 1;
		//cout << u << " " << cyc << " " << node[u]<<"\n";
		if (cyc == u) 
		{
			rootCyc[adj.size() - 1] = sz[u];
			sz[u] = 0;
			cyc = -1;
		}
	}
	if (node[ori[u].fst] == -2) {cyc = ori[u].fst; sz[u] += ori[u].snd;}
	return cyc;	
}
void dfs2(int u, int p, int c)
{
	sps[u][0][0] = p; sps[u][0][1] = c;
	h[u] = (p + 1) ? (h[p] + 1) : 0;
	//cout<<"DFS2 "<<u<<" "<<p<<" "<<c<<"\n";
	for (int i = 1; i < LG; i++)
	{
		sps[u][i][0] = -1;
		if (sps[u][i - 1][0] + 1)
		{
			sps[u][i][0] = sps[sps[u][i - 1][0]][i - 1][0];
			sps[u][i][1] = sps[u][i - 1][1] + sps[sps[u][i-1][0]][i - 1][1];
		}
	}
	for (auto v : adj[u]) {dfs2(v.fst, u, v.snd);}
}
ll MOD(ll a, ll m) {return ((a % m) + m)% m;}
ll lca(int u, int v)
{
	ll v1 = u, v2 = v, rem1 = 0, rem2 = 0;
	u = node[u % n]; v = node[v % n];
	if (h[u] > h[v]) {swap(u, v); swap(v1, v2);}
	//cout<<"ORI "<<u<<" "<<v<<" "<<v1<<" "<<v2<<"\n";
	for (int i = 0; i < LG; i++)
	{
		if ((h[v] - h[u]) & (1 << i)) {rem2 += sps[v][i][1]; v = sps[v][i][0];}
	}
	for (int i = LG - 1; i >= 0; i--)
	{
		if (sps[u][i][0] != sps[v][i][0])
		{
			rem1 += sps[u][i][1];
			rem2 += sps[v][i][1];
			u = sps[u][i][0];
			v = sps[v][i][0];
		}
	}
	//cout << u << " " << v << " " << v1 << " " << rem1 << " " << v2 << " " << rem2 <<"\n";
	if (u != v) 
	{
		rem1 += sps[u][0][1];
		rem2 += sps[v][0][1];
		u = sps[u][0][0];
		v = sps[v][0][0];
	}
	//cout << rem1 << " " << rem2 << "\n";
	if (u == -1) {return -1;}
	else if (v1 - rem1 == v2 - rem2) {return v1 - rem1;}
	else
	{
		//cout<<u<<" "<<h[u]<<" H\n";
		for (int i = 0; i < LG; i++)
		{

			if (h[u] & (1 << i)) 
			{
				rem1 += sps[u][i][1]; 
				rem2 += sps[u][i][1];
				u = sps[u][i][0];
			}
		}
		//cout<<v2 - rem2<<" "<<sz[((v2 - rem2)%n + n) % n]<<" "<<v1 - rem1<<" "<<sz[((v1 - rem1)%n + n) % n]<<"\n";
		if ((v2 - rem2 - sz[MOD(v2 -rem2, n)] - v1 + rem1 + sz[MOD(v1 -rem1, n)]) % rootCyc[u] == 0) {return min(v2 - rem2, v1 - rem1);}
	}
	return -1;
}
int32_t main()
{
	//ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> a >> b >> ca >> cb >> da >> db;
	n = a * b;
	for (int i = 0; i < n; i++)
	{
		node[i] = -1;
		if (i % a == ca) {ori[i] = {((i - da) % n + n) % n, da};}
		else if (i % b == cb) {ori[i] = {((i - db) % n + n) % n, db};}
		else {ori[i] = {(i - 1 + n) % n, 1};}
		//cout<<i<<" "<<ori[i].fst<<" "<<ori[i].snd<<"\n";
	}
	//cout<<"CHECK NODE :\n";
	for (int i = 0; i < n; i++) 
	{
		if (node[i] == -1) {dfs(i);}
	}
	for (int i = 0; i < adj.size(); i++)
	{
		if (rootCyc[i]) {dfs2(i, -1, 0);}
	}
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		int n1, n2;
		ll rs = 0; 
		cin >> n1 >> n2;
		rs = lca(n1, n2);
		if (rs < 1) {cout << "-1\n";}
		else {cout << rs << "\n";}
	}
	return 0;
}