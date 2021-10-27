#include <bits/stdc++.h>

using namespace std;

long long n,m;

int main()
{
	long long z;
	
	scanf("%lld%lld",&n,&m);
	if(n%2)
	{
		swap(n,m);
	}
	if(m%2==0)
	{
		z=n*m/4;
	}
	else if(n%2==0)
	{
		z=n*(m-3)/4;
	}
	else
	{
		z=n*m-(n/2+1)*(m/2+1)*3;
	}
	printf("%lld\n",max(z,-1ll));
}
