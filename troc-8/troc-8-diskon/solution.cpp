#include <bits/stdc++.h>
using namespace std;

int X, Y, Z;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>X>>Y>>Z;
	cout<<(X/10000)*(100-Y)*(100+Z)<<'\n';
	
	return 0;
}
