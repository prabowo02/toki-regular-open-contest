#include <iostream>
#include <vector>
using namespace std;

#define endl "\n"

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	int n; cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i ++)
		cin >> a[i];

	vector<pair<int, int> > edge(n);
	for(int i = 1; i < n; i ++)
		cin >> edge[i].first >> edge[i].second;

	int cnt = 0;
	for(int i = 1; i <= n; i ++)
		cnt += a[i];

	if(n == 2){
		if(cnt == 1) cout << "YES\n";
		else cout << "NO\n";
	}else{
		if(cnt == 0) cout << "NO\n";
		else cout << "YES\n";
	}

	return 0;
}