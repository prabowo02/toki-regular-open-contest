#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

long long n,m,d,wg[20],dp[21][1ll<<20],sq[200069],inf=1e18;
pair<long long,long long> a[200069],ex[20];

int main()
{
	long long i,j,y,x,w,ly,lx,mk;
	
	scanf("%lld%lld%lld",&n,&m,&d);
	for(i=1;i<=n;i++)
	{
		scanf("%lld%lld",&y,&x);
		a[i]={y,x};
		sq[i]=inf;
	}
	for(i=0;i<m;i++)
	{
		scanf("%lld%lld%lld",&y,&x,wg+i);
		ex[i]={y,x};
	}
	dp[0][0]=n;
	for(i=1;i<=n;i++)
	{
		mk=0;
		for(j=0;j<m;j++)
		{
			ly=a[i].fr-ex[j].fr;
			lx=a[i].sc-ex[j].sc;
			mk|=(ly*ly+lx*lx<=d*d)<<j;
		}
		dp[0][mk]--;
	}
	for(i=1;i<=m;i++)
	{
		for(mk=0;mk<1ll<<m;mk++)
		{
			dp[i][mk]=dp[i-1][mk]+dp[i-1][mk^1ll<<i-1]*(mk>>i-1&1);
		}
	}
	for(mk=0;mk<1ll<<m;mk++)
	{
		w=0;
		for(i=0;i<m;i++)
		{
			w+=wg[i]*!(mk>>i&1);
		}
		sq[dp[m][mk]]=min(sq[dp[m][mk]],w);
	}
	for(i=n-1;i;i--)
	{
		sq[i]=min(sq[i],sq[i+1]);
	}
	for(i=1;i<=n;i++)
	{
		if(sq[i]==inf)
		{
			sq[i]=-1;
		}
		printf("%lld\n",sq[i]);
	}
}
