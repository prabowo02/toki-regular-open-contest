#include <bits/stdc++.h>

using namespace std;

const long long mm=6;
long long n,m,d,a1[mm+1],m0[mm+1][mm+1],m1[mm+1][mm+1],tmp[mm+1][mm+1],mz[mm+1][mm+1],az[mm+1],dv=1e9+7;

void mul(long long x[mm+1][mm+1],long long y[mm+1][mm+1],long long z[mm+1][mm+1])
{
	long long i,j,r;
	
	for(i=1;i<=mm;i++)
	{
		for(j=1;j<=mm;j++)
		{
			tmp[i][j]=0;
			for(r=1;r<=mm;r++)
			{
				tmp[i][j]=(tmp[i][j]+x[i][r]*y[r][j])%dv;
			}
		}
	}
	for(i=1;i<=mm;i++)
	{
		for(j=1;j<=mm;j++)
		{
			z[i][j]=tmp[i][j];
		}
	}
}

void mpw(long long x)
{
	if(!x)
	{
		mul(m0,m0,mz);
		return;
	}
	mpw(x/2);
	mul(mz,mz,mz);
	if(x%2)
	{
		mul(mz,m1,mz);
	}
}

int main()
{
	long long i,j,lh,rh;
	
	for(i=1;i<=mm;i++)
	{
		m0[i][i]=1;
	}
	scanf("%lld%lld%lld%lld%lld",&n,&lh,&rh,&d,&m);
	m1[1][1]=(n+dv-2)%dv;
	m1[2][1]=(n+dv-2)%dv;
	m1[2][2]=dv-1;
	m1[2][4]=(dv-n+2)%dv;
	m1[3][1]=(n+dv-2)%dv;
	m1[3][2]=dv-1;
	m1[3][4]=(dv-n*2%dv+4)%dv;
	m1[3][5]=1;
	m1[4][2]=1;
	m1[5][3]=1;
	m1[6][1]=(n+dv-2)%dv;
	m1[6][2]=dv-1;
	m1[6][4]=(dv-n*2%dv+4)%dv;
	m1[6][5]=1;
	a1[1]=n*(n-1)%dv;
	lh=(lh-d+m-1)/m*m+d;
	rh=((rh-d+m)/m-1)*m+d;
	if(lh>rh)
	{
		printf("0\n");
		return 0;
	}
	mpw(lh-2);
	for(i=1;i<=mm;i++)
	{
		az[i]=0;
		for(j=1;j<=mm;j++)
		{
			az[i]=(az[i]+a1[j]*mz[i][j])%dv;
		}
	}
	for(i=1;i<=mm;i++)
	{
		a1[i]=az[i];
	}
	mpw(m);
	mul(mz,m0,m1);
	m1[6][6]=1;
	mpw((rh-lh)/m);
	for(i=1;i<=mm;i++)
	{
		az[i]=0;
		for(j=1;j<=mm;j++)
		{
			az[i]=(az[i]+a1[j]*mz[i][j])%dv;
		}
	}
	printf("%lld\n",az[6]);
}
