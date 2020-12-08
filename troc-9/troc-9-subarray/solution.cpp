#include <bits/stdc++.h>
#define pii pair<int,long long>
#define tii pair<pii,int>
#define i1 first
#define i2 second
using namespace std;

const int MAXN=4e4+5, MAXC=1<<15;
const long long BASE=1031, MOD=(1<<30)-35;

int N, Q, X, Y, L;
int A[MAXN];
int B[MAXN];
int H[MAXN];
long long P[MAXN];
pii S[MAXN];
tii K[MAXN];
vector <pii> V[MAXC];

void build() {
	S[L-1].i2=0;
	X=0;
	
	for (int i=1;i<L-1;i++) {
		S[i]={-1,-1};
		S[L-1].i2=(S[L-1].i2*BASE+A[i])%MOD;
	}
	
	for (int i=L-1;i<N;i++) {
		S[i].i1=i;
		S[i].i2=(S[i].i2*BASE+A[i])%MOD;
		S[i+1].i2=(S[i].i2+MOD-P[L-2]*A[i-L+2]%MOD)%MOD;
	}
	
	S[0]={-1,-1};
	S[N]={N,MOD};
	
	for (int i=L-1;i<N;i++) {
		V[S[i].i2&(MAXC-1)].push_back(S[i]);
	}
	
	Y=L-1;
	
	for (int i=0;i<MAXC;i++) {
		for (pii c : V[i]) {
			S[Y]=c;
			Y++;
		}
		
		V[i].clear();
	}
	
	for (int i=L-1;i<N;i++) {
		V[S[i].i2>>15].push_back(S[i]);
	}
	
	Y=L-1;
	
	for (int i=0;i<MAXC;i++) {
		for (pii c : V[i]) {
			S[Y]=c;
			Y++;
		}
		
		V[i].clear();
	}
	
	return;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>N>>Q;
	P[0]=1;
	
	for (int i=0;i<N;i++) {
		cin>>A[i];
		P[i+1]=(P[i]*BASE)%MOD;
	}
	
	for (int i=0;i<Q;i++) {
		cin>>K[i].i1.i1>>Y;
		K[i].i2=i;
		
		for (int j=1;j<K[i].i1.i1;j++) {
			cin>>X;
			K[i].i1.i2=(K[i].i1.i2*BASE+(X^Y))%MOD;
			Y=X;
		}
	}
	
	sort(K,K+Q);
	
	for (int i=N-1;i;i--) {
		A[i]^=A[i-1];
	}
	
	for (int i=0;i<Q;i++) {
		if (K[i].i1.i1!=L) {
			L=K[i].i1.i1;
			build();
		}
		
		if (K[i].i1.i2<S[X].i2) {
			continue;
		}
		
		if (K[i].i1.i2==S[X].i2) {
			H[K[i].i2]=H[K[i-1].i2];
			continue;
		}
		
		while (K[i].i1.i2>S[X].i2) {
			X++;
		}
		
		Y=0;
		
		while (K[i].i1.i2==S[X].i2) {
			if (S[X].i1>Y) {
				H[K[i].i2]++;
				Y=S[X].i1+L-1;
			}
			
			if (!B[S[X].i1]) B[S[X].i1]=L;
			X++;
		}
		
		X--;
	}
	
	for (int i=0;i<Q;i++) {
		cout<<H[i]<<'\n';
	}
	
	X=0;
	Y=-1;
	
	for (int i=1;i<N;i++) {
		if (B[i]&&i-B[i]>=Y) {
			X++;
			Y=i;
		}
	}
	
	cout<<X<<'\n';
	return 0;
}
