#include <cstdio>

int main(){
	int a, b, c, d, e, f;
	scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f);
	int twice_answer=0;
	int twice_width=a*2;
	for(int i = 1;i < b+c;i ++){
		twice_answer+=twice_width;
		if(i<b){
			twice_width++;
		}else{
			twice_width--;
		}
		if(i<f){
			twice_width++;
		}else{
			twice_width--;
		}
	}
	printf("%d\n", twice_answer/2);
}