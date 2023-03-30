N = 500000000
DX = 1/N


def f(x): return 4.0/(1+x*x)


PI = 0
for i in range(N):
    PI += f((i+0.5)*DX)
PI *= DX

print(PI)