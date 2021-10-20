'''
    f(x) = (1 - 2 / (e^x) )^2
=>  f'(x) = 4 * (e^(-2x)) * (e^x - 2)
'''

import math

E = math.e

def grad(x):
    return 4.0*(E**(-2.0*x)) * ((E ** x) - 2.0)

def cost(x):
    return (1.0 - 2.0 / (E ** x))**2.0

def GD(eta, x0):
    x = [x0]
    for it in range(100):
        x_new = x[-1] - eta*grad(x[-1])
        if abs(grad(x_new)) < 1e-3:
            break
        x.append(x_new)
    return (x, it)


#innit with x0 = 5 and n=0.01
(x1, it1) = GD(.01, 5)
#innit with x0 = 5 and n= 0.07
(x2, it2) = GD(.07, 5)
print('Solution x1 = %f, cost = %f, obtained after %d loops'%(x1[-1], cost(x1[-1]), it1))
print('Solution x2 = %f, cost = %f, obtained after %d loops'%(x2[-1], cost(x2[-1]), it2))
