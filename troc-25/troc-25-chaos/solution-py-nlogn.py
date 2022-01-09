n = int(input())
A = list(map(int, input().split()))

L = [0 for _ in range(n)]

for i in range(1, n):
	L[i] = L[i - 1] + (A[i - 1] + 1)

ok = 1
for i in range(n):
	if A[i] > L[i]:
		z = i
		r = [0 for _ in range(n + 1)]
		r[z + 1] = 0
		for i in range(z + 2, n):
			r[i] = r[i - 1]
			if A[i - 1] <= r[i - 1]:
				r[i] += 1

		R = 0
		for i in range(z + 1, n):
			R += max(0, A[i] - r[i])

		if L[z] + R < A[z]:
			ok = 0
			break

if ok == 1:
	print("YES")
else:
	print("NO")

