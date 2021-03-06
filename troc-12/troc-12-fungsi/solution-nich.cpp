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
	//single query complexity: O(log(MAXX)^2)
	int q;
	scanf("%d", &q);
	while(q--){
		int x, y;
		scanf("%d%d", &x, &y);
		if(x==y){
			printf("%d\n", x);
			continue;
		}
		if(x<y)swap(x, y);
		int X=x;
		for(int i = logMAXX;i --;){
			if(X-powerJump[X%ab][i]<=0)
				continue;
			int Y=y;
			for(int j = logMAXX;j --;)
				if(Y-powerJump[Y%ab][j]>=X-powerJump[X%ab][i])
					Y-=powerJump[Y%ab][j];
			if(Y!=X-powerJump[X%ab][i])
				X-=powerJump[X%ab][i];
		}
		X-=powerJump[X%ab][0];
		if(X<=0){
			printf("-1\n");
		}else{
			printf("%d\n", X);
		}
	}
}