#include<bits/stdc++.h>
using namespace std;
int n, m, k;
char ans[1005][1005];
int main(){
	scanf("%d%d%d", &n, &m, &k);
	if(k<max(n, m)){printf("NO\n"); return 0;}
	printf("YES\n");
	for(int i=0; i<n; i++) for(int j=0; j<m; j++) ans[i][j]='.';
	for(int i=0; i<min(n, m); i++) ans[i][i]='X';
	for(int i=min(n, m); i<max(n, m); i++){
		if(n<m) ans[n-1][i]='X';
		else ans[i][m-1]='X';
	}
	k-=max(n, m);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(ans[i][j]=='.'){
				ans[i][j]='X'; k--;
			}if(k==0) break;
		}
		if(k==0) break;
	}
	for(int i=0; i<n; i++) printf("%s\n", ans[i]);
	return 0;
}