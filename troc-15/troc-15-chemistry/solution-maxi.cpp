#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
using namespace std;

const int MX = 200005;
const int inf = 1e9 + 69;

int n, m, tp, k, dp[MX];
vector<pair<int, int> > adj[MX];
bitset<MX> sc;

int f(int nw){
	if(sc[nw]) return dp[nw] = 1;
	if(dp[nw] != -1) return dp[nw];

	dp[nw] = inf;
	for(auto i : adj[nw])
		dp[nw] = min(dp[nw], min(max(f(i.first) + 1, f(i.second)), max(f(i.first), f(i.second) + 1)));
	
	return dp[nw] = dp[nw];
}

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	cin >> n >> m >> tp;
	for(int x, y, z, i = 0; i < m; i ++){
		cin >> x >> y >> z;
		adj[z].push_back({x, y});
	}

	cin >> k;
	for(int x, i = 0; i < k; i ++){
		cin >> x;
		sc[x] = 1;
	}

	memset(dp, -1, sizeof(dp));
	f(tp);

	if(dp[tp] >= MX) dp[tp] = -1;
	cout << dp[tp] << "\n";
	return 0;
}
