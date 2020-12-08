#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e3+5;

int N, M;
int A[MAXN], B[MAXN];
long long H;

int main () {
	cin>>N>>M;
	
	for (int i=1;i<=N;i++) {
		cout<<"? "<<i<<' '<<1<<'\n';
		fflush(stdout);
		cin>>A[i];
	}
	
	for (int i=2;i<=M;i++) {
		cout<<"? "<<1<<' '<<i<<'\n';
		fflush(stdout);
		cin>>B[i];
		B[i]^=A[1];
	}
	
	for (int i=1;i<=N;i++) {
		for (int j=1;j<=M;j++) {
			H+=A[i]^B[j];
		}
	}
	
	cout<<"! "<<H<<'\n';
	fflush(stdout);
	
	return 0;
}
