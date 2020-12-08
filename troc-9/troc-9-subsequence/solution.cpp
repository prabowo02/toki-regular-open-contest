#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;

int N, K;
long long H;
long long A[MAXN];

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>N>>K;
	
	for (int i=0;i<N;i++) {
		cin>>A[i];
	}
	
	sort(A,A+N);
	
	for (int i=0;i<K/2;i++) {
		A[i+(K+1)/2]=A[i+N-K/2];
	}
	
	for (int i=1;i<K;i++) {
		H+=A[i]*i-A[i-1];
		A[i]+=A[i-1];
	}
	
	cout<<H<<'\n';
	return 0;
}
