# Author   : rama_pang
# Problem  : troc-12-fungsi
# Time     : O(A B log max(X, Y) + Q log max(X, Y))
# Memory   : O(A B log max(X, Y))

from sys import stdin, stdout

MAXN = 100005
BITS = 30

A, B, KA, KB, LA, LB = [0 for i in range(6)]
func = [[0 for j in range(BITS)] for i in range(MAXN)]

def Build(): # Build Sparse Table
  global A, B, KA, KB, LA, LB, func
  for a in range(A):
    for b in range(B):
      if a == KA:
        func[a * B + b][0] = LA
      elif b == KB:
        func[a * B + b][0] = LB
      else:
        func[a * B + b][0] = 1
  
  for j in range(1, BITS):
    for i in range(A * B):
      a, b = i // B, i % B
      a -= func[i][j - 1] % A
      b -= func[i][j - 1] % B
      if a < 0: a += A
      if b < 0: b += B
      func[i][j] = func[i][j - 1] + func[a * B + b][j - 1]

def FindDepth(X): # Find number of iteration of while loop in func() that X > 0 holds
  global A, B, KA, KB, LA, LB, func
  depth = 0
  for j in range(BITS - 1, -1, -1):
    if X > func[(X % A) * B + (X % B)][j]:
      X -= func[(X % A) * B + (X % B)][j]
      depth |= 1 << j

  return depth

def Lift(X, D): # Do D number of iterations of func()'s while loop on X
  global A, B, KA, KB, LA, LB, func
  for j in range(BITS):
    if (D & (1 << j)) > 0:
      X -= func[(X % A) * B + (X % B)][j]

  return X

def Query(X, Y): # Find Lowest Common Ancestor of X and Y by binary lifting
  global A, B, KA, KB, LA, LB, func
  DX, DY = FindDepth(X), FindDepth(Y)
  if DX > DY:
    X, Y = Y, X
    DX, DY = DY, DX
  
  if Lift(X, DX) != Lift(Y, DY): 
    return -1;
  
  Y = Lift(Y, DY - DX)

  for j in range(BITS - 1, -1, -1):
    if X - func[(X % A) * B + (X % B)][j] != Y - func[(Y % A) * B + (Y % B)][j]:
      X -= func[(X % A) * B + (X % B)][j]
      Y -= func[(Y % A) * B + (Y % B)][j]

  if X != Y:
    X -= func[(X % A) * B + (X % B)][0]

  return X

def main():
  global A, B, KA, KB, LA, LB, func
  A, B, KA, KB, LA, LB = [int(x) for x in stdin.readline().split()]
  Build()
  Q = int(stdin.readline())
  for i in range(Q):
    X, Y = [int(x) for x in stdin.readline().split()]
    stdout.write(str(Query(X, Y)) + '\n')

if __name__ == '__main__':
  main()