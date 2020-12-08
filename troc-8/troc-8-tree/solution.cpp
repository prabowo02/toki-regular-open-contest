#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;

int N, Q, T, U, V, X, L;
int cnt;
int P[MAXN];
int D[MAXN];
long long save;
long long lazy[MAXN];
long long jumlah[MAXN];
long long nilai[MAXN];
long long banyak[MAXN];

int lca(int x,int y) {
	while (x!=y) {
		if (D[x]>D[y]) {
			x=P[x];
		}
		else if (D[x]<D[y]) {
			y=P[y];
		}
		else {
			x=P[x];
			y=P[y];
		}
	}
	
	return x;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>N>>Q;
	
	for (int i=2;i<=N;i++) {
		cin>>P[i];
		D[i]=D[P[i]]+1;
	}
	
	for (int i=1;i<=N;i++) {
		cin>>nilai[i];
	}
	
	for (int i=N;i;i--) {
		jumlah[i]+=nilai[i];
		banyak[i]++;
		jumlah[P[i]]+=jumlah[i];
		banyak[P[i]]+=banyak[i];
	}
	
	for (int i=1;i<=Q;i++) {
		cin>>T;
		
		if (T==1) {
			cin>>U>>V>>X;
			L=lca(U,V);
			
			save=0;
			for (int j=U;j;j=P[j]) {
				if (j>L) {
					nilai[j]+=X;
					save+=X;
				}
				
				jumlah[j]+=save;
			}
			
			save=0;
			for (int j=V;j;j=P[j]) {
				if (j>=L) {
					nilai[j]+=X;
					save+=X;
				}
				
				jumlah[j]+=save;
			}
		}
		
		if (T==2) {
			cin>>U>>X;
			
			lazy[U]+=X;
			for (int j=P[U];j;j=P[j]) {
				jumlah[j]+=banyak[U]*X;
			}
		}
		
		if (T==3) {
			cin>>U>>V;
			L=lca(U,V);
			save=0;
			
			cnt=0;
			for (int j=U;j;j=P[j]) {
				if (j>L) {
					save+=nilai[j];
					cnt++;
				}
				
				save+=lazy[j]*cnt;
			}
			
			cnt=0;
			for (int j=V;j;j=P[j]) {
				if (j>=L) {
					save+=nilai[j];
					cnt++;
				}
				
				save+=lazy[j]*cnt;
			}
			
			cout<<save<<'\n';
		}
		
		if (T==4) {
			cin>>U;
			
			save=jumlah[U];
			for (int j=U;j;j=P[j]) {
				save+=banyak[U]*lazy[j];
			}
			
			cout<<save<<'\n';
		}
	}
	
	return 0;
}
