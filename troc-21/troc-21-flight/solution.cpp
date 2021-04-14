#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

const long long inf=1e18;
long long n,ps[200069],dp[2][2][200069];

bool cmp(long long x,long long y,long long x2,long long y2)
{
	return mp(x/y,x%y*y2)<=mp(x2/y2,x2%y2*y);
}

bool chk(long long ky,long long x,long long y,long long y2)
{
	long long u=!ky*2-1;
	
	return cmp((ps[y2]-ps[x])*u,x-y2,(ps[y]-ps[x])*u,x-y);
}

long long f(long long x,long long w)
{
	return x*w+ps[x];
}

struct segtree
{
	long long l,r,nn[2];
	vector<long long> sk[2];
	segtree *p[2];
	
	void bd(long long lh,long long rh)
	{
		long long i,ii;
		
		l=lh;
		r=rh;
		if(l<r)
		{
			long long md=(l+r)/2;
			
			for(ii=0;ii<2;ii++)
			{
				p[ii]=new segtree;
				p[ii]->bd(!ii?lh:md+1,!ii?md:r);
			}
		}
		for(ii=0;ii<2;ii++)
		{
			nn[ii]=0;
			for(i=l;i<=r;i++)
			{
				for(;nn[ii]>=2&&chk(ii,i,sk[ii][nn[ii]-1],sk[ii][nn[ii]-2]);sk[ii].pop_back(),nn[ii]--);
				sk[ii].push_back(i);
				nn[ii]++;
			}
		}
	}
	long long qr(long long ky,long long lh,long long rh,long long w)
	{
		long long u=!ky*2-1;
		
		if(l>rh||r<lh)
		{
			return inf*u;
		}
		else if(l>=lh&&r<=rh)
		{
			long long md,zz;
			
			for(zz=0,lh=1,rh=nn[ky]-1;lh<=rh;)
			{
				md=(lh+rh)/2;
				if(f(sk[ky][md],w)*u<=f(sk[ky][md-1],w)*u)
				{
					zz=md;
					lh=md+1;
				}
				else
				{
					rh=md-1;
				}
			}
			return f(sk[ky][zz],w);
		}
		else
		{
			return min(p[0]->qr(ky,lh,rh,w)*u,p[1]->qr(ky,lh,rh,w)*u)*u;
		}
	}
}
sg;

int main()
{
	long long t,rr,i,ii,jj,u,uu,k,l,w,z;
	
	scanf("%lld%lld",&n,&t);
	n++;
	for(i=2;i<=n;i++)
	{
		scanf("%lld",ps+i);
		ps[i]+=ps[i-1];
	}
	for(ii=0;ii<2;ii++)
	{
		u=!ii*2-1;
		for(jj=0;jj<2;jj++)
		{
			uu=!jj*2-1;
			dp[ii][jj][(n+1)*jj]=inf*u;
			for(i=1+(n-1)*jj;i&&i<=n;i+=uu)
			{
				dp[ii][jj][i]=min(dp[ii][jj][i-uu]*u,ps[i]*u)*u;
			}
		}
	}
	sg.bd(1,n);
	for(rr=0;rr<t;rr++)
	{
		scanf("%lld%lld%lld",&k,&l,&w);
		k++;
		l++;
		z=0;
		for(ii=0;ii<2;ii++)
		{
			u=!ii*2-1;
			z=min(min(dp[ii][0][k-1]*u,(dp[ii][1][l+1]+w*(l-k+1))*u),(sg.qr(ii,k,l,w)-w*(k-1))*u)*u-z;
		}
		printf("%lld\n",z);
	}
}
