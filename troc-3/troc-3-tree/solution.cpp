#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5, LOG=20;

int N, P;
int A[MAXN];
int Z[MAXN], DP[MAXN][LOG];
long long ans;
long long H[LOG];
vector <int> V[MAXN];

void maju(int par,int now) {
	for (int next : V[now]) {
		if (next==par) {
			continue;
		}
		
		maju(now,next);
		
		Z[now]+=Z[next];
		for (int i=0;i<LOG;i++) {
			DP[now][i]+=DP[next][i];
		}
	}
	
	Z[now]++;
	for (int i=0;i<LOG;i++) {
		if ((A[now]>>i)&1) {
			DP[now][i]=Z[now]-DP[now][i];
		}
	}
	
	return;
}

void mundur(int par,int now) {
	for (int i=0;i<LOG;i++) {
		H[i]+=DP[now][i];
		
		if ((A[now]>>i)&1) {
			H[i]--;
		}
	}
	
	for (int next : V[now]) {
		if (next==par) {
			continue;
		}
		
		for (int i=0;i<LOG;i++) {
			int save;
			save=DP[now][i];
			
			if ((A[now]>>i)&1) {
				save-=Z[next]-DP[next][i];
			}
			else {
				save-=DP[next][i];
			}
			
			if ((A[next]>>i)&1) {
				save=N-Z[next]-save;
			}
			
			DP[next][i]+=save;
		}
		
		mundur(now,next);
	}
	
	return;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>N;
	
	for (int i=1;i<=N;i++) {
		cin>>A[i];
	}
	
	for (int i=2;i<=N;i++) {
		cin>>P;
		V[i].push_back(P);
		V[P].push_back(i);
	}
	
	maju(0,1);
	mundur(0,1);
	
	for (int i=0;i<LOG;i++) {
		H[i]=H[i]>>1;
		ans+=H[i]<<i;
	}
	
	cout<<ans<<'\n';
	
	return 0;
}
