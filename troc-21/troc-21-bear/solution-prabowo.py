N, D = [int(s) for s in input().split()]
A = {int(s) for s in input().split()}
print(len(A & {a + D for a in A}))
