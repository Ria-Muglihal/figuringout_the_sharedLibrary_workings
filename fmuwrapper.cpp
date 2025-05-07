#define _GNU_SOURCE
#include <dlfcn.h>
#include <iostream>
#include <cstdlib>

typedef void (*fptr_vecu_func)();
fptr_vecu_func vecu_func = 0;

extern "C" void fmuwrapper_func() 
{
    std::cout << "[fmuwrapper] Loading vecu.so with RTLD_GLOBAL\n";
    
    void* vecu = dlopen("./vecu.so", RTLD_GLOBAL | RTLD_NOW);
    if (!vecu) 
    {
        std::cerr << "dlopen vecu.so failed: " << dlerror() << std::endl;
        std::exit(1);
    }
    
    std::cout << "[fmuwrapper] vecu.so loaded\n";

    fptr_vecu_func vecu_func = (fptr_vecu_func)dlsym(vecu, "vecu_func");
    
    if (!vecu_func) 
    {
        std::cerr << "dlsym vecu_func failed: " << dlerror() << std::endl;
        std::exit(1);
    }
    
    vecu_func();
    std::cout << " " << dlclose(vecu) << std::endl;

}
