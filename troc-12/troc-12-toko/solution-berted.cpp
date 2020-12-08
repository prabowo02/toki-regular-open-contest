#include <iostream>
#include <set>
#include <vector>
#define pub push_back
#define vi vector<int>
using namespace std;
int n, d, deg[100001] = {};
set<int> s;
vector<vi> adj;
vi ans;
int main()
{
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> d;
	for (int i = 0; i < n; i++) {adj.pub(vi());}
	for (int i = 0; i < n; i++)
	{
		cin >> deg[i];
		for (int j = 0; j < deg[i]; j++)
		{
			int v; cin >> v;
			adj[v - 1].pub(i);
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (deg[i] == 0) {s.insert(i);}
	}
	int ofs = 0;
	for (int i = 0; i < n; i++)
	{
		set<int>::iterator it = s.lower_bound(ofs);
		if (it == s.end())  {it = s.begin();}
		for (const auto &x : adj[*it])
		{
			deg[x]--;
			if (deg[x] == 0) {s.insert(x);}
		}
		ans.pub((*it + n - ofs) % n);
		s.erase(it);
		ofs += n - d;
		ofs %= n;
	}
	for (int i = 0; i < n; i++)
	{
		cout << ans[i];
		if (i < n - 1) {cout << " ";}
	}
	cout << "\n";
	return 0;
}