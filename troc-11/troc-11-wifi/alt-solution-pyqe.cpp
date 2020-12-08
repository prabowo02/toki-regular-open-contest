#include <bits/stdc++.h>

using namespace std;

long long n,m,a[100069];

int main()
{
	long long i,mn=1e18;
	
	scanf("%lld%lld",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",a+i);
	}
	sort(a+1,a+n+1);
	for(i=m;i<=n;i++)
	{
		mn=min(mn,a[i]-a[i-m+1]);
	}
	printf("%lld\n",mn);
}
