#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXX=1000000000;
const int logMAXX=30;
const int MAXab=100000;
int a, b, ka, kb, la, lb;
int ab;
inline int posmod(int x){
	return (x%ab+ab)%ab;
}
int powerJump[MAXab][logMAXX];
int main(){
	scanf("%d%d%d%d%d%d", &a, &b, &ka, &kb, &la, &lb);
	//precomputation complexity: O(MAXab log(MAXX))
	ab=a*b;
	for(int i = 0;i < ab;i ++)
		powerJump[i][0]=1;
	for(int i = kb;i < ab;i += b)
		powerJump[i][0]=lb;
	for(int i = ka;i < ab;i += a)
		powerJump[i][0]=la;
	for(int I = 1;I < logMAXX;I ++)for(int i = 0;i < ab;i ++){
		if(powerJump[i][I-1]+powerJump[posmod(i-powerJump[i][I-1])][I-1]>=MAXX){
			powerJump[i][I]=MAXX;
		}else{
			powerJump[i][I]=powerJump[i][I-1]+powerJump[posmod(i-powerJump[i][I-1])][I-1];
		}
	}
	//single query complexity: O(log(MAXX))
	int q;
	scanf("%d", &q);
	while(q--){
		int x, y;
		scanf("%d%d", &x, &y);
		int X=x, xstep=0;
		for(int i = logMAXX;i --;){
			if(X-powerJump[X%ab][i]>0){
				X-=powerJump[X%ab][i];
				xstep|=1<<i;
			}
		}
		int Y=y, ystep=0;
		for(int i = logMAXX;i --;){
			if(Y-powerJump[Y%ab][i]>0){
				Y-=powerJump[Y%ab][i];
				ystep|=1<<i;
			}
		}
		if(xstep<ystep){
			swap(x, y);
			swap(xstep, ystep);
		}
		int steps=xstep-ystep;
		for(int i = logMAXX;i --;){
			if(steps>>i&1){
				x-=powerJump[x%ab][i];
			}
		}
		if(x==y){
			printf("%d\n", x);
			continue;
		}
		for(int i = logMAXX;i --;){
			if(x-powerJump[x%ab][i]<=0)continue;
			if(x-powerJump[x%ab][i]!=y-powerJump[y%ab][i]){
				x-=powerJump[x%ab][i];
				y-=powerJump[y%ab][i];
			}
		}
		x-=powerJump[x%ab][0];
		if(x<=0){
			printf("-1\n");
		}else{
			printf("%d\n", x);
		}
	}
}