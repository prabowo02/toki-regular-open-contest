#include <bits/stdc++.h>

using namespace std;

long long n,m,a[200069];

int main()
{
	long long i,z;
	
	scanf("%lld%lld",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",a+i);
	}
	sort(a+1,a+n+1);
	z=a[1]+m-a[n];
	for(i=2;i<=n;i++)
	{
		z=max(z,a[i]-a[i-1]);
	}
	printf("%lld\n",m-z);
}
