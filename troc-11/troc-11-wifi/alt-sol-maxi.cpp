#include<bits/stdc++.h>
using namespace std;
const int inf=2*1000*1000*1000;
int n, dist, mn; vector<int>a;
int main(){
	scanf("%d %d", &dist, &n);
	a.resize(n);
	for(int i=0; i<n; i++)
		scanf("%d", &a[i]);
	sort(a.begin(), a.end());
	mn=inf;
	for(int i=dist-1; i<n; i++){
		if(a[i]-a[i-dist+1]<mn)
			mn=a[i]-a[i-dist+1];
	}
	printf("%d\n", mn);
	return 0;
}