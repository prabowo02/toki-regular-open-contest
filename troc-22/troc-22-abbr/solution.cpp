#include <bits/stdc++.h>

using namespace std;

const long long inf=1e18;
long long n,d,a[100069],am[9][9],dp[100069][9];

int main()
{
	long long i,j,z=-inf;
	char ch;
	
	scanf("%lld%lld",&n,&d);
	for(i=1;i<=n;i++)
	{
		scanf(" %c",&ch);
		a[i]=ch-'1';
	}
	for(i=0;i<d;i++)
	{
		for(j=0;j<d;j++)
		{
			scanf("%lld",&am[i][j]);
		}
		dp[1][i]=-inf;
	}
	dp[1][a[1]]=0;
	for(i=1;i<n;i++)
	{
		dp[1][a[1]]+=am[a[i]][a[i+1]];
	}
	for(i=2;i<n;i++)
	{
		for(j=0;j<d;j++)
		{
			dp[i][j]=dp[i-1][j];
		}
		for(j=0;j<d;j++)
		{
			dp[i][a[i]]=max(dp[i][a[i]],dp[i-1][j]-am[j][a[i]]);
		}
	}
	for(i=0;i<d;i++)
	{
		z=max(z,dp[n-1][i]-am[i][a[n]]);
	}
	printf("%lld\n",z);
}
