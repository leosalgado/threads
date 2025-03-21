#include <iostream>
#include "functions.h"

void fib(long x){
  long sum = 0;
  int y = 0, z = 1, count = x;
  for(int i = 0; i < count; i++){
    sum = y + z;
    z = y;
    y = sum;

    std::cout << "thread1: " << sum << std::endl;
  }
}

void mult(long n){
  int count = n;
  for (int i = 0; i < count; i++)
  {
    std::cout << "thread2: " << n << std::endl;
    n = n << 1;
  }
  
}