N = int(input())
a = [int(s) for s in input().split()]

if sorted(a)[0] == sorted(a)[-1]:
    print('EQUAL')
elif a == sorted(a):
    print('NONDECREASING')
elif a == sorted(a)[::-1]:
    print('NONINCREASING')
else:
    print('NONE')
