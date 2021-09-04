#include <bits/stdc++.h>

using namespace std;

long long n;

int main()
{
	long long i;
	
	scanf("%lld",&n);
	for(i=0;i<n;i++)
	{
		printf("%c",(char)(i%3+'a'));
	}
	printf("\n");
}
