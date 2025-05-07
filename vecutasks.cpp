#include <iostream>
#include <csignal>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

__thread void *IcuForThisThread = nullptr;

extern "C" bool initializeDirectMode(const char* fmuCurrentLocation, const void* mdScalarVariableMap)
{
  std::cout << "decoding phase 1" << std::endl;
  return true;
}

void terminateDirectMode()
{
}

int main(int argc, const char * argv[])
{
  std::cout << "decoding phase 2" << std::endl;
  return 0;
}