#include <cstdio>

int main(){
	int n;
	scanf("%d", &n);
	if(n==0){
		printf("1\n");
	}else if(n==1){
		printf("0\n");
	}else if(n&1){
		printf("4");
		for(int i = 0;i < n/2;i ++){
			printf("8");
		}
		printf("\n");
	}else{
		for(int i = 0;i < n/2;i ++){
			printf("8");
		}
		printf("\n");
	}
	return 0;
}