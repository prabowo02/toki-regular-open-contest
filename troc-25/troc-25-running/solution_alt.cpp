#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
	ll t,k;
	cin>>t>>k;
   	if(t<k){
	        cout<<t<<'\n';
	        return 0;
	}
	ll ans=k;
	for(int i=1; i<=t-k; i++){
		ans*=2ll;
	}
	cout<<ans<<'\n';
}
