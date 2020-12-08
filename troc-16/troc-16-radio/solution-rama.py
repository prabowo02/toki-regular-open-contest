from sys import stdin, stdout

def main():
  N, M, R = [int(x) for x in stdin.readline().split()]
  X, Y = [[0 for i in range(N)] for j in range(2)]
  A, B, C = [[0 for i  in range(M)] for j in range(3)]

  for i in range(N):
    X[i], Y[i] = [int(x) for x in stdin.readline().split()]

  for i in range(M):
    A[i], B[i], C[i] = [int(x) for x in stdin.readline().split()]

  mask_all = (1 << M) - 1
  dp = [0 for i in range(1 << M)]
  ans = [-1 for i in range(N + 1)]
  
  for i in range(N):
    mask, x, y = 0, X[i], Y[i]
    for j in range(M):
      dx, dy = x - A[j], y - B[j]
      if dx * dx + dy * dy <= R * R:
        mask |= 1 << j
    dp[mask ^ mask_all] += 1
  
  for i in range(M):
    for mask in reversed(range(1 << M)):
      if ((mask >> i) & 1) == 0:
        dp[mask] += dp[mask ^ (1 << i)]

  for mask in range(1 << M):
    cost = 0
    for i in range(M):
      if ((mask >> i) & 1) == 1:
        cost += C[i]
    cnt = N - dp[mask]
    if ans[cnt] == -1 or ans[cnt] > cost:
      ans[cnt] = cost

  for i in reversed(range(N)):
    if ans[i + 1] != -1 and (ans[i] == -1 or ans[i] > ans[i + 1]):
      ans[i] = ans[i + 1]

  for i in range(1, N + 1):
    stdout.write(str(ans[i]) + '\n')
    
if __name__ == '__main__':
  main()
