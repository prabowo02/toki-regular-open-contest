#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;

#define ll long long

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	ll GCD, LCM;
	cin >> GCD >> LCM;

	if(LCM % GCD != 0){
		cout << "-1 -1\n";
		return 0;
	}

	ll DV = LCM / GCD;

	ll ans = 1000000000000000000ll;
	ll lf = -1, rg = -1;
	for(ll i = (ll)sqrt(DV); i >= 1; i --) if(DV % i == 0){
		if(__gcd(DV / i, i) == 1ll){
			ans = DV / i + i;
			lf = DV / i;
			rg = i;
		}
	}

	cout << lf * 1ll * GCD << " " << rg * 1ll * GCD << endl;
	return 0;
}