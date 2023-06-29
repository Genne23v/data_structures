/**************************************************/
/*                                                */
/*  Lab 1 Starter file                            */
/*                                                */
/*  Name: Wonkeun No                              */
/*  Student number: 145095196                     */
/*                                                */
/**************************************************/

/* remember to code these in an iterative only manner*/

unsigned long long factorial (unsigned int n){
    long long sum = 1;

    for (int i=n; i>0; i--){
        sum *= i;
    }
    return sum;
}

unsigned long long power (unsigned int base, unsigned int n){
    long long sum = 1;

    for (int i=0; i<n; i++){
        sum *= base;
    }
    return sum;
}
unsigned long long fibonacci (unsigned int n){
    if (n == 0) return 0;
    if (n == 1) return 1;

    long long fib1 = 0;
    long long fib2 = 1;
    long long fib_next = fib1 + fib2;

    for (int i=0; i<=n-2; i++){
        fib_next = fib1 + fib2;
        fib1 = fib2;
        fib2 = fib_next;
    }
    return fib_next;
}