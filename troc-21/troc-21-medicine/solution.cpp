#include <bits/stdc++.h>

using namespace std;

const long long dv=1e9+7;
long long n,m;

int main()
{
	long long i,z;
	
	scanf("%lld%lld",&n,&m);
	z=m-1;
	for(i=0;i<n-1;i++)
	{
		z=z*m%dv;
	}
	z=(z+m)%dv;
	printf("%lld\n",z);
}
