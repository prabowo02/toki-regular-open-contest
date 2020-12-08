n = int(input())
a = set(input().split())
print(len(a) if len(a) in (1, n) else n-1)
