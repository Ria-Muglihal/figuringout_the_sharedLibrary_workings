#define _GNU_SOURCE
#include <dlfcn.h>
#include <iostream>
#include <cstdlib>

int main() 
{
    std::cout << "[silcontroller] Loading fmuwrapper.so with RTLD_LOCAL\n";
    
    void* fmuwrapper = dlopen("./fmuwrapper.so", RTLD_LOCAL | RTLD_NOW);
    if (!fmuwrapper) 
    {
        std::cerr << "dlopen fmuwrapper.so failed: " << dlerror() << std::endl;
        std::exit(1);
    }
    
    std::cout << "[silcontroller] fmuwrapper.so loaded\n";

    using FuncType = void(*)();
    FuncType fmuwrapper_func = reinterpret_cast<FuncType>(dlsym(fmuwrapper, "fmuwrapper_func"));
    if (!fmuwrapper_func) {
        std::cerr << "dlsym fmuwrapper_func failed: " << dlerror() << std::endl;
        std::exit(1);
    }
    
    fmuwrapper_func();

    std::cout << " " << dlclose(fmuwrapper) << std::endl;

    // Launching again...

    std::cout << "[silcontroller] Loading fmuwrapper.so with RTLD_LOCAL\n";
    
    void* fmuwrapper_ = dlopen("./fmuwrapper.so", RTLD_LOCAL | RTLD_NOW);
    if (!fmuwrapper_) 
    {
        std::cerr << "dlopen fmuwrapper.so failed: " << dlerror() << std::endl;
        std::exit(1);
    }
    
    std::cout << "[silcontroller] fmuwrapper.so loaded\n";

    using FuncType_ = void(*)();
    FuncType_ fmuwrapper_func_ = reinterpret_cast<FuncType_>(dlsym(fmuwrapper_, "fmuwrapper_func"));
    if (!fmuwrapper_func_) {
        std::cerr << "dlsym fmuwrapper_func failed: " << dlerror() << std::endl;
        std::exit(1);
    }
    
    fmuwrapper_func_();

    std::cout << " " << dlclose(fmuwrapper_) << std::endl;

    return 0;
}
