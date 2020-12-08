#include <bits/stdc++.h>

using namespace std;

long long n,m,nn=0,dsu[100069],dis[100069],cdis=0,dp[100069],mx=-1e18;
vector<long long> al[100069],al2[100069];
bitset<100069> vtd,vtd2;

long long fd(long long x)
{
	if(dsu[x]!=x)
	{
		dsu[x]=fd(dsu[x]);
	}
	return dsu[x];
}

void scc(long long x)
{
	long long i,sz=al[x].size(),l;
	
	vtd[x]=1;
	vtd2[x]=1;
	dis[x]=cdis;
	cdis++;
	for(i=0;i<sz;i++)
	{
		l=al[x][i];
		if(!vtd[l])
		{
			scc(l);
		}
		if(vtd2[fd(l)]&&dis[fd(l)]<=dis[fd(x)])
		{
			dsu[fd(x)]=fd(l);
		}
	}
	cdis--;
	vtd2[x]=0;
}

void dfs(long long x)
{
	long long i,sz=al2[x].size(),l;
	
	vtd[x]=1;
	dp[x]=1;
	for(i=0;i<sz;i++)
	{
		l=al2[x][i];
		if(!vtd[l])
		{
			dfs(l);
		}
		dp[x]=max(dp[x],dp[l]+1);
	}
	mx=max(mx,dp[x]);
}

int main()
{
	long long i,j,k,l,sz;
	
	scanf("%lld%lld",&n,&m);
	for(i=1;i<=n;i++)
	{
		dsu[i]=i;
	}
	for(i=0;i<m;i++)
	{
		scanf("%lld%lld",&k,&l);
		al[k].push_back(l);
	}
	for(i=1;i<=n;i++)
	{
		if(!vtd[i])
		{
			scc(i);
		}
	}
	for(i=1;i<=n;i++)
	{
		sz=al[i].size();
		for(j=0;j<sz;j++)
		{
			l=al[i][j];
			if(fd(l)!=fd(i))
			{
				al2[fd(i)].push_back(fd(l));
			}
		}
	}
	vtd.reset();
	for(i=1;i<=n;i++)
	{
		if(fd(i)==i)
		{
			nn++;
			if(!vtd[i])
			{
				dfs(i);
			}
		}
	}
	if(mx==nn)
	{
		printf("YA\n");
	}
	else
	{
		printf("TIDAK\n");
	}
}
