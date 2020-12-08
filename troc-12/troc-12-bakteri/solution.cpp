#include<bits/stdc++.h>
using namespace std;
int n, m, k;
char ans[1005][1005];
int main(){
	scanf("%d%d%d", &n, &m, &k);
	if(k<(n+m+1)/2) printf("TIDAK\n");
	else{
		printf("YA\n");
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++)
				ans[i][j]='.';
		for(int i=0; i<n; i+=2) ans[i][0]='X'; 
		int st=0;
		if(n%2==1) st=2;
		else st=1;
		for(int j=st; j<m; j+=2) ans[n-1][j]='X';
		ans[n-1][m-1]='X';
		k-=(n+m+1)/2;
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				if(ans[i][j]=='.'){
					ans[i][j]='X'; k--;
				}
				if(k==0) break;
			}
			if(k==0) break;
		}
		for(int i=0; i<n; i++)
			printf("%s\n", ans[i]);
	}
	return 0;
}