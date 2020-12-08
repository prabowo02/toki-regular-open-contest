#include <iostream>
#include <queue>
using namespace std;

const int MX = 55;

int n, m;
bool vis[MX][MX];

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	cin >> n >> m;
	if(n >= 49){
		cout << "YES\n";
		return 0;
	}

	queue<pair<int, int> > bfs;
	bfs.push({0, 0});

	while(bfs.size()){
		int nw = bfs.front().first, stp = bfs.front().second;
		bfs.pop();

		if(vis[nw][stp]) continue;
		vis[nw][stp] = 1;
		if(nw == m) break;

		int nx = nw + (2 * stp + 1);
		if(1 <= nx && nx <= n)
			bfs.push({nx, stp + 1});

		nx = nw - (2 * stp + 1);
		if(1 <= nx && nx <= n)
			bfs.push({nx, stp + 1});
	}

	bool ans = 0;
	for(int i = 0; i < MX; i ++)
		ans |= vis[m][i];

	if(ans) cout << "YES\n";
	else cout << "NO\n";

	return 0;
}