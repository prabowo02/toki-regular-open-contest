#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

long long n,m=0,dsu[2069];
pair<long long,long long> ed[500069],as[500069];

long long fd(long long x)
{
	if(dsu[x]!=x)
	{
		dsu[x]=fd(dsu[x]);
	}
	return dsu[x];
}

int main()
{
	long long i,j,k,l,w,p;
	
	scanf("%lld",&n);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			scanf("%lld",&k);
			if(i<j)
			{
				m++;
				ed[m]={i,j};
				as[m]={k,m};
			}
		}
	}
	sort(as+1,as+m+1);
	for(i=1;i<=n*2;i++)
	{
		dsu[i]=i;
	}
	for(i=1;i<=m;i++)
	{
		w=as[i].fr;
		p=as[i].sc;
		k=ed[p].fr;
		l=ed[p].sc;
		if(fd(k)==fd(l))
		{
			break;
		}
		dsu[fd(n+l)]=fd(k);
		dsu[fd(l)]=fd(n+k);
	}
	printf("%lld\n",w);
}
