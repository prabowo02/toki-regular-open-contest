#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;

int N, M;
int A[MAXN];
vector <int> V;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>N;
	
	for (int i=1;i<=N;i++) {
		cin>>A[i];
	}
	
	M=1;
	
	for (int i=2;i<=N;i++) {
		if (A[i]!=A[M]) {
			M++;
			A[M]=A[i];
		}
	}
	
	N=M;
	
	if (N>1) {
		M=2;
		
		for (int i=3;i<=N;i++) {
			if ((A[M-1]<A[M])!=(A[M]<A[i])) {
				M++;
			}
			
			A[M]=A[i];
		}
		
		N=M;
	}
	
	cout<<N<<'\n';
	
	for (int i=1;i<=N;i++) {
		cout<<A[i];
		
		if (i==N) {
			cout<<'\n';
		}
		else {
			cout<<' ';
		}
	}
	
	return 0;
}
