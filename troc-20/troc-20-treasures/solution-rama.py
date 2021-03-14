import sys

def find_SCC(graph):
  SCC, S, P = [], [], []
  depth = [0] * len(graph)

  stack = list(range(len(graph)))
  while stack:
    node = stack.pop()
    if node < 0:
      d = depth[~node] - 1
      if P[-1] > d:
        SCC.append(S[d:])
        del S[d:], P[-1]
        for node in SCC[-1]:
          depth[node] = -1
    elif depth[node] > 0:
      while P[-1] > depth[node]:
        P.pop()
    elif depth[node] == 0:
      S.append(node)
      P.append(len(S))
      depth[node] = len(S)
      stack.append(~node)
      stack += graph[node]
  return SCC[::-1]

def main():
  N, M = [int(x) for x in sys.stdin.readline().split()]
  T, X, Y, Z = [[0 for j in range(M)] for i in range(4)]
  for i in range(M):
    T[i], X[i], Y[i], Z[i] = [int(x) for x in sys.stdin.readline().split()]
    T[i] -= 1
    X[i] -= 1
    Y[i] -= 1

  mn, mx = min(Z), max(Z)
  lower = [mn for i in range(N)]
  upper = [mx for i in range(N)]

  for i in range(M):
    if T[i] == 0:
      upper[X[i]] = min(upper[X[i]], Z[i])
      upper[Y[i]] = min(upper[Y[i]], Z[i])
    else:
      lower[X[i]] = max(lower[X[i]], Z[i])
      lower[Y[i]] = max(lower[Y[i]], Z[i])

  for i in range(N):
    if lower[i] > upper[i]:
      print("NO")
      return

  adj = [[] for i in range(2 * N)]
  def eitherOr(x, y):
    x = max(2 * x, -1 - 2 * x)
    y = max(2 * y, -1 - 2 * y)
    adj[x ^ 1].append(y)
    adj[y ^ 1].append(x)

  for i in range(M):
    cntX = (lower[X[i]] == Z[i]) + (upper[X[i]] == Z[i])
    cntY = (lower[Y[i]] == Z[i]) + (upper[Y[i]] == Z[i])
    if cntX == 0 and cntY == 0:
      print("NO")
      return
    elif cntX != 0 and cntY == 0:
      eitherOr((~X[i] if lower[X[i]] == Z[i] else X[i]), (~X[i] if lower[X[i]] == Z[i] else X[i]))
    elif cntX == 0 and cntY != 0:
      eitherOr((~Y[i] if lower[Y[i]] == Z[i] else Y[i]), (~Y[i] if lower[Y[i]] == Z[i] else Y[i]))
    elif cntX != 0 and cntY != 0:
      eitherOr((~X[i] if lower[X[i]] == Z[i] else X[i]), (~Y[i] if lower[Y[i]] == Z[i] else Y[i]))

  comps = find_SCC(adj)
  comp = [-1 for i in range(2 * N)]
  for i in range(len(comps)):
    for j in comps[i]:
      comp[j] = i

  for i in range(N):
    if comp[i * 2] == comp[i * 2 + 1]:
      print("NO")
      return

  print("YES")
  return

if __name__ == '__main__':
  main()
