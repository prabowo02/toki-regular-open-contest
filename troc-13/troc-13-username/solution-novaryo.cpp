#include <cstdio>
using namespace std;

int N;
char a;
char last = '0';

int main() {
  scanf("%d", &N);getchar();
  for(int i = 1; i <= N; i++) {
    a = getchar();
    if(a != last)putchar(a);
    last = a;
  }
  putchar('\n');
}