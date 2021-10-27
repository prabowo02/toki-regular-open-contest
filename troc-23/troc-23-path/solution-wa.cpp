#include <bits/stdc++.h>

using namespace std;

long long n;

int main()
{
	long long i,k;
	
	scanf("%lld",&n);
	for(i=1;i<=n*n;i++)
	{
		scanf("%lld%lld",&k,&k);
	}
	for(i=1;i<=n*n;i++)
	{
		printf("%lld%c",i," \n"[i==n*n]);
	}
	scanf("%lld",&n);
	for(i=1;i<=n;i++)
	{
		printf("1\n");
	}
}
