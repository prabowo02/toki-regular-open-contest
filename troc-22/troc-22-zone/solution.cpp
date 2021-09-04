#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

const long long inf=1e18;
long long n,m,d,pst[100069],a[100069],nr[100069],sq[100069];
vector<pair<long long,long long>> al[100069];
priority_queue<pair<long long,long long>> pq;

int main()
{
	long long i,k,l,w,sz,ww,lh,rh,md,zz,c,z;
	
	scanf("%lld%lld",&n,&m);
	for(i=0;i<m;i++)
	{
		scanf("%lld%lld%lld",&k,&l,&w);
		al[k].push_back({l,w});
		al[l].push_back({k,w});
	}
	scanf("%lld",&d);
	for(i=1;i<=d;i++)
	{
		scanf("%lld%lld",pst+i,a+i);
		sq[i]=inf;
	}
	for(lh=1,rh=n;lh<=rh;)
	{
		md=(lh+rh)/2;
		for(i=1;i<=n;i++)
		{
			nr[i]=inf;
			if(i<=md)
			{
				pq.push({0,i});
				nr[i]=0;
			}
		}
		for(;!pq.empty();)
		{
			w=-pq.top().fr;
			k=pq.top().sc;
			pq.pop();
			if(w>nr[k])
			{
				continue;
			}
			sz=al[k].size();
			for(i=0;i<sz;i++)
			{
				l=al[k][i].fr;
				ww=al[k][i].sc;
				if(w+ww<nr[l])
				{
					pq.push({-w-ww,l});
					nr[l]=w+ww;
				}
			}
		}
		c=0;
		for(i=1;i<=d;i++)
		{
			if(nr[pst[i]]<=a[i])
			{
				c++;
				sq[i]=min(sq[i],md);
			}
		}
		if(c==d)
		{
			zz=md;
			rh=md-1;
		}
		else
		{
			lh=md+1;
		}
	}
	for(i=1;i<=d;i++)
	{
		if(sq[i]==zz)
		{
			z=i;
		}
	}
	printf("%lld\n",z);
}
