#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

const int ma=1e9;
int n,as[90069],fw[369],fi;
pair<int,int> a[90069];

struct segtree
{
	int l,r,sm;
	segtree *p[2];
	
	void bd(int lh,int rh)
	{
		l=lh;
		r=rh;
		sm=0;
		p[0]=0;
	}
	void blc()
	{
		if(!p[0])
		{
			int ii,md=(l+r)/2;
			
			for(ii=0;ii<2;ii++)
			{
				p[ii]=new segtree;
				p[ii]->bd(!ii?l:md+1,!ii?md:r);
			}
		}
	}
	void ud(int x,int w)
	{
		if(l>x||r<x);
		else if(l>=x&&r<=x)
		{
			sm+=w;
		}
		else
		{
			int ii;
			
			blc();
			for(ii=0;ii<2;ii++)
			{
				p[ii]->ud(x,w);
			}
			sm=p[0]->sm+p[1]->sm;
		}
	}
	int qr(int lh,int rh)
	{
		if(l>rh||r<lh)
		{
			return 0;
		}
		else if(l>=lh&&r<=rh)
		{
			return sm;
		}
		else
		{
			blc();
			return p[0]->qr(lh,rh)+p[1]->qr(lh,rh);
		}
	}
}
sg[369];

bool cmp(int x,int y)
{
	return a[x]<a[y];
}

void ud(int x,int w)
{
	for(fi=x;fi<=n;fi+=fi&-fi)
	{
		fw[fi]+=w;
	}
}

int qr(int x)
{
	int z=0;
	
	for(fi=x;fi;fi-=fi&-fi)
	{
		z+=fw[fi];
	}
	return z;
}

int main()
{
	int t,rr,i,k,y,x,y2,x2;
	
	scanf("%d",&n);
	for(i=1;i<=n*n;i++)
	{
		scanf("%d%d",&y,&x);
		y=(long long)(y-(y==ma))*n/ma+1;
		if(y%2==0)
		{
			x=ma-x;
		}
		a[i]={y,x};
		as[i]=i;
	}
	sort(as+1,as+n*n+1,cmp);
	for(i=1;i<=n*n;i++)
	{
		printf("%d%c",as[i]," \n"[i==n*n]);
	}
	for(i=1;i<=n;i++)
	{
		sg[i].bd(0,ma);
	}
	for(i=1;i<=n*n;i++)
	{
		y=a[i].fr;
		x=a[i].sc;
		ud(y,1);
		sg[y].ud(x,1);
	}
	scanf("%d",&t);
	for(rr=0;rr<t;rr++)
	{
		scanf("%d%d%d",&k,&y,&x);
		y=(long long)(y-(y==ma))*n/ma+1;
		if(y%2==0)
		{
			x=ma-x;
		}
		y2=a[k].fr;
		x2=a[k].sc;
		ud(y2,-1);
		sg[y2].ud(x2,-1);
		a[k]={y,x};
		ud(y,1);
		sg[y].ud(x,1);
		printf("%d\n",qr(y-1)+sg[y].qr(0,x));
	}
}
