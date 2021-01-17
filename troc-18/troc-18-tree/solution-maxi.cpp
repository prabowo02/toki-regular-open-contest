#include <stdio.h>
#include <vector>

using namespace std;

const int MX = 200005;

int n, q;

vector<int> adj[MX];
int ht[MX], tin[MX], tout[MX], tim;

int st[MX * 4][2], lz[MX * 4][2];

void prop(int nd, int cl, int cr, int tp){
	if(lz[nd][tp]){
		if((cr - cl + 1) & 1)
			st[nd][tp] ^= lz[nd][tp];
		if(cl != cr){
			lz[nd * 2][tp] ^= lz[nd][tp];
			lz[nd * 2 + 1][tp] ^= lz[nd][tp];
		}
		lz[nd][tp] = 0;
	}
}

void upd(int nd, int cl, int cr, int lf, int rg, int val, int tp){
	prop(nd, cl, cr, tp);
	if(cr < lf || rg < cl) return;
	if(lf <= cl && cr <= rg){
		lz[nd][tp] ^= val;
		prop(nd, cl, cr, tp);
		return;
	}

	int cm = (cl + cr) / 2;
	upd(nd * 2, cl, cm, lf, rg, val, tp);
	upd(nd * 2 + 1, cm + 1, cr, lf, rg, val, tp);
	st[nd][tp] = (st[nd * 2][tp] ^ st[nd * 2 + 1][tp]);
}

int que(int nd, int cl, int cr, int lf, int rg, int tp){
	prop(nd, cl, cr, tp);
	if(cr < lf || rg < cl) return 0;
	if(lf <= cl && cr <= rg) return st[nd][tp];

	int cm = (cl + cr) / 2;
	return (que(nd * 2, cl, cm, lf, rg, tp) ^
		que(nd * 2 + 1, cm + 1, cr, lf, rg, tp));
}

void dfs(int nw, int bf){
	tin[nw] = tim ++;
	for(int nx : adj[nw]) if(nx != bf){
		ht[nx] = ht[nw] + 1;
		dfs(nx, nw);
	}
	tout[nw] = tim - 1;
}

int main(){
	scanf("%d", &n);

	for(int u, v, i = 1; i < n; i ++){
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	tim ++; dfs(1, 1); tim --;

	scanf("%d", &q);
	for(int tp, x, v, i = 0; i < q; i ++){
		scanf("%d %d", &tp, &x);
		if(tp == 1){
			scanf("%d", &v);
			upd(1, 1, tim, tin[x], tout[x], v, ht[x] & 1);
		}else{
			printf("%d\n", que(1, 1, tim, tin[x], tin[x], ht[x] & 1));
		}
	}

	return 0;
}
