#include <iostream>
#include <algorithm>
using namespace std;

const int MX = 200005;

int n, v[MX], pre[MX], nex[MX], last[MX];

bool dnc(int lf, int rg){
	if(lf == rg) return false;
	for(int i = 0; i < rg - lf; i ++){
		if(pre[lf + i] < lf && nex[lf + i] >= rg)
			return dnc(lf, lf + i) || dnc(lf + i + 1, rg);
	}
	return true;
}

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	cin >> n;
	for(int i = 0; i < n; i ++)
		cin >> v[i];

	for(int i = 0; i < MX; i ++) last[i] = -1;
	for(int i = 0; i < n; i ++){
		pre[i] = last[v[i]];
		last[v[i]] = i;
	}
	for(int i = 0; i < MX; i ++) last[i] = n;
	for(int i = n - 1; i >= 0; i --){
		nex[i] = last[v[i]];
		last[v[i]] = i;
	}

	if(dnc(0, n)) cout << "NO\n";
	else cout << "YES\n";

	return 0;
}