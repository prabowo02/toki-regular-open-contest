#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

long long n,nn=0,zs=0;
pair<long long,pair<long long,long long>> sq[100069];

long long f(long long x)
{
	return (x-1)*(x-2)*(x-3)/6*x;
}

int main()
{
	long long i,k,l;
	
	scanf("%lld",&n);
	for(;n>=4;n-=f(k))
	{
		for(i=1;f(i+1)<=n;i++);
		k=i;
		l=nn;
		for(i=0;i<k;i++)
		{
			nn++;
			zs++;
			sq[zs]={nn,{l+1,l+k}};
		}
	}
	for(i=0;i<n;i++)
	{
		zs++;
		sq[zs]={nn+1,{nn+2,nn+4}};
		nn+=4;
	}
	printf("%lld\n",zs);
	for(i=1;i<=zs;i++)
	{
		printf("%lld %lld %lld\n",sq[i].fr,sq[i].sc.fr,sq[i].sc.sc);
	}
}
