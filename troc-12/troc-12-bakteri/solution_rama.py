# Author   : rama_pang
# Problem  : troc-12-bakteri
# Time     : O(N M)
# Memory   : O(N M)

from sys import stdin, stdout

def main():
  N, M, K = [int(x) for x in stdin.readline().split()]
  ans = [['.' for j in range(M)] for i in range(N)]

  for i in range(N - 1, -1, -2):
    ans[i][0] = 'X'
  for i in range(M - 1, -1, -2):
    ans[0][i] = 'X'
  
  K -= sum(element.count('X') for element in ans)
  for i in range(N):
    for j in range(M):
      if ans[i][j] == '.' and K > 0:
        ans[i][j] = 'X'
        K -= 1
  
  if K < 0:
    stdout.write('TIDAK\n')
  else :
    stdout.write('YA\n')
    stdout.write('\n'.join([''.join(i) for i in ans]) + '\n')

if __name__ == '__main__':
  main()