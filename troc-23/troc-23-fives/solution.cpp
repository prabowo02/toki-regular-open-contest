#include <bits/stdc++.h>

using namespace std;

const long long ub=22;
long long n;

int main()
{
	long long i,sm=0;
	
	scanf("%lld",&n);
	for(i=0;i<ub;i++)
	{
		sm=sm*5+1;
	}
	n+=sm;
	for(;n;n/=5)
	{
		if(n%5>2)
		{
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n");
}
