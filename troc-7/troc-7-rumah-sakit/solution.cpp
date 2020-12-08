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
#define mx 20003


int n, m, k, u, v, w;
long long s[mx], p[20], c[20];
long long dist[16][mx];
int bit[mx];
long long pasien[(1 << 15) + 100], rumahSakit[(1 << 15) + 100];
vector<pair<int, int>> g[mx];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	for(int i = 0; i < n; i++)
		cin >> s[i];
	for(int i = 0; i < m; i++){
		cin >> u >> v >> w;
		u -= 1;
		v -= 1;
		g[u].pb({v, w});
		g[v].pb({u, w});
	}
	for(int i = 0; i < k; i++){
		cin >> p[i] >> c[i];
		p[i] -= 1;
	}
	for(int i = 0; i < k; i++){
		priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
		pq.push({0, p[i]});
		for(int j = 0; j < n; j++)
			dist[i][j] = 1e18;
		dist[i][p[i]] = 0;
		while(!pq.empty()){
			auto now = pq.top();
			pq.pop();
			for(auto x : g[now.s]){
				if(dist[i][x.f] > now.f + x.s){
					dist[i][x.f] = now.f + x.s;
					pq.push({dist[i][x.f], x.f});
				}
			}
		}
	}
	for(int i = 0; i < (1 << k); i++){
		for(int j = 0; j < k; j++){
			if(i & (1 << j)){
				rumahSakit[i] += c[j];
				// debug(i);
				// debug(c[i]);
			}
		}
	}
	long long l = 0, r = 1e18 - 1, ans = -1, mid;
	while(l <= r){
		mid = (l + r) >> 1;
		for(int i = 0; i < (1 << k); i++)
			pasien[i] = 0;
		for(int i = 0; i < n; i++){
			bit[i] = 0;
			for(int j = 0; j < k; j++){
				if(dist[j][i] <= mid)
					bit[i] |= 1 << j;
			}
			pasien[bit[i]] += s[i];
		}
		for(int i = 0; i < k; i++){
			for(int mask = 0; mask < (1 << k); mask++){
				if(mask & (1 << i))
					pasien[mask] += pasien[mask ^ (1 << i)];
			}
		}
		// debug(pasien[(1 << k) - 1]);
		// debug(rumahSakit[(1 << k) - 1]);
		int ya = 1;
		for(int i = 0; i < (1 << k); i++){
			if(rumahSakit[i] < pasien[i])
				ya = 0;
		}
		if(ya){
			// l = mid + 1;
			r = mid - 1;
			ans = mid;
		}
		else l = mid + 1;
	}
	cout << ans << '\n';
}