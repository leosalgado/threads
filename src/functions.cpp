#include <iostream>
#include <mutex>

std::mutex print_mutex;

void fib(long x){
  long sum = 0;
  int y = 0, z = 1, count = x;
  for(int i = 0; i < count; i++){
    sum = y + z;
    z = y;
    y = sum;

    std::lock_guard<std::mutex> guard(print_mutex);
    std::cout << "[T1] fib(): " << sum << std::endl;
  }
}

void mult(long n){
  int count = n;
  for (int i = 0; i < count; i++)
  {
    std::lock_guard<std::mutex> guard(print_mutex);
    std::cout << "[T2] mult(): " << n << std::endl;
    n = n << 1;
  }
  
}