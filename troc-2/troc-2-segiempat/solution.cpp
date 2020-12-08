#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int N, M;
int A, B;
int main(){
  scanf("%d%d", &N, &M);
  scanf("%d%d", &A, &B);
  printf("%d\n", max((N / A) * (M / B), (N / B) * (M / A))); 
  return 0;
}