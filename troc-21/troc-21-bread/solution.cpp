#include <bits/stdc++.h>

using namespace std;

long long n,a[100069],dsu[2][100069],sq[100069];
bitset<100069> wg;

long long fd(long long xx,long long x)
{
	if(dsu[xx][x]!=x)
	{
		dsu[xx][x]=fd(xx,dsu[xx][x]);
	}
	return dsu[xx][x];
}

int main()
{
	long long i,ii,u,k;
	
	scanf("%lld",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%lld%lld",a+i,&k);
		wg[i]=k;
		for(ii=0;ii<2;ii++)
		{
			dsu[ii][i]=i;
		}
	}
	for(i=n;i;i--)
	{
		u=!wg[i]*2-1;
		k=fd(wg[i],a[i]);
		sq[i]=(n+(a[i]-k)*u)%n;
		for(ii=0;ii<2;ii++)
		{
			u=!ii*2-1;
			dsu[ii][fd(ii,k)]=fd(ii,(k+n-u-1)%n+1);
		}
	}
	for(i=1;i<=n;i++)
	{
		printf("%lld%c",sq[i]," \n"[i==n]);
	}
}
