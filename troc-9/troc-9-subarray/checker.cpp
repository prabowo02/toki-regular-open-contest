#include <bits/stdc++.h>
using namespace std;

const int MAXN=4e4+5, MAXB=1024;

int N, Q, K;
int A[MAXN];
int B[MAXN];
int faf[MAXN];
int ans[MAXB];
int last[MAXN];
bool ada[MAXB];

int kmp() {
	for (int i=2;i<K;i++) {
		faf[i]=faf[i-1];
		
		while (B[i]!=B[faf[i]+1]) {
			if (!faf[i]) {
				faf[i]--;
				break;
			}
			
			faf[i]=faf[faf[i]];
		}
		
		faf[i]++;
	}
	
	last[0]=0;
	ans[0]=0;
	
	int x;
	x=0;
	
	for (int i=1;i<N;i++) {
		while (A[i]!=B[x+1]) {
			if (!x) {
				x--;
				break;
			}
			
			x=faf[x];
		}
		
		x++;
		
		if (x==K-1) {
		    x=faf[x];
			last[i]=max(last[i],i-K+2);
			
			if (i-K+2>last[0]) {
				ans[0]++;
				last[0]=i+1;
			}
		}
	}
	
	return ans[0];
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>N>>Q;
	
	for (int i=0;i<N;i++) {
		cin>>A[i];
	}
	
	for (int i=N-1;i;i--) {
		A[i]^=A[i-1];
	}
	
	if (Q!=20000) {
		for (int i=1;i<=Q;i++) {
			cin>>K;
			
			for (int j=0;j<K;j++) {
				cin>>B[j];
			}
			
			for (int j=K-1;j;j--) {
				B[j]^=B[j-1];
			}
			
			cout<<kmp()<<'\n';
		}
		
		last[0]=0;
		ans[0]=0;
		
		for (int i=1;i<N;i++) {
			if (last[i]&&last[i]>last[0]) {
				ans[0]++;
				last[0]=i+1;
			}
		}
		
		cout<<ans[0]<<'\n';
		return 0;
	}
	
	for (int i=1;i<N;i++) {
		if (last[A[i]]!=i) {
			ans[A[i]]++;
			last[A[i]]=i+1;
		}
	}
	
	for (int i=1;i<=Q;i++) {
		cin>>B[0]>>B[1]>>B[2];
		B[2]^=B[1];
		ada[B[2]]=1;
		cout<<ans[B[2]]<<'\n';
	}
	
	ans[0]=0;
	
	for (int i=1;i<N;i++) {
		if (ada[A[i]]) {
			ans[0]++;
			i++;
		}
	}
	
	cout<<ans[0]<<'\n';
	return 0;
}
