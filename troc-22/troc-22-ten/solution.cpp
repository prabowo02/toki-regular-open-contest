#include <bits/stdc++.h>

using namespace std;

long long n;

int main()
{
	scanf("%lld",&n);
	for(;n;n/=10)
	{
		if(n%10==0)
		{
			printf("YES\n");
			return 0;
		}
	}
	printf("NO\n");
}
