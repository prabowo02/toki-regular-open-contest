#include <iostream>
using namespace std;

#define ll long long
const ll mod = 1e9 + 7;

ll n, m, k;
ll pw(ll b, ll e){
	ll r = 1ll; b %= mod;
	for(; e > 0; e /= 2, b = (b * 1ll * b) % mod)
		if(e % 2 == 1) r = (r * 1ll * b) % mod;
	return r;
}

int main(){
	cin >> n >> m >> k;
	cout << pw(k + 1, n + m - 1) << endl;
	return 0;
}