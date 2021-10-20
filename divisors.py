
def printDivisors(n) :
    sum = 0
    product = 1
    i = 1
    while i <= n :
        if (n % i==0) :
            print(i)
            sum += i
            product *= i
        i = i + 1
    print("Sum of divisors:", sum)
    print("Product of divisors:", product)

printDivisors(10_000)