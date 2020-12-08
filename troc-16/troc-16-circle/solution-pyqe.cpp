#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

long long n,m=0,nn=0,nm[2],ub=1e14,a[100069],pr[100069],dg[100069],od[100069],pst[100069],nr[2][100069],ps[2][100069],z=0,dv=1e9+7,inf=1e18;
pair<pair<long long,long long>,long long> ed[200069];
pair<long long,long long> al[400069];
bitset<100069> vtd;
priority_queue<pair<long long,long long>> pq;
pair<long long,pair<long long,long long>> as[2][100069];

bool cmp(pair<pair<long long,long long>,long long> x,pair<pair<long long,long long>,long long> y)
{
	return mp(x.fr.sc,-x.fr.fr)<mp(y.fr.sc,-y.fr.fr);
}

void dij(long long ky,long long x)
{
	long long i,k,l,w,ww;
	
	for(i=1;i<=nn;i++)
	{
		nr[ky][a[i]]=inf;
	}
	pq.push({0,x});
	nr[ky][x]=0;
	for(;!pq.empty();)
	{
		w=-pq.top().fr;
		k=pq.top().sc;
		pq.pop();
		if(w>nr[ky][k])
		{
			continue;
		}
		for(i=1;i<=dg[k];i++)
		{
			l=al[od[k]+i].fr;
			ww=al[od[k]+i].sc;
			if(w+ww<nr[ky][l])
			{
				pq.push({-w-ww,l});
				nr[ky][l]=w+ww;
			}
		}
	}
}

void dnc(long long lb,long long rb)
{
	long long i,j,ii,k,l,w,mn=inf,p[2],e;
	
	for(i=lb;i<=rb;i++)
	{
		k=ed[i].fr.fr;
		l=ed[i].fr.sc;
		w=ed[i].sc;
		for(ii=0;ii<2;ii++)
		{
			dg[k]++;
			al[od[k]+dg[k]]={l,w};
			if(!vtd[k])
			{
				vtd[k]=1;
				nn++;
				a[nn]=k;
			}
			swap(k,l);
		}
	}
	sort(a+1,a+nn+1);
	for(i=1;i<=nn;i++)
	{
		pst[a[i]]=i;
	}
	if(nn==3)
	{
		for(i=1;i<=nn;i++)
		{
			dij(0,a[i]);
			for(j=i+1;j<=nn;j++)
			{
				z=(z+nr[0][a[j]])%dv;
			}
		}
	}
	else
	{
		for(i=lb;i<=rb;i++)
		{
			k=ed[i].fr.fr;
			l=ed[i].fr.sc;
			w=max(pst[l]-pst[k]+1,nn-(pst[l]-pst[k]-1));
			if(w<mn)
			{
				mn=w;
				p[0]=k;
				p[1]=l;
			}
		}
		for(ii=0;ii<2;ii++)
		{
			dij(ii,p[ii]);
			nm[ii]=0;
		}
		for(i=1;i<=nn;i++)
		{
			if(a[i]!=p[0]&&a[i]!=p[1])
			{
				k=nr[0][a[i]];
				l=nr[1][a[i]];
				e=i>pst[p[0]]&&i<pst[p[1]];
				nm[e]++;
				as[e][nm[e]]={k-l,{k%dv,l%dv}};
			}
		}
		sort(as[0]+1,as[0]+nm[0]+1);
		for(i=1;i<=nm[0];i++)
		{
			k=as[0][i].sc.fr;
			l=as[0][i].sc.sc;
			for(ii=0;ii<2;ii++)
			{
				ps[ii][i]=(ps[ii][i-1]+k)%dv;
				swap(k,l);
			}
		}
		for(i=1;i<=nm[1];i++)
		{
			w=as[1][i].fr;
			k=as[1][i].sc.fr;
			l=as[1][i].sc.sc;
			e=upper_bound(as[0]+1,as[0]+nm[0]+1,mp(-w,mp(inf,inf)))-as[0]-1;
			z=(z+ps[0][e]+k*e+ps[1][nm[0]]+dv-ps[1][e]+l*(nm[0]-e))%dv;
		}
		z=(z+dv-nr[0][p[1]]%dv)%dv;
	}
	for(i=1;i<=nn;i++)
	{
		dg[a[i]]=0;
		vtd[a[i]]=0;
	}
	nn=0;
	if(mn!=inf)
	{
		for(ii=0;ii<2;ii++)
		{
			nm[ii]=0;
		}
		e=lb-1;
		for(i=lb;i<=rb;i++)
		{
			k=ed[i].fr.fr;
			l=ed[i].fr.sc;
			w=ed[i].sc;
			if(pst[k]<pst[p[0]]||pst[l]>pst[p[1]])
			{
				e++;
				swap(ed[i],ed[e]);
			}
		}
		for(i=lb;i<=rb;i++)
		{
			k=ed[i].fr.fr;
			l=ed[i].fr.sc;
			w=ed[i].sc;
			if(k==p[0]&&l==p[1])
			{
				e++;
				swap(ed[i],ed[e]);
				ed[e].sc=nr[0][p[1]];
			}
		}
		w=nr[0][p[1]];
		dnc(lb,e);
		ed[e]={{p[0],p[1]},w};
		dnc(e,rb);
	}
}

int main()
{
	long long i,k,l,w,sz,p;
	
	scanf("%lld%lld",&n,&sz);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",a+i);
		pr[i]=i-1;
	}
	for(i=0;i<sz;i++)
	{
		scanf("%lld%lld%lld",&k,&l,&w);
		if(k+1==l)
		{
			p=k;
		}
		else if(k==1&&l==n)
		{
			p=n;
		}
		else
		{
			p=0;
		}
		if(!p)
		{
			m++;
			ed[m]={{k,l},w};
		}
		else
		{
			a[p]=min(a[p],w);
		}
	}
	for(i=1;i<=n;i++)
	{
		k=i;
		l=i%n+1;
		if(k>l)
		{
			swap(k,l);
		}
		m++;
		ed[m]={{k,l},a[i]};
	}
	sort(ed+1,ed+m+1,cmp);
	sz=m;
	for(i=1;i<=sz;i++)
	{
		k=ed[i].fr.fr;
		l=ed[i].fr.sc;
		if(k+1<l)
		{
			for(p=pr[pr[l]];p!=k;p=pr[p])
			{
				m++;
				ed[m]={{p,l},ub};
			}
			pr[l]=k;
		}
	}
	for(i=1;i<=m;i++)
	{
		k=ed[i].fr.fr;
		l=ed[i].fr.sc;
		dg[k]++;
		dg[l]++;
	}
	for(i=1;i<=n;i++)
	{
		od[i+1]=od[i]+dg[i];
		dg[i]=0;
	}
	dnc(1,m);
	printf("%lld\n",z);
}
