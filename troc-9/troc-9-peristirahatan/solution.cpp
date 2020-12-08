#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;
const long long INF=1e12;

struct angka {
	long long minl, minr;
	long long maxl, maxr;
	
	void build(long long val,int pos) {
		minl=val-pos;
		maxl=val-pos;
		minr=val+pos;
		maxr=val+pos;
		
		return;
	}
	
	void update(long long x) {
		minl+=x;
		maxl+=x;
		minr+=x;
		maxr+=x;
		
		return;
	}
	
	angka operator + (const angka lain) const {
		angka ret;
		ret.minl=min(minl,lain.minl);
		ret.maxl=max(maxl,lain.maxl);
		ret.minr=min(minr,lain.minr);
		ret.maxr=max(maxr,lain.maxr);
		
		return ret;
	}
	
}
kosong={INF,INF,-INF,-INF};

int N, Q, T, X, Y, Z;
int mins, maks;
long long A[MAXN];
angka kiri, kanan;

struct segment {
	int L, R;
	angka val;
	long long udt;
	segment *lef, *rig;
	
	void build(int x,int y) {
		L=x;
		R=y;
		udt=0;
		
		if (x==y) {
			val.build(A[x],x);
			return;
		}
		
		int T;
		T=(L+R)/2;
		
		lef=new segment;
		lef->build(L,T);
		rig=new segment;
		rig->build(T+1,R);
		
		val=lef->val+rig->val;
		return;
	}
	
	void balance() {
		if (!udt) {
			return;
		}
		
		lef->val.update(udt);
		lef->udt+=udt;
		rig->val.update(udt);
		rig->udt+=udt;
		udt=0;
		
		return;
	}
	
	void update(int x,int y,long long z) {
		if (L>y||R<x) {
			return;
		}
		
		if (L>=x&&R<=y) {
			val.update(z);
			udt+=z;
			return;
		}
		
		balance();
		lef->update(x,y,z);
		rig->update(x,y,z);
		val=lef->val+rig->val;
		
		return;
	}
	
	angka query(int x,int y) {
		if (L>y||R<x) {
			return kosong;
		}
		
		if (L>=x&&R<=y) {
			return val;
		}
		
		balance();
		return lef->query(x,y)+rig->query(x,y);
	}
	
}
data;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>N>>Q;
	
	for (int i=1;i<=N;i++) {
		cin>>A[i];
	}
	
	data.build(1,N);
	
	for (int i=1;i<=Q;i++) {
		cin>>T>>X>>Y>>Z;
		
		if (T==1) {
			data.update(X,Y,Z);
			continue;
		}
		
		kiri=data.query(X,min(Y,Z));
		kanan=data.query(max(X,Z),Y);
		
		mins=min(kiri.minl+Z,kanan.minr-Z);
		maks=max(kiri.maxl+Z,kanan.maxr-Z);
		
		cout<<maks-mins<<'\n';
	}
	
	return 0;
}
