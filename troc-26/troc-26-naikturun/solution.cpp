#include<bits/stdc++.h>
using namespace std;

long long n,m,x,odd,even;
bool f;
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cin>>x;
			if(x==-1)
			{
				if((i+j)%2)
				{
					f=false;
				}
				else
				{
					f=true;
				}
				continue;
			}
			if((i+j)%2)
			{
				odd+=x;
			}
			else
			{
				even+=x;
			}
		}
	}
	if(!f&&odd<=even)
	{
		cout<<"YES\n";
		cout<<even-odd<<'\n';
	}
	else if(f&&even<=odd)
	{
		cout<<"YES\n";
		cout<<odd-even<<'\n';
	}
	else
	{
		cout<<"NO\n";
	}
}
