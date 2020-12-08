#include <iostream>
#include <cctype>

int main(){
	char s[101], t[101];
	std::cin>>s>>t;
	for(int i = 0;;i ++){
		if(tolower(s[i])!=tolower(t[i])){
			printf("x_x\n");
			return 0;
		}
		if(s[i]=='\0')
			break;
	}
	printf("20/20\n");
	return 0;
}
