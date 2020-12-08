#include<bits/stdc++.h>
using namespace std;
int main(){
	int n, m, r; cin>>n>>m>>r;
	if(n>m) swap(n, m);
	int rad=min(n, 2*r+1);
	int ans=(n+rad-1)/rad;
	cout<<ans<<endl;
	return 0;
}