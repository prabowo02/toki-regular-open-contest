#include <bits/stdc++.h>

using namespace std;

long long n;
map<long long,long long> yk;

int main()
{
	long long i,k,x=0,y=0,kx[4]={0,1,0,-1},ky[4]={1,0,-1,0};
	string s;
	
	yk[20]=0;
	yk[17]=1;
	yk[3]=2;
	yk[11]=3;
	cin>>s;
	n=s.length();
	for(i=1;i<=n;i++)
	{
		k=yk[s[i-1]-'A'];
		x+=kx[k];
		y+=ky[k];
	}
	printf("%lld %lld\n",x,y);
}
