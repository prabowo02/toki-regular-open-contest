#include <cstdio>
int main(){
	int n, k, l;
	scanf("%d%d%d", &n, &k, &l);
	printf(n-1<=k||l<=k?"A\n":"B\n");
}