#include <bits/stdc++.h>

using namespace std;

const long long dv=998244353;
long long n,dp[3][2069][2069][2],tmp[3][2069][2];
vector<long long> al[2069];

void dfs(long long x)
{
	long long i,j,r,ii,jj,sz=al[x].size(),l,w,p,p2,e;
	
	for(i=1;i<=n;i++)
	{
		dp[0][x][i][0]=1;
		for(j=1;j<3;j++)
		{
			dp[j][x][i][0]=dp[j-1][x][i][0]*i%dv;
		}
	}
	for(i=0;i<sz;i++)
	{
		l=al[x][i];
		dfs(l);
		for(j=0;j<3;j++)
		{
			for(r=1;r<=n;r++)
			{
				for(ii=0;ii<2;ii++)
				{
					for(p=0;p<3-j;p++)
					{
						for(p2=r-1;p2<=r+1;p2++)
						{
							for(jj=0;jj<2;jj++)
							{
								w=dp[j][x][r][ii]*dp[p][l][p2][jj]*(1+(j==1&&p==1));
								if(jj||r==p2-1)
								{
									e=ii||p2==r-1;
									tmp[j+p][r][e]=(tmp[j+p][r][e]+w)%dv;
								}
								if(r==1&&p2==1)
								{
									tmp[j+p][r][1]=(tmp[j+p][r][1]+w)%dv;
								}
							}
						}
					}
				}
			}
		}
		for(j=0;j<3;j++)
		{
			for(r=1;r<=n;r++)
			{
				for(ii=0;ii<2;ii++)
				{
					dp[j][x][r][ii]=tmp[j][r][ii];
					tmp[j][r][ii]=0;
				}
			}
		}
	}
}

int main()
{
	long long i,k,z=0;
	
	scanf("%lld",&n);
	for(i=2;i<=n;i++)
	{
		scanf("%lld",&k);
		al[k].push_back(i);
	}
	dfs(1);
	for(i=1;i<=n;i++)
	{
		z=(z+dp[2][1][i][1])%dv;
	}
	z=(z+n*n)*2%dv;
	printf("%lld\n",z);
}
