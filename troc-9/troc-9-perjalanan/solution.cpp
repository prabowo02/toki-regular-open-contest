#include <bits/stdc++.h>
using namespace std;

const int MAXN=2e5+5;

struct jalan {
	int hitam, putih;
	int lef, rig, ans, len;
	
	void build(int x) {
		hitam=0;
		putih=0;
		ans=0;
		len=0;
		lef=0;
		rig=0;
		
		if (x==3) {
			hitam++;
		}
		else if (x==0) {
			putih++;
		}
		else {
			len++;
			lef=x;
			rig=x;	
		}
		
		return;
	}
	
	void set(int x) {
		if (hitam) {
			build(x^3);
		}
		else {
			build(x^lef);
		}
		
		return;
	}
	
	void swaps() {
		swap(hitam,putih);
		
		if (len) {
			lef=lef^3;
			rig=rig^3;
		}
		
		return;
	}
	
	jalan operator + (const jalan lain) const {
		jalan ret;
		ret.hitam=hitam+lain.hitam;
		ret.putih=putih+lain.putih;
		ret.ans=ans+lain.ans;
		ret.len=len+lain.len;
		ret.lef=lef;
		ret.rig=lain.rig;
		
		if (!ret.lef) {
			ret.lef=lain.lef;
		}
		else if (!ret.rig) {
			ret.rig=rig;
		}
		else if (rig+lain.lef==3) {
			ret.ans++;
		}
		
		return ret;
	}
	
	jalan operator - (const jalan lain) const {
		jalan ret;
		ret.hitam=hitam+lain.hitam;
		ret.putih=putih+lain.putih;
		ret.ans=ans+lain.ans;
		ret.len=len+lain.len;
		ret.lef=rig;
		ret.rig=lain.rig;
		
		if (!ret.lef) {
			ret.lef=lain.lef;
		}
		else if (!ret.rig) {
			ret.rig=lef;
		}
		else if (lef+lain.lef==3) {
			ret.ans++;
		}
		
		return ret;
	}
	
	int jawab(int x,int y) {
		int ret;
		ret=5*hitam+2*(putih+len)+ans;
	    
	    if (!lef&&x!=y) {
	        ret++;
	    }
	    
		if (x==lef) {
			ret++;
		}
		
		if (y==rig) {
			ret++;
		}
		
		return ret;
	}
	
}
kosong, savex, savey;

int tipe[MAXN];

struct segment {
	int L, R;
	jalan val;
	bool lazy;
	segment *lef, *rig;
	
	void build(int x,int y) {
		L=x;
		R=y;
		lazy=0;
		
		if (x==y) {
			val.build(tipe[x]);
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
		if (!lazy) {
			return;
		}
		
		lef->val.swaps();
		rig->val.swaps();
		lef->lazy^=1;
		rig->lazy^=1;
		
		lazy=0;
		return;
	}
	
	void set(int x,int y) {
		if (x>R||x<L) {
			return;
		}
		
		if (L==R) {
			val.set(y);
			return;
		}
		
		balance();
		lef->set(x,y);
		rig->set(x,y);
		
		val=lef->val+rig->val;
		return;
	}
	
	void update(int x,int y) {
		if (x>R||y<L) {
			return;
		}
		
		if (x<=L&&y>=R) {
			val.swaps();
			lazy^=1;
			return;
		}
		
		balance();
		lef->update(x,y);
		rig->update(x,y);
		
		val=lef->val+rig->val;
		return;
	}
	
	jalan query(int x,int y) {
		if (x>R||y<L) {
			return kosong;
		}
		
		if (x<=L&&y>=R) {
			return val;
		}
		
		balance();
		return lef->query(x,y)+rig->query(x,y);
	}
	
}
*data[MAXN];

int N, Q;
int par[MAXN];
int chl[MAXN];
int rot[MAXN];
int dep[MAXN];
int siz[MAXN];
int way[MAXN];
vector <int> edge[MAXN];

int t, x, y;
char c, d;

void dfs(int now,int root) {
	rot[now]=root;
	tipe[dep[now]]=way[now];
	
	if (edge[now].empty()) {
		data[root]=new segment;
		data[root]->build(dep[root],dep[now]);
		return;
	}
	
	for (int next : edge[now]) {
		if (next==chl[now]) {
			dfs(next,root);
		}
		else {
			dfs(next,next);
		}
	}
	
	return;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin>>N>>Q;
	
	for (int i=2;i<=N;i++) {
		cin>>par[i]>>c>>d;
		
		if (c=='a') {
			way[i]^=1;
		}
		
		if (d=='b') {
			way[i]^=2;
		}
		
		dep[i]=dep[par[i]]+1;
		edge[par[i]].push_back(i);
	}
	
	for (int i=N;i>=1;i--) {
		siz[i]++;
		siz[par[i]]+=siz[i];
		
		if (siz[i]>siz[chl[par[i]]]) {
			chl[par[i]]=i;
		}
	}
	
	dfs(1,1);
	
	for (int i=1;i<=Q;i++) {
		cin>>t;
		
		if (t==1) {
			cin>>x>>c;
			
			x++;
			data[rot[x]]->set(dep[x],1<<(c-'A'));
		}
		
		if (t==2) {
			cin>>x>>y;
			
			while (rot[x]!=rot[y]) {
				if (dep[rot[x]]>dep[rot[y]]) {
					data[rot[x]]->update(dep[rot[x]],dep[x]);
					x=par[rot[x]];
				}
				else {
					data[rot[y]]->update(dep[rot[y]],dep[y]);
					y=par[rot[y]];
				}
			}
			
			if (dep[x]>dep[y]) {
				swap(x,y);
			}
			
			data[rot[x]]->update(dep[x]+1,dep[y]);
		}
		
		if (t==3) {
			cin>>x>>c>>y>>d;
			
			savex=kosong;
			savey=kosong;
			
			while (rot[x]!=rot[y]) {
				if (dep[rot[x]]>dep[rot[y]]) {
					savex=data[rot[x]]->query(dep[rot[x]],dep[x])+savex;
					x=par[rot[x]];
				}
				else {
					savey=data[rot[y]]->query(dep[rot[y]],dep[y])+savey;
					y=par[rot[y]];
				}
			}
			
			if (dep[x]>dep[y]) {
				swap(c,d);
				swap(x,y);
				swap(savex,savey);
			}
			
			savey=data[rot[x]]->query(dep[x]+1,dep[y])+savey;
			cout<<(savex-savey).jawab(1<<(c-'A'),1<<(d-'A'))<<'\n';
		}
	}
	
	return 0;
}
