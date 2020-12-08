#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e3+5, MAXS=1e6+5;

int N, P;
long long K, H;
long long A[4][MAXN];
long long B[2][MAXS];

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>N>>K;
	
	for (int i=0;i<4;i++) {
		for (int j=0;j<N;j++) {
			cin>>A[i][j];
		}
	}
	
	for (int i=0;i<2;i++) {
		for (int j=0;j<N;j++) {
			for (int k=0;k<N;k++) {
				B[i][j*N+k]=A[i<<1][j]+A[i<<1|1][k];
			}
		}
		
		sort(B[i],B[i]+N*N);
	}
	
	for (int i=N*N-1;i>=0;i--) {
		while (P<N*N&&B[0][i]+B[1][P]<=K) {
			P++;
		}
		
		H+=P;
	}
	
	cout<<H<<'\n';
	return 0;
}
