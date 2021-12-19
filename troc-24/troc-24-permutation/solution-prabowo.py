input()
print(sum([1 for a, b in zip(input().split(), input().split()) if a == b]))
