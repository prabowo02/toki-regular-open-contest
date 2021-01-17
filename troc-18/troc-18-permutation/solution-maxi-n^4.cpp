#include <stdio.h>
#include <functional>
#include <vector>
#include <bitset>
#include <algorithm>
#include <numeric>
using namespace std;

#define ll long long
const int MX = 305;
const ll mod = 998244353;

int n;
vector<int> v;
bitset<MX> vis;
ll C[MX][MX], dp[MX][MX];

vector<int> par;
inline int find(int nw){
	if(par[nw] == nw) return nw;
	par[nw] = find(par[nw]);
	return par[nw];
}

int main(){
	scanf("%d", &n);
	v.resize(n);
	for(int i = 0; i < n; i ++)
		scanf("%d", &v[i]);

	C[0][0] = 1;
	for(int i = 1; i < MX; i ++)
	{
		C[i][0] = 1;
		for(int j = 1; j <= i; j ++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	}

	for(int i = n - 1; i >= 0; i --){
		for(int j = i; j < n; j ++){
			if(i == j) dp[i][j] = 1;
			else{
				vector<int> q, on;
				for(int k = i; k <= j; k ++)
					q.push_back(v[k]);
				sort(q.begin(), q.end());

				for(int k = i; k < j; k ++){
					on.assign(n + 1, 0);
					for(int l = i; l < k; l ++)
						on[q[l - i]] = 1;
					on[q[k + 1 - i]] = 1;

					bool ok = 1;
					for(int l = i; l <= k; l ++)
						if(!on[v[l]]){
							ok = 0; 
							break;
						}

					if(ok)
						(dp[i][j] += (dp[i][k] * 1ll * dp[k + 1][j]) % mod * 1ll * C[j - i - 1][k - i] % mod) %= mod;
				}
			}
		}
	}

	printf("%lld\n", dp[0][n - 1]);
	return 0;
}
