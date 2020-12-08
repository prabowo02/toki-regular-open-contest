#include<bits/stdc++.h>
using namespace std;
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
int n, a[20005], peri=0, ans=0;
int connect[20005], dp[20005];
int work(int num){
	int len=peri/num;
	memset(connect, -1, sizeof(connect));
	memset(dp, 0, sizeof(dp));
	for(int lf=0, rg=0, tlen=0; lf<2*n; lf++){
		for(; rg<2*n && tlen<len; tlen+=a[rg], rg++);
		if(tlen==len) connect[lf]=rg;
		tlen-=a[lf];
	}
	for(int i=2*n-1; i>=0; i--) if(connect[i]!=-1){
		dp[i]=1;
		if(connect[i]<2*n) dp[i]+=dp[connect[i]];
	}
	int mx=-1;
	for(int i=0; i<2*n; i++) 
		mx=max(mx, dp[i]);
	if(mx>=num) return num;
	return 0;
}
int main(){ fast;
	cin>>n;
	for(int i=0; i<n; i++){
		cin>>a[i];
		peri+=a[i];
	}
	for(int i=n; i<2*n; i++) a[i]=a[i-n];
	for(int i=1; i*i<=peri; i++) if(peri%i==0){
		ans=max(ans, work(i));
		if(i!=peri/i)
			ans=max(ans, work(peri/i));
	}
	if(ans<=2) cout<<"-1\n";
	else cout<<n-ans<<endl;
	return 0;
}