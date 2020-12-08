#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

long long n,d,dg[100069],sq[100069];
vector<long long> al[100069];
multiset<long long> ms;
multiset<long long>::iterator it;

int main()
{
	long long i,j,k,l,w,sz,sh=0;
	
	scanf("%lld%lld",&n,&d);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",dg+i);
		for(j=0;j<dg[i];j++)
		{
			scanf("%lld",&k);
			al[k].push_back(i);
		}
		if(!dg[i])
		{
			ms.insert(i-1);
		}
	}
	for(i=1;i<=n;i++)
	{
		it=ms.lower_bound(sh);
		if(it==ms.end())
		{
			it=ms.begin();
		}
		k=*it+1;
		ms.erase(it);
		sq[i]=(k-1+n-sh)%n;
		sz=al[k].size();
		for(j=0;j<sz;j++)
		{
			l=al[k][j];
			dg[l]--;
			if(!dg[l])
			{
				ms.insert(l-1);
			}
		}
		sh=(sh+n-d)%n;
	}
	for(i=1;i<=n;i++)
	{
		printf("%lld%c",sq[i]," \n"[i==n]);
	}
}
