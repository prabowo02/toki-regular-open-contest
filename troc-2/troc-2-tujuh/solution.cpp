#include <iostream>
#include <cstdio>

using namespace std;

int main(){
  int n;
  scanf("%d", &n);
  printf("%d\n", n - 1);
  for(int i = 2;i < n; ++i) printf("1 ");
  puts("2");
  return 0;
}