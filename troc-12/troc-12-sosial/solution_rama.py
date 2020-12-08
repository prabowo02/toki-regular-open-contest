# Author   : rama_pang
# Problem  : troc-12-sosial
# Time     : O(N)
# Memory   : O(N)

from sys import stdin, stdout

def main():
  N = int(stdin.readline());
  A = [int(x) for x in stdin.readline().split()]
  S = 0
  for i in range(N + 1):
    S += A[i] * (2 ** i)
  
  if S % (2 ** N) == 0:
    stdout.write(str(S // (2 ** N)) + "\n")
  else:
    stdout.write("-1\n")

if __name__ == '__main__':
  main()