#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll binExpo(ll a,ll b){
	ll res=1;
	while(b){
		if(b%2==1)
			res*=a;
		b/=2;
		a*=a;
	}
	return res;
}
int main(){
	ll t,k;
	cin>>t>>k;
    if(t<k){
        cout<<t<<'\n';
    } else {
	    cout<<k*binExpo(2ll,max(t-k,0ll))<<'\n';
    }
}
