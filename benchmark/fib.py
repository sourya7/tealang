
def fib(n):
    if n == 0:
        return 0;
    if n == 1:
        return 1;
    l = fib(n - 1)
    r = fib(n - 2)
    return l + r

if __name__ == "__main__":
    print(fib(40))
