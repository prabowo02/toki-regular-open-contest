#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	ll n, m; scanf("%lld %lld", &n, &m);
	ll ans=2ll*(
		(n - 2ll) * 1ll * (n + 1ll) +
		(m - 2ll) * 1ll * (m + 1ll));
	printf("%lld\n", ans); return 0;
}