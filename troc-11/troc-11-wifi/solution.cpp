#include <bits/stdc++.h>
using namespace std;
long long n,m,arr[100005],ans;
int main(){
	cin>>n>>m;
	ans = 1e18;
	for(int i =1;i<=n;i++){
		cin>>arr[i];
	}
	sort(arr+1,arr+n+1);
	for(int i =1;i+m-1<=n;i++){
		ans = min(ans,arr[i+m-1]-arr[i]);
	}
	cout<<ans<<endl;
}