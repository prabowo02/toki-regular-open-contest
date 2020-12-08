#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5, SQR=320;
const int INF=1e9;

int N, M, K;
int A[MAXN];
int DP[SQR][SQR];
bool R;

int ind(int x,int y) {
	if (R) {
		return N*y+x;
	}
	
	return M*x+y;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>N>>M>>K;
	
	for (int i=0;i<N;i++) {
		for (int j=0;j<M;j++) {
			cin>>A[ind(i,j)];
		}
	}
	
	if (N>M) {
		swap(N,M);
		R=1;
	}
	
	for (int i=0;i<N;i++) {
		for (int j=0;j<N;j++) {
			DP[i][j]=-INF;
		}
	}
	
	DP[0][0]=0;
	
	for (int i=1;i<N+M-1;i++) {
		for (int j=N-1;j>=0;j--) {
			for (int k=N-1;k>=0;k--) {
				if (j) {
					DP[j][k]=max(DP[j][k],DP[j-1][k]);
				}
				
				if (k) {
					DP[j][k]=max(DP[j][k],DP[j][k-1]);
				}
				
				if (j&&k) {
					DP[j][k]=max(DP[j][k],DP[j-1][k-1]);
				}
			}
		}
		
		for (int j=0;j<N;j++) {
			for (int k=0;k<N;k++) {
				if (j>i||k>i) {
					DP[j][k]=-INF;
					continue;
				}
				
				if (i-j>=M||i-k>=M) {
					DP[j][k]=-INF;
					continue;
				}
				
				if (j==k) {
					DP[j][k]+=A[ind(j,i-j)];
					DP[j][k]+=A[ind(k,i-k)]^K;
				}
				else {
					DP[j][k]+=A[ind(j,i-j)];
					DP[j][k]+=A[ind(k,i-k)];
				}
			}
		}
	}
	
	cout<<DP[N-1][N-1]<<'\n';
	
	return 0;
}
