#include <bits/stdc++.h>

using namespace std;

long long n,m,dp[100069][2],dv=1e9+7;

int main()
{
	long long i,sm=1;
	
	scanf("%lld%lld",&n,&m);
	dp[0][0]=1;
	for(i=1;i<=n;i++)
	{
		dp[i][0]=(dp[i-1][0]+dp[i-1][1])*(m-1)%dv;
		dp[i][1]=dp[i-1][0];
		sm=sm*(m-1)%dv;
	}
	printf("%lld\n",(dp[n][0]+dp[n][1]+dv-sm)%dv);
}
