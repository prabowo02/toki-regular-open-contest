N, A, S = int(input()), [int(x) for x in input().split()], 0
for i in range(N): S += (i == 0 or A[i - 1] != A[i])
print("NO" if N > 4 and S > 3 else "YES")
