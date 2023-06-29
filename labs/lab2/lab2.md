## Factorial Analysis
```cpp
unsigned long long factorial (unsigned int n){
    if (n == 0){                        //1
        return 1;                       //Return only in last call
    } else {                            //
        return n * factorial(n-1);      //3 + T(n-1)
    }
}
```

Let $n$ represent the value we are finding the factorial for. 

Let $T(n)$ represent number of operations needed to find  using the code.

$T(n) = 4 + T(n-1)$

$T(n) = 4 + 4 + T(n-2)$

$T(n) = 4 + 4 + 4 + ... + 2$

$T(n) = 4(n-1) + 2$

$T(n) = 4n -2$

$T(n)$ is $O(n)$

## Power Analysis 
```cpp 
unsigned long long power (unsigned int base, unsigned int n){
    if (n == 0){                        //1
        return 1;                       //Return only in last call
    }
    return base * power(base, n-1);     //3 + T(n-1)
}
```

Let $n$ represent the value we are finding the sum of base multiplied n times for. 

Let $T(n)$ represent number of operations needed to find  using the code.

$T(n) = 4 + T(n-1)$

$T(n) = 4 + 4 + T(n-2)$

$T(n) = 4 + 4 + 4 + ... + 2$

$T(n) = 4(n-1) + 2$

$T(n) = 4n -2$

$T(n)$ is $O(n)$

## Fibonacci Analysis
```cpp 
unsigned long long fibonacci (unsigned int n){
    if (n <= 1){                                //1
        return n;                               //Return only in last call
    } 
    return fibonacci(n-1) + fibonacci(n-2);     //3 + T(n-1) + T(n-2)
}
```
Let $n$ represent the value we are finding the fibonacci for. 

Let $T(n)$ represent number of operations needed to find  using the code.

$T(n) = 4 + T(n-1) + T(n-2)$

$T(n) = 4 + 4 + T(n-2) + T(n-3) + 4 + T(n-3) + T(n-4)$

$T(n) = 4 + (4 + 4 + T(n-3) + T(n-4) + 4 + T(n-4) + T(n-5) + ... + 2 + 2) + 4 + (4 + 4 + T(n-4) + T(n-5) + 4 + T(n-5) + T(n-6) + ... + 2 + 2)$ 

$T(n)$ are increased by $2^n$ times

$T(n) = 4(2^{n} -2)$

$T(n) = 4 * 2^{n} - 8$

$T(n)$ is $O(2^n)$

## Reflection

Recursive function is not easy at the beginning. It needs some intuition. I struggled to figure it out when I tried recursive programming before, but now I feel mmuch more comfortable to use the recursive in these cases. 

It wrote some notes on my notepad for fibonaci analysis. I could see the amount of operation increated exponentially. But I couldn't get some of the details to figure out accurate formula. 

fibonaci(20) took about 0.6 microsecond. Every time I increased the number by 5, runtime was increased significantly. Surprisingly fibonaci(45) took 8 seconds. The runtime data that I had is as below. 

![fibonaci_graph](https://user-images.githubusercontent.com/59734889/191378798-917df5b4-863b-487f-a9fa-9a2f0f5a327d.png)

I was thinking recursive solution would take expotentially increasing runtime, but it takes more longer time than I expected. 

## Challenge
There is only big O notation better than O(n) which is O(log n). To achieve this, I should divide the number of data n by half in each loop. I updated my power function as below. 

```cpp
unsigned long long power2 (unsigned int base, unsigned int n){
    if (n == 0) return 1;                                   //1 * log n
	int recursieve = power2(base, n/2);                     //2 * log n
	if (n % 2 == 0) return recursieve * recursieve;         //2 * log n
	return recursieve * recursieve * base;                  //Worst case scenario 3 * log n
}
```

Eventually I will end up with $8(log n)$ that is $O(log n)$. And I tested my function using lab2timing file. When I set `n` to `19,500`, original function took *0.0008 seconds* while enhanced version took *0.33 microsecond* which is much faster. I could see when `n` gets bigger, the runtime gap between original power function and enhanced version is greater.  
