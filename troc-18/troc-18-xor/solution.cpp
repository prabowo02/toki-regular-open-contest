#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

#define ll long long
const ll mod = 998244353;

int n, x; 
vector<int> v;
vector<ll> dp[2];

ll solve(int x, vector<int> v){
	int max_id = 0;
	for(int i = 1; i < n; i ++)
		if(v[i] > v[max_id]) max_id = i;
	swap(v[max_id], v[n - 1]);

	int t = 1;
	for(; 2 * t <= v[n - 1] + 1; t *= 2);
	if(x >= 2 * t) return 0;
	
	for(int i = 0; i < 2; i ++) dp[i].assign(n, 0);
	dp[0][0] = 1ll;
	for(int i = 0; i < n - 1; i ++){
		for(int j = 0; j < 2; j ++){
			(dp[j][i + 1] += (dp[j][i] * 1ll * min(v[i] + 1, t)) % mod) %= mod;
			(dp[1 - j][i + 1] += (dp[j][i] * 1ll * max(v[i] - t + 1, 0)) % mod) %= mod;
		}
	}

	ll ans = 0ll;
	if(0 <= x && x < t) ans = dp[0][n - 1];
	else ans = dp[1][n - 1];

	if(v[n - 1] >= t){
		v[n - 1] -= t;
		(ans += solve(x ^ t, v)) %= mod;
	}

	return ans;
}

int main(){
	scanf("%d %d", &n, &x);
	v.resize(n);
	for(int i = 0; i < n; i ++)
		scanf("%d", &v[i]);

	printf("%lld\n", solve(x, v));
	return 0;
}
