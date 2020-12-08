#include <bits/stdc++.h>

using namespace std;

long long n,z,z2;

void ac()
{
	printf("AC\n");
	exit(0);
}

void wa()
{
	printf("WA\n");
	exit(0);
}

int main(int argc,char *argv[])
{
	ifstream tc_in(argv[1]);
	ifstream tc_out(argv[2]);
	ifstream con_out(argv[3]);
	string s;
	
	tc_in>>n;
	if(!(con_out>>z))
	{
		wa();
	}
	if(!(con_out>>z2))
	{
		wa();
	}
	if(min(z,z2)<=0||max(z,z2)>n||z*z2!=n)
	{
		wa();
	}
	if(con_out>>s)
	{
		wa();
	}
	ac();
}
