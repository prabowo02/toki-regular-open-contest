#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

const long long ma=1e9,inf=1e18;
long long n,d,ps[100069],dsu[100069],cc[100069],dp[100069],lz[100069];
vector<long long> al[100069];
vector<pair<long long,long long>> vl[100069];

long long f(pair<long long,long long> x,long long w)
{
	return x.fr*w+x.sc;
}

struct lichao
{
	long long l,r;
	pair<long long,long long> mn;
	lichao *p[2];
	
	void bd(long long lh,long long rh)
	{
		l=lh;
		r=rh;
		mn={0,inf};
		p[0]=0;
	}
	void blc()
	{
		if(!p[0])
		{
			long long ii,md=(l+r)/2;
			
			for(ii=0;ii<2;ii++)
			{
				p[ii]=new lichao;
				p[ii]->bd(!ii?l:md+1,!ii?md:r);
			}
		}
	}
	void ins(pair<long long,long long> x)
	{
		long long ii,md=(l+r)/2;
		
		if(f(x,md)<f(mn,md))
		{
			swap(mn,x);
		}
		blc();
		for(ii=0;ii<2;ii++)
		{
			if(f(x,l)<f(mn,l))
			{
				p[ii]->ins(x);
			}
			swap(l,r);
		}
	}
	long long qr(long long x)
	{
		if(l>x||r<x)
		{
			return inf;
		}
		else
		{
			long long ii,k=f(mn,x);
			
			if(l<r&&p[0])
			{
				for(ii=0;ii<2;ii++)
				{
					k=min(k,p[ii]->qr(x));
				}
			}
			return k;
		}
	}
}
lch[100069];

long long fd(long long x)
{
	if(dsu[x]!=x)
	{
		dsu[x]=fd(dsu[x]);
	}
	return dsu[x];
}

void jo(long long x,long long y)
{
	long long i,sz,sl,wg;
	
	x=fd(x);
	y=fd(y);
	if(cc[y]>cc[x])
	{
		swap(x,y);
	}
	if(cc[y])
	{
		lz[x]+=dp[y];
		lz[y]+=dp[x];
		sz=vl[y].size();
		for(i=0;i<sz;i++)
		{
			sl=vl[y][i].fr;
			wg=vl[y][i].sc;
			lch[x].ins({sl,wg+lz[y]-lz[x]});
			vl[x].push_back({sl,wg+lz[y]-lz[x]});
		}
	}
	dp[x]+=dp[y];
	cc[x]+=cc[y];
	dsu[y]=x;
}

void dfs(long long x)
{
	long long i,sz=al[x].size(),l,sl,wg;
	
	dsu[x]=x;
	lch[x].bd(0,ma);
	for(i=0;i<sz;i++)
	{
		l=al[x][i];
		dfs(l);
		jo(x,l);
	}
	sl=-ps[x]*2;
	wg=dp[fd(x)]+ps[x]*ps[x];
	lch[fd(x)].ins({sl,wg-lz[fd(x)]});
	vl[fd(x)].push_back({sl,wg-lz[fd(x)]});
	cc[fd(x)]++;
	dp[fd(x)]=lch[fd(x)].qr(ps[x])+ps[x]*ps[x]+d+lz[fd(x)];
}

int main()
{
	long long i,k;
	
	scanf("%lld%lld",&n,&d);
	for(i=2;i<=n;i++)
	{
		scanf("%lld%lld",&k,ps+i);
		al[k].push_back(i);
		ps[i]+=ps[k];
	}
	dfs(1);
	printf("%lld\n",dp[fd(1)]);
}
