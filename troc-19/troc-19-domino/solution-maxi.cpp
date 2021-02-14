#include <iostream>
using namespace std;

#define endl "\n"
#define ll long long
const ll mod = 998244353;

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	int n, m; 
	cin >> n >> m;

	ll rs = 1ll;
	for(int i = 1; i < n * m; i ++)
		(rs *= 2) %= mod;

	cout << rs << endl;
	return 0;
}