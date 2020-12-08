#include<bits/stdc++.h>
#define pb push_back
#define mk make_pair
#define fs first
#define sc second
typedef long long ll;
typedef long double ld;
typedef std::pair<int,int> pii;
const int MAKS_K = 1e5;
const int MAKS_N = 1e3;
int d[4]={0, 1, 0, -1};
using namespace std;

struct soldierAtoKotak{
	int x, y, L, idx;
};
int A[MAKS_N+10][MAKS_N+10], n, m, k, ans[MAKS_N+10][MAKS_N+10], jawab[MAKS_K];
bool vis[MAKS_N+10][MAKS_N+10];
pii par[MAKS_N+10][MAKS_N+10];
soldierAtoKotak P[2*MAKS_K];
vector < soldierAtoKotak > lst;
bool cmp(soldierAtoKotak a, soldierAtoKotak b){
	return a.L < b.L;
}
void init(){
	for (int i= 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			par[i][j] = mk(i, j);
			ans[i][j] = i+j-2;
		//	printf("wtf");
		}
	}
	
	
}
pii find(int now_x, int now_y){
	if (par[now_x][now_y] == mk(now_x, now_y)) return mk(now_x, now_y);
	return par[now_x][now_y] = find(par[now_x][now_y].fs, par[now_x][now_y].sc);
}
bool valid(int x, int y){
	if (x<1 || x > n || y < 1 || y > m) return false;
	return true;
}
void nyala(int idx){
	int x = lst[idx].x;
	int y = lst[idx].y;
//	printf("nyala %d %d\n",x, y);
	vis[x][y] = true;
	for (int i = 0; i < 4; i++){
		int xx = x + d[i];
		int yy = y + d[3-i];
		if (!valid(xx, yy) || !vis[xx][yy]) continue;
		pii p1 = find(x, y);
		pii p2 = find(xx, yy);
		if (p1==p2) continue;
//		printf("connect %d %d to %d %d\n", x, y, xx, yy);
		par[p1.fs][p1.sc] = p2;
		ans[p2.fs][p2.sc] = min(ans[p2.fs][p2.sc], ans[p1.fs][p1.sc]);
	}
	return;
}
int main(){
	scanf("%d%d%d", &n, &m, &k);
	init();
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			scanf("%d", &A[i][j]);
			soldierAtoKotak temp;
			temp.x = i;
			temp.y = j;
			temp.L = A[i][j];
			lst.pb(temp);
		}
	}
	for (int i = 0; i < k; i++){
		scanf("%d%d%d", &P[i].x, &P[i].y, &P[i].L);
		P[i].idx = i;
	}
	sort(lst.begin(), lst.end(), cmp);
	sort(P, P+k, cmp);
	int now = 0;
	for (int i = 0; i < k; i++){
		while(now!=lst.size() && lst[now].L <= P[i].L){
			nyala(now++);
		}
	//	printf("%d %d %d %d %d %d\n",i, now, P[i].idx, ans[P[i].x][P[i].y], P[i].x, P[i].y);
		pii temp = find(P[i].x, P[i].y);
		jawab[P[i].idx] = ans[temp.fs][temp.sc];
	}
	for (int i = 0; i < k; i++){
		printf("%d\n", jawab[i]);
	}
}
