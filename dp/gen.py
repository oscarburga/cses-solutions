from random import randint
import resource, sys
resource.setrlimit(resource.RLIMIT_STACK, (2**29, -1))
sys.setrecursionlimit(10**7)

n = 20
w = randint(1, 10**9)
print(n, w)
for i in range(n): print(randint(1, w), end = ' \n'[i+1==n])
