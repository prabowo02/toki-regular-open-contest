/* Author: maximath_1 */
#include <stdio.h>
#include <string.h>
using namespace std;
int main(){
	char s[105]; scanf("%s", s);
	int x=0, y=0, n=strlen(s);
	for(int i=0; i<n; i++){
		if(s[i]=='R') x++;
		if(s[i]=='L') x--;
		if(s[i]=='U') y++;
		if(s[i]=='D') y--;
	}
	printf("%d %d\n", x, y);
	return 0;
}
