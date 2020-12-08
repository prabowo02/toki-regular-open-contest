#include <bits/stdc++.h>

using namespace std;

long long n[2];

int main()
{
	long long ii,z=0;
	
	scanf("%lld%lld",n,n+1);
	for(ii=0;ii<2;ii++)
	{
		z+=((n[ii]-2)*(n[ii]-1)/2+n[ii]-2)*4;
	}
	printf("%lld\n",z);
}
