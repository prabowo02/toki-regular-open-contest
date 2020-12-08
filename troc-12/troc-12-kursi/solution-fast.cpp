//O(1) processing time complexity
#include <cstdio>
#include <algorithm>
using namespace std;

int main(){
	int q;
	scanf("%d", &q);
	while(q--){
		int x, y;
		scanf("%d%d", &x, &y);
		if(x>y)swap(x, y);
		if(x==0){
			printf("%d\n", y);
			continue;
		}
		if(x==y){
			printf("%d\n", x+y+2);
			continue;
		}
		if(y-x&3){
			printf("%d\n", x+y);
			continue;
		}
		int k=(y-x)&(x-y);
		if(x%k<k/2&&x%k){
			printf("%d\n", x+y+2);
		}else{
			printf("%d\n", x+y);
		}
	}
}