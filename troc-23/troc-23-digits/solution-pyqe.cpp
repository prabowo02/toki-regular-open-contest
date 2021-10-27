#include <bits/stdc++.h>

using namespace std;

const long long ub=1e6;
long long n;

int main()
{
	long long i,k,ml,sm,z=0;
	
	scanf("%lld",&n);
	n=min(n,ub);
	for(i=1;i<=n;i++)
	{
		ml=1;
		sm=0;
		for(k=i;k;k/=10)
		{
			ml*=k%10;
			sm+=k%10;
		}
		z+=ml+sm==i;
	}
	printf("%lld\n",z);
}
