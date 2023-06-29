/**************************************************/
/*                                                */
/*  Lab 2 Starter file                            */
/*                                                */
/*  Name: Wonkeun No                              */
/*  Student number: 145095196                     */
/*                                                */
/**************************************************/

/* remember to code these in a RECURSIVE only manner*/

unsigned long long factorial (unsigned int n){
    if (n == 0){
        return 1;
    } else {
        return n * factorial(n-1);
    }
}

unsigned long long power (unsigned int base, unsigned int n){
    if (n == 0){
        return 1;
    }
    return base * power(base, n-1);
}
unsigned long long fibonacci (unsigned int n){ 
    if (n <= 1){
        return n;
    }
    return fibonacci(n-1) + fibonacci(n-2);
}