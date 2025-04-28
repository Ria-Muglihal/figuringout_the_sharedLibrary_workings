#define _GNU_SOURCE
#include <dlfcn.h>
#include <iostream>
#include <cstdlib>

extern "C" void vecu_func() {
    std::cout << "[vecu] Loading vecutasks.so with dlmopen and RTLD_DEEPBIND\n";
    // In vecu.cpp
    void* vecutasks = dlmopen(LM_ID_NEWLM, "./vecutasks.so", RTLD_DEEPBIND | RTLD_NOW);
    // void* vecutasks = dlopen("./vecutasks.so", RTLD_NOW);
    if (!vecutasks) {
        std::cerr << "dlmopen vecutasks.so failed: " << dlerror() << std::endl;
        std::exit(1);
    }
    std::cout << "[vecu] vecutasks.so loaded in new namespace\n";

    using FuncType = void(*)();
    FuncType vecutasks_func = reinterpret_cast<FuncType>(dlsym(vecutasks, "vecutasks_func"));
    if (!vecutasks_func) {
        std::cerr << "dlsym vecutasks_func failed: " << dlerror() << std::endl;
        std::exit(1);
    }

    std::cout << "[vecu] Calling vecutasks_func...\n";
    vecutasks_func();
    
    dlclose(vecutasks);
    char *msg = dlerror();
    std::cout << msg;
}
