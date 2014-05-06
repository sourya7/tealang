#include <stdio.h>

long long fib(int n){
    if(n == 0) return n;
    if(n == 1) return n;
    long long l = fib(n-1);
    long long r = fib(n-2);
    return l + r;
}

int main(int argc, char* argv[]){
    printf("%d\n", fib(atoi(argv[1])));
    return 0;
}
