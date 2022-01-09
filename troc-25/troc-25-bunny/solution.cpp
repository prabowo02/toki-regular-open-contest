#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ld long double

#define debug(x) cout << #x << " => " << x << "\n"

int T, M, N;
int mu[200005], sieve[200005];
vector <int> factors[200005];
int ans[200005], dp[200005];

void mobius(){
	for(int i = 2; i <= 200000; i++){
		if(sieve[i] == 0){
			sieve[i] = i;
			for(int j = i * i; j <= 200000; j += i){
				if(sieve[j] == 0)
					sieve[j] = i;
			}
		}
	}
	mu[1] = 1;
	for(int i = 2; i <= 200000; i++){
		int p = i / sieve[i];
		if(sieve[i] == sieve[p]) mu[i] = 0;
		else mu[i] = -mu[p];
	}
}

void factorize(){
	for(int i = 1; i <= 200000; i++){
        for(int j = i; j <= 200000; j += i){
            factors[j].push_back(i);
        }
    }
}

signed main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	mobius();
	factorize();
	cin >> T >> M;
	ans[1] = dp[1] = 1;
    for(int i = 2; i <= 200000; i++){
    	for(auto j : factors[i]){
    		if(i != j)
    		ans[i] = (ans[i] + dp[j] * mu[j] + M) % M;
    	}
        for(auto j : factors[i]){
        	dp[j] = (dp[j] + ans[i]) % M;
        }
    }
    for(; T--; ){
    	cin >> N;
    	cout << ans[N] % M << "\n";
    }
}