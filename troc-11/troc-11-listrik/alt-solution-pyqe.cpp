#include <bits/stdc++.h>

using namespace std;

long long n,dsu[100069];
bitset<100069> vtd;

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
	long long i,j,k,z=0,c,tg;
	bool ft;
	
	scanf("%lld",&n);
	for(i=0;i<n;i++)
	{
		scanf("%lld",&k);
		if(vtd[k])
		{
			z+=k;
		}
		vtd[k]=1;
	}
	for(i=1;i<=100000;i++)
	{
		dsu[i]=i;
	}
	for(i=1e5;i;i--)
	{
		ft=1;
		c=0;
		for(j=i;j<=100000;j+=i)
		{
			if(vtd[j])
			{
				if(ft)
				{
					tg=fd(j);
					ft=0;
				}
				else if(fd(j)!=tg)
				{
					dsu[fd(j)]=tg;
					c++;
				}
			}
		}
		z+=i*c;
	}
	printf("%lld\n",z);
}
