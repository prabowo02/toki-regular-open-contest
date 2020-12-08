#include<bits/stdc++.h>
using namespace std;
const int N=100000;
int p[N+5], n; bool vis[N+5];
int f(int x){return p[x]=(p[x]==x?x:f(p[x]));}
long long ans;
int main(){
	scanf("%d", &n);
	ans=0ll;
	for(int i=0, x; i<n; i++){
		scanf("%d", &x);
		if(vis[x]) ans+=(long long)x;
		vis[x]=true;
	}
	int t, add;
	for(int i=1; i<=N; i++) p[i]=i;
	for(int i=N; i>0; i--){
		bool first=true;
		add=0;
		for(int j=i; j<=N; j+=i) if(vis[j]){
			if(first){
				t=f(j); first=false;
			}else if(f(j)!=t){
				p[f(j)]=t; add++;
			}
		}
		ans+=add*1ll*i;
	}
	printf("%lld\n", ans); return 0;
}