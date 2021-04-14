#include <bits/stdc++.h>

using namespace std;

long long n,d,a[100069];

int main()
{
	long long i,j,z=0;
	
	scanf("%lld%lld",&n,&d);
	for(j=0,i=1;i<=n;i++)
	{
		scanf("%lld",a+i);
		for(;a[j+1]<=a[i]-d;j++);
		z+=j&&a[j]==a[i]-d;
	}
	printf("%lld\n",z);
}
