#include <bits/stdc++.h>

using namespace std;

long long n,d,nn=0,fc[100069],ifc[100069],fq[100069],fz[1069],dp[100069],pwk,dv=1e9+7;

long long pw(long long x,long long y)
{
	if(!y)
	{
		return 1;
	}
	pwk=pw(x,y/2);
	pwk=pwk*pwk%dv;
	if(y%2)
	{
		pwk=pwk*x%dv;
	}
	return pwk;
}

long long cb(long long x,long long y)
{
	if(x<y)
	{
		return 0;
	}
	return fc[x]*ifc[y]%dv*ifc[x-y]%dv;
}

int main()
{
	long long i,j,r,k,z=0;
	
	fc[0]=1;
	ifc[0]=1;
	for(i=1;i<=100000;i++)
	{
		fc[i]=fc[i-1]*i%dv;
		ifc[i]=pw(fc[i],dv-2);
	}
	scanf("%lld%lld",&n,&d);
	for(i=0;i<n;i++)
	{
		scanf("%lld",&k);
		fq[k]++;
	}
	for(i=1;i*i<=d;i++)
	{
		if(d%i==0)
		{
			nn++;
			fz[nn]=i;
			if(d/i!=i)
			{
				nn++;
				fz[nn]=d/i;
			}
		}
	}
	for(i=1;i<=nn;i++)
	{
		for(j=100000/fz[i]*fz[i];j;j-=fz[i])
		{
			dp[j]=0;
			k=0;
			for(r=j;r<=100000;r+=j)
			{
				dp[j]=(dp[j]+dv-dp[r])%dv;
				k+=fq[r];
			}
			dp[j]=(dp[j]+cb(k,d/fz[i]))%dv;
		}
		z=(z+dp[fz[i]])%dv;
	}
	printf("%lld\n",z);
}
