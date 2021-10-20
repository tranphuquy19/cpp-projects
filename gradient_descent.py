# linear

import numpy as np

def gradientDescent(x, y):
    theta1 = theta2 = 0
    max_loops = 1000
    e = 0.001
    n = len(x)
    for i in range(max_loops):
        y_predicted = theta1 * x + theta2
        # print(y_predicted)
        md = (-2 / n) * sum(x * (y - (y_predicted)))
        bd = (-2 / n) * sum(y - (y_predicted))
        # print(md,bd)
        theta1 = theta1 - e * md
        theta2 = theta2 - e * bd

        cost = 1 / n * sum([val ** 2 for val in (y - y_predicted)])
        print("m => {} b => {} loop => {} cost => {} ".format(theta1,theta2,i,cost))

    return theta1, theta2


x = np.array([1, 2, 3, 4, 5])
y = np.array([2, 4, 6, 8, 10])

t1, t2 = gradientDescent(x, y)
print("t1 => {} t2 => {}".format(t1, t2))
print(t1 * x + t2)