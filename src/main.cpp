#include <iostream>
#include <thread>
#include "functions.h"


int main(){
  
  long num;
  
  std::cin >> num;

  std::thread first (fib, num);
  std::thread second (mult, num);

  std::cout << "Starting..." << std::endl;

  first.join();
  second.join();

  std::cout << "Finished" << std::endl;


  return 0;
}
