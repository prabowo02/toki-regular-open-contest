#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

long long n,ma=1e5,nn[100069],pwk,dv=1e9+7,inf=1e18;
vector<pair<long long,long long>> fz[100069],sk[100069];

long long pw(long long x,long long y)
{
	if(!y)
	{
		return 1;
	}
	pwk=pw(x,y/2);
	pwk=pwk*pwk%dv;
	if(y%2)
	{
		pwk=pwk*x%dv;
	}
	return pwk;
}

int main()
{
	long long i,j,k,l,w,c,sz,sm=1,z=1;
	
	for(i=1;i<=ma;i++)
	{
		sz=fz[i].size();
		if(i-1&&!sz)
		{
			for(j=i;j<=ma;j+=i)
			{
				for(c=0,k=j;k%i==0;k/=i,c++);
				fz[j].push_back({i,c});
			}
		}
		sk[i].push_back({0,inf});
	}
	scanf("%lld",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",&k);
		sz=fz[k].size();
		for(j=0;j<sz;j++)
		{
			l=fz[k][j].fr;
			w=fz[k][j].sc;
			sk[l].push_back({i,0});
			nn[l]++;
			for(;sk[l][nn[l]].sc<=w;sk[l].pop_back(),nn[l]--)
			{
				sm=sm*pw(l,(w-sk[l][nn[l]].sc)*(sk[l][nn[l]].fr-sk[l][nn[l]-1].fr))%dv;
			}
			sk[l].push_back({i,w});
			nn[l]++;
		}
		z=z*sm%dv;
	}
	printf("%lld\n",z);
}
