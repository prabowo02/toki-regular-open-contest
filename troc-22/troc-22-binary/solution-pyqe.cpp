#include <bits/stdc++.h>

using namespace std;

long long n,sq[4];

long long qr(long long x)
{
	long long k;
	
	printf("? %lld\n",x);
	fflush(stdout);
	scanf("%lld",&k);
	return k;
}

int main()
{
	long long i,ii,k,e,lh,rh,md,zz,z,z2=0;
	
	scanf("%lld",&n);
	e=qr(1);
	for(ii=0;ii<2;ii++)
	{
		for(k=max(z2,1ll)*2;qr(z2+k)==(e^ii);k*=2);
		for(zz=k/2,lh=k/2+1,rh=k-1;lh<=rh;)
		{
			md=(lh+rh)/2;
			if(qr(z2+md)==(e^ii))
			{
				zz=md;
				lh=md+1;
			}
			else
			{
				rh=md-1;
			}
		}
		z=zz;
		swap(z,z2);
	}
	sq[0]=z2;
	sq[2]=z2-z+z2*e;
	sq[1]=(n+sq[2]-1)/z2/2+1;
	sq[3]=z2*2*sq[1]-n-sq[2];
	printf("!");
	for(i=0;i<4;i++)
	{
		printf(" %lld",sq[i]);
	}
	printf("\n");
	fflush(stdout);
	
}
