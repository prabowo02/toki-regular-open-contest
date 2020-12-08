#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e4+5, MAXH=100, LOG=20;
const long long MOD=1e9+7;

int N, Q, X[MAXN], Y[MAXN], Z[MAXN];
int H[MAXN];
long long S[MAXN], A[MAXH+5], P[MAXN];
long long M[LOG][MAXH+5][MAXH+5];

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>N;
	
	for (int i=1;i<=N;i++) {
		cin>>H[i];
		M[0][1][H[i]]++;
	}
	
	for (int i=2;i<=MAXH;i++) {
		for (int j=i;j<=MAXH;j++) {
			M[0][i][j]=M[0][i-1][j];
		}
	}
	
	for (int i=1;i<LOG;i++) {
		for (int j=1;j<=MAXH;j++) {
			for (int k=1;k<=MAXH;k++) {
				for (int l=1;l<=MAXH;l++) {
					M[i][j][k]=(M[i][j][k]+M[i-1][j][l]*M[i-1][l][k])%MOD;
				}
			}
		}
	}
	
	cin>>Q;
	
	for (int i=1;i<=Q;i++) {
		cin>>X[i]>>Y[i]>>Z[i];
		
		if (Z[i]==0) {
			if (X[i]==Y[i]) {
				P[i] = 1;
			}
			else {
				P[i] = 0;
			}
			
			continue;
		}
		
		for (int j=1;j<=MAXH;j++) {
			A[j]=0;
		}
		
		Z[i]--;
		A[H[X[i]]]=1;
		
		for (int j=0;j<LOG;j++) {
			if ((Z[i]>>j)%2==0) {
				continue;
			}
			
			for (int k=1;k<=MAXH;k++) {
				for (int l=1;l<=MAXH;l++) {
					S[l]=(S[l]+A[k]*M[j][k][l])%MOD;
				}
			}
			
			for (int k=1;k<=MAXH;k++) {
				A[k]=S[k];
				S[k]=0;
			}
		}
		
		for (int k=2;k<=MAXH;k++) {
			A[k]=(A[k]+A[k-1])%MOD;
		}
		
		P[i]=A[H[Y[i]]];
	}
	
	for (int i=1;i<=Q;i++) {
		if (i>1) {
			cout<<'\n';
		}
		
		cout<<P[i];
	}
	
	cout<<'\n';
	return 0;
}
