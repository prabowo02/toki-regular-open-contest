#include <bits/stdc++.h>
using namespace std;

const int MAXP=70, MAX3P=200;
const long long MOD=1e9+7;

int N, P, Q;
long long M, A, C, H;
long long DP[MAXP][MAX3P];
long long DPsum[MAX3P];
long long DPcnt[MAX3P];
long long sum[3][MAX3P];
long long cnt[3][MAX3P];
long long inv[MAX3P];
string S;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>N>>Q>>S;
	P=66;
	
	for (int i=0;i<N;i++) {
		cin>>A;
		
		if (S[i]=='b') {
			sum[0][0]=(sum[0][0]+A)%MOD;
			cnt[0][0]=(cnt[0][0]+1)%MOD;
			
			for (int j=1;j<3*P;j++) {
				sum[0][j]=(sum[0][j]+sum[2][j-1]+A*cnt[2][j-1])%MOD;
				cnt[0][j]=(cnt[0][j]+cnt[2][j-1])%MOD;
			}
		}
		
		if (S[i]=='o') {
			sum[1][0]=(sum[1][0]+A)%MOD;
			cnt[1][0]=(cnt[1][0]+1)%MOD;
			
			for (int j=1;j<3*P;j++) {
				sum[1][j]=(sum[1][j]+sum[0][j-1]+A*cnt[0][j-1])%MOD;
				cnt[1][j]=(cnt[1][j]+cnt[0][j-1])%MOD;
			}
		}
		
		if (S[i]=='n') {
			sum[2][0]=(sum[2][0]+A)%MOD;
			cnt[2][0]=(cnt[2][0]+1)%MOD;
			
			for (int j=1;j<3*P;j++) {
				sum[2][j]=(sum[2][j]+sum[1][j-1]+A*cnt[1][j-1])%MOD;
				cnt[2][j]=(cnt[2][j]+cnt[1][j-1])%MOD;
			}
		}
	}
	
	for (int i=0;i<3*P;i++) {
		DPsum[i]=sum[i%3][i];
		DPcnt[i]=cnt[i%3][i];
	}
	
	for (int i=1;i<=P;i++) {
		DP[i][1]=DPsum[3*i-1];
	}
	
	inv[1]=1;
	
	for (int i=2;i<=3*P;i++) {
		for (int j=3*P-1;j>=0;j--) {
			DPsum[j]=0;
			DPcnt[j]=0;
			
			for (int k=1;k<=j;k++) {
				DPsum[j]=(DPsum[j]+DPsum[k-1]*cnt[j%3][j-k]+DPcnt[k-1]*sum[j%3][j-k])%MOD;
				DPcnt[j]=(DPcnt[j]+DPcnt[k-1]*cnt[j%3][j-k])%MOD;
			}
		}
		
		for (int j=1;j<=P;j++) {
			DP[j][i]=DPsum[3*j-1];
		}
		
		inv[i]=MOD-(MOD/i)*inv[MOD%i]%MOD;
	}
	
	for (int i=1;i<=Q;i++) {
		cin>>P>>M;
		M%=MOD;
		H=0;
		C=M;
		
		for (int j=1;j<=3*P;j++) {
			H=(H+C*DP[P][j])%MOD;
			C=C*(M-j)%MOD;
			C=C*inv[j+1]%MOD;
		}
		
		cout<<H<<'\n';
	}
	
	return 0;
}
