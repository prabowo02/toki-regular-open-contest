N, M = input().split()
print("NO" if sum([sum([int(x) for x in input().split()]) for i in range(int(N))]) == 0 else "YES")
