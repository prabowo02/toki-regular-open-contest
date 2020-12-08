#include <iostream>
#include <map>
#define ll long long
#define snd second
#define fst first
const ll md = (1e9) + 7;
using namespace std;
const int MX = 100000;
ll fkt[100001]={};
inline ll pw(ll b,ll e)
{
	e += md-1;e %= md-1;
	ll t = 1;
	while (e > 0)
	{
		if (e&1) {t *= b; t %= md;}
		b *= b; b %= md; e>>=1;
	}
	return t;
}
inline ll comb(ll n,ll r)
{
	if (n < r) {return 0;}
	return ((fkt[n] * pw(fkt[n-r],-1))%md * pw(fkt[r],-1))%md;
}
ll n,k,freq[100001]={},out = 0,dp[100001];
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>k;
	fkt[0] = 1;
	for (int i = 1; i <= n; i++) {fkt[i] = (fkt[i-1] * i) % md;}
	for (int i = 0;i < n;i++) {int x;cin>>x;freq[x]++;}
	for (int i = 1; i * i <= k; i++)
	{
		if (k % i == 0)
		{
			for (int j = MX - MX % (k / i); j ; j -= k / i) 
			{
				ll amnt = 0;
				dp[j] = 0;
				for (int k = j; k <= MX; k += j)
				{
					amnt += freq[k];
					dp[j] += (md - dp[k])%md;
					dp[j] %= md;
				}
				dp[j] += comb(amnt,i);
				dp[j] %= md;
			}
			out = (out + dp[k / i]) % md;
			if (i * i < k)
			{
				for (int j = MX - MX % i; j ; j -= i) 
				{
					ll amnt = 0;
					dp[j] = 0;
					for (int k = j; k <= MX; k += j)
					{
						amnt += freq[k];
						dp[j] += (md - dp[k])%md;
						dp[j] %= md;
					}
					dp[j] += comb(amnt,k/i);
					dp[j] %= md;
				}
				out = (out + dp[i]) % md;
			}
		}
	}
	cout<<out<<"\n";
	return 0;
}