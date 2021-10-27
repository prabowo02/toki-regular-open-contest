#include <bits/stdc++.h>

using namespace std;

const long long d=4;
long long p3[5],pst[4],pst2[5][5][4];

int main()
{
	long long i,j,r,k;
	
	p3[0]=1;
	for(i=1;i<d+1;i++)
	{
		p3[i]=p3[i-1]*3;
	}
	for(i=0;i<d+1;i++)
	{
		for(j=i+1;j<d+1;j++)
		{
			for(r=0;r<d;r++)
			{
				pst2[i][j][r]=-1;
			}
		}
	}
	for(i=0;1;i++)
	{
		for(j=0;j<4;j++)
		{
			pst[j]=-1;
		}
		for(j=0;1;j++)
		{
			printf("? %lld\n",p3[j]<<i);
			fflush(stdout);
			scanf("%lld",&k);
			k--;
			if(pst[k]+1)
			{
				break;
			}
			pst[k]=j;
		}
		if(pst2[pst[k]][j][k]+1)
		{
			break;
		}
		pst2[pst[k]][j][k]=i;
	}
	printf("! %lld %lld\n",p3[j]<<pst2[pst[k]][j][k],p3[pst[k]]<<i);
}
