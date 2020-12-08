#include <iostream>
#include <queue>
using namespace std;

const int MX = 2005;

int n, m, tp, k;
vector<int> adj[MX], li[MX][MX];
bool sc[MX];
int dist[MX];
bool vis[MX];

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	cin >> n >> m >> tp;
	for(int x, y, z, i = 0; i < m; i ++){
		cin >> x >> y >> z;
		li[x][z].push_back(y);
		li[y][z].push_back(x);
		adj[x].push_back(z);
		adj[y].push_back(z);
	}

	queue<int> bfs;
	for(int i = 1; i <= n; i ++)
		dist[i] = MX * MX;

	cin >> k;
	for(int x, i = 0; i < k; i ++){
		cin >> x;
		dist[x] = 1; sc[x] = 1;
		bfs.push(x);
	}

	for(; bfs.size();){
		int nw = bfs.front(); bfs.pop();
		if(vis[nw]) continue;
		vis[nw] = 1;

		for(int nx : adj[nw]){
			for(int per : li[nw][nx]){
				if(vis[per] || sc[per]){
					dist[nx] = min(dist[nx], min(max(dist[nw], dist[per] + 1), max(dist[nw] + 1, dist[per])));
					bfs.push(nx);
				}
			}
		}
	}

	if(dist[tp] == MX * MX || (!vis[tp])) dist[tp] = -1;
	cout << dist[tp] << "\n";
	return 0;
}
