#include <iostream>
#include <thread>
#include "functions.h"


int main(){
  
  long num;
  
  std::cin >> num;
  
  std::cout << "Starting..." << std::endl;

  std::thread first (fib, num);
  std::thread second (mult, num);


  first.join();
  second.join();

  std::cout << "Finished" << std::endl;


  return 0;
}
