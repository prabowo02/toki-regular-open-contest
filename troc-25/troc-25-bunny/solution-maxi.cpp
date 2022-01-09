#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define ll long long
#define endl "\n"
const int MX = 200005;

int tc;
ll mod;

ll mob[MX];
vector<int> fact[MX];

ll dp[MX], ans[MX];

int main(){
	cin.tie(0) -> sync_with_stdio(0);

	cin >> tc >> mod;

	mob[1] = 1;
	for(int i = 2; i < MX; i ++){
		if(mob[i] < 0) mob[i] = 0;
		else if(mob[i] == 0){
			for(int j = 2 * i; j < MX; j += i)
				mob[j] ++;
			for(ll j = i * 1ll * i; j < MX; j += i * 1ll * i)
				mob[j] = -mod;
			mob[i] = mod - 1;
		}else{
			if(mob[i] & 1) mob[i] = mod - 1;
			else mob[i] = 1;
		}
	}

	for(int i = 1; i < MX; i ++)
		for(int j = i; j < MX; j += i)
			fact[j].push_back(i);

	ans[1] = dp[1] = 1;
	for(int i = 2; i < MX; i ++){
		for(int j : fact[i]) if(i != j)
			(ans[i] += (dp[j] * 1ll * mob[j]) % mod) %= mod;
		for(int j : fact[i])
			(dp[j] += ans[i]) %= mod;
	}

	for(int x; tc --;){
		cin >> x;
		cout << ans[x] << endl;
	}

	return 0;
}