#include <bits/stdc++.h>

using namespace std;

long long n,a[200069];

int main()
{
	long long t,rr,i,k,l,w,sm,mn,mx;
	
	scanf("%lld%lld",&n,&t);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",a+i);
	}
	for(rr=0;rr<t;rr++)
	{
		scanf("%lld%lld%lld",&k,&l,&w);
		mn=0;
		mx=0;
		sm=0;
		for(i=1;i<=n;i++)
		{
			sm+=a[i]+w*(i>=k&&i<=l);
			mn=min(mn,sm);
			mx=max(mx,sm);
		}
		printf("%lld\n",mx-mn);
	}
}
