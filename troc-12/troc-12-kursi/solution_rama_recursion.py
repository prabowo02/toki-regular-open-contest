# Author   : rama_pang
# Problem  : troc-12-kursi
# Time     : O(Q log max(X, Y))
# Memory   : O(log max(X, Y))

from sys import stdin, stdout

def Solve(X, Y, T, L):
  # T = 0: detect form (1, 1), T = 1: detect form (3, 1)
  # T = 2: detect form (1, 3), T = 3: detect form (7, 3)
  if X == 0 or Y == 0: return False
  while L > 2 and L // 2 > max(X, Y): L //= 2
  if X == L // 2 and Y == L // 2: return T == 0
  if X == L // 2 or  Y == L // 2: return False
  if X >= L // 2 and Y >= L // 2: return Solve(X - L // 2, Y - L // 2, T, L)
  if X >= L // 2 and Y <= L // 2: return Solve(L - X, Y, T ^ 1, L)
  if X <= L // 2 and Y >= L // 2: return Solve(X, L - Y, T ^ 2, L)

def main():
  Q = int(stdin.readline())
  L = 2 ** 30
  for i in range(Q):
    X, Y = [int(x) for x in stdin.readline().split()]
    stdout.write(str(X + Y + 2 * Solve(X, Y, 0, L)) + '\n')

if __name__ == '__main__':
  main()
