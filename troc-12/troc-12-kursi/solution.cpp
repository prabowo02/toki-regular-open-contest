#include <cstdio>
#include <queue>
using namespace std;

const int maxChair=30;
inline bool between(unsigned lo, unsigned mid, unsigned hi){
	return (lo<mid&&mid<hi)||(lo>mid&&mid>hi);
}
inline unsigned solve(int x, int y){
	unsigned x1=0u, y1=0u, x2=1u<<maxChair, y2=1u<<maxChair, x3=2u<<maxChair, y3=2u<<maxChair;
	for(int i = maxChair;i --;){
		if(between(x1+x2>>1, x, x2+x3>>1)&&between(y1+y2>>1, y, y2+y3>>1)){
			x1=x1+x2>>1;
			y1=y1+y2>>1;
			x3=x2+x3>>1;
			y3=y2+y3>>1;
		}else if(between(x2, x, x3)&&between(y1, y, y2)){
			x1=x3;
			x3=x2;
			y3=y2;
		}else if(between(x1, x, x2)&&between(y2, y, y3)){
			x3=x2;
			y1=y3;
			y3=y2;
		}else if(between(x1, x, x2)&&between(y1, y, y2)){
			x3=x2;
			y3=y2;
		}else{
			break;
		}
		x2=x1+x3>>1;
		y2=y1+y3>>1;
	}
	if(x1+1u==x2&&y1+1u==y2){
		return x+y+2u;
	}else{
		return x+y;
	}
}
int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		unsigned x, y;
		scanf("%u%u", &x, &y);
		printf("%u\n", solve(x, y));
	}
}