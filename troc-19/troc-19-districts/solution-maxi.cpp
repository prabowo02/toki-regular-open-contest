#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

#define endl "\n"
#define ll long long
const int MXN = 100005;
const int MXA = 1000005;

vector<pair<int, int> > seg[2][MXA];
ll val[MXN];
int dsu[MXN];

int find(int nw){
	return dsu[nw] = (dsu[nw] == nw ? nw : find(dsu[nw]));
}

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	int n; cin >> n;
	if(n == 1){
		cout << -1 << endl;
		return 0;
	}

	for(int x1, y1, x2, y2, i = 1; i <= n; i ++){
		cin >> x1 >> y1 >> x2 >> y2;
		val[i] = (x2 - x1) * 1ll * (y2 - y1);

		seg[0][y1].push_back({x1, i});
		seg[0][y1].push_back({x2, -i});

		seg[0][y2].push_back({x1, i});
		seg[0][y2].push_back({x2, -i});

		seg[1][x1].push_back({y1, i});
		seg[1][x1].push_back({y2, -i});

		seg[1][x2].push_back({y1, i});
		seg[1][x2].push_back({y2, -i});		
	}

	vector<pair<pair<int, int>, ll> > edge;
	for(int tp = 0; tp < 2; tp ++){
		for(int i = 1; i < MXA; i ++){
			sort(seg[tp][i].begin(), seg[tp][i].end());

			int u = -1, v = -1;
			for(pair<int, int> j : seg[tp][i]){
				if(j.second > 0){
					if(u < 0) u = j.second;
					else v = j.second;

					if(!(u < 0 || v < 0))
						edge.push_back({{u, v}, abs(val[u] - val[v])});
				}else{
					if(u == -j.second) u = -1;
					else v = -1;
				}
			}
		}
	}

	sort(edge.begin(), edge.end(), 
		[&](pair<pair<int, int>, ll> a, pair<pair<int, int>, ll> b){
			return a.second < b.second;
		});

	iota(dsu, dsu + MXN, 0);
	ll sum = 0ll, mx = 0ll;

	for(pair<pair<int, int>, ll> i : edge){
		int u = i.first.first, v = i.first.second;
		ll wt = i.second;

		int fu = find(u), fv = find(v);
		if(fu != fv){
			dsu[fu] = fv;
			sum += wt;
			mx = wt;
		}
	}

	int cc = 0;
	for(int i = 1; i <= n; i ++)
		if(dsu[i] == i) cc ++;

	if(cc == 1) sum -= mx;
	if(cc > 2) cout << -1 << endl;
	else cout << sum << endl;

	return 0;
}