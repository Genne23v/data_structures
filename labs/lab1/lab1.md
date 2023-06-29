## Factorial Analysis 
```cpp
unsigned long long factorial (unsigned int n){
    long long sum = 1;          //1

    for (int i=n; i>0; i--){    //1 + n + n
        sum *= i;               //2n
    }
    return sum;                 //1
}
```

Let $n$ represent the value we are finding the factorial for. 

Let $T(n)$ represent number of operations needed to find  using the code.

$T(n) = 1 + 1 + n + n + 2n + 1$

$T(n) = 4n + 3$

$T(n)$ is $O(n)$

## Power Analysis
```cpp
unsigned long long power (unsigned int base, unsigned int n){
    long long sum = 1;          //1

    for (int i=0; i<n; i++){    //1 + n + n
        sum *= base;            //2n
    }
    return sum;                 //1
}
```

Let $n$ represent the value we are finding the sum of base multiplied n times for. 

Let $T(n)$ represent number of operations needed to find  using the code.

$T(n) = 1 + 1 + n + n + 2n + 1$

$T(n) = 4n + 3$

$T(n)$ is $O(n)$

## Fibonaci Analysis
```cpp
unsigned long long fibonacci (unsigned int n){
    if (n == 0) return 0;                 //1 for worst case
    if (n == 1) return 1;                 //1 for worst case

    long long fib1 = 0;                   //1
    long long fib2 = 1;                   //1
    long long fib_next = fib1 + fib2;     //2

    for (int i=0; i<=n-2; i++){           //1 + (n-1) + (n-1)
        fib_next = fib1 + fib2;           //2(n-1)
        fib1 = fib2;                      //(n-1)
        fib2 = fib_next;                  //(n-1)
    }
    return fib_next;                      //1
}
```
Let $n$ represent the value we are finding the fibonacci for. 

Let $T(n)$ represent number of operations needed to find  using the code.

$T(n) = 1 + 1 + 1 + 1 + 2 + 1 + (n-1) + (n-1) + 2(n-1) + (n-1) + (n-1) + 1$

$T(n) = 6n + 2$

$T(n)$ is $O(n)$

## Challenge Analysis
```cpp
unsigned int challenge(unsigned int data[], unsigned int numData, unsigned int goal){
	unsigned int answer = 0;                        	//1
	        
	for (int i=0; i<numData; i++){                  	//1 + n + n
		for (int j=1; j<numData; j++){              	//1 + (n-1) + (n-1)
			if (data[i]+data[j] == goal){           //2(n-1)
				answer = data[i] * data[j];     //2
			}
		}
	}
	return answer;                                  	//1
}
```
Let $n$ represent the number of data in the array we are finding two numbers matching with goal for. 

Let $T(n)$ represent number of operations needed to find  using the code.

$T(n) = 1 + 1 + n + n + 1 + (n-1) + (n-1) + 2(n-1) + 2 + 1$

$T(n) = 6n + 2$

$T(n)$ is $O(n)$
