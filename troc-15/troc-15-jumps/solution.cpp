#include <iostream>
#include <queue>
#include <algorithm>
#include <assert.h>
#include <math.h>
using namespace std;

const int MX = 105;

int n, m;
bool vis[MX][MX];

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	cin >> n >> m;
	if(m >= MX){
		cout << "YES\n";

		int sq = (int)sqrt(m);
		if(sq % 2 != m % 2) sq --;

		string s = "";
		for(int i = 0; i < sq; i ++)
			s += 'R';

		for(int i = 0; i < m - sq * sq; i += 2)
			s += "LR";

		cout << s << "\n";
		return 0;
	}

	n = min(n, MX - 1);
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

	for(int i = 0; i < MX; i ++) if(vis[m][i]){
		cout << "YES\n";

		int cr = m, st = i;
		string s = "";

		while(st != 0){
			if(cr - st - st + 1 >= (st == 1 ? 0 : 1) && vis[cr - st - st + 1][st - 1]){
				cr = cr - st - st + 1;
				st --;
				s += 'R';
			}else{
				cr = cr + st + st - 1;
				assert(1 <= cr && cr <= n && vis[cr][st - 1]);
				st --;
				s += 'L';
			}
		}

		reverse(s.begin(), s.end());
		cout << s << "\n";
		return 0;
	}

	cout << "NO\n";
	return 0;
}
