n = int(input())
a = sorted([int(s) for s in input().split()])
a = [a[0]] + sorted(a[1:], reverse=True)
print(*a)
