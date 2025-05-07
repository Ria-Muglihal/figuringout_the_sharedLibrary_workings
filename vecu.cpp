#define _GNU_SOURCE
#include <dlfcn.h>
#include <iostream>
#include <thread>
#include <cstdlib>

extern volatile uint32_t T10Counter;
volatile uint32_t T10Counter = 0;

typedef void (*fptr_initialize)();
typedef int (*main_ptr)(int argc, const char *argv[]);
typedef void (*fptr_terminate)();

fptr_initialize init = 0;
main_ptr main_dll = 0;
fptr_terminate terminate = 0;

extern "C" void vecu_func() 
{   
    void* vecutasks = dlopen("./libvECUTasks.so", RTLD_NOW);

    init = (fptr_initialize)dlsym(vecutasks, "initializeDirectMode");
    main_dll = (main_ptr)dlsym(vecutasks, "main");
    terminate = (fptr_terminate)dlsym(vecutasks, "terminateDirectMode");

    T10Counter++;

    std::cout << "Taskcounter value: " << T10Counter << std::endl;
    
        // std::thread t(
        //     [&]()
        //     {
        //         const char *argv[1];
        //         argv[0] = "ProjectName.vrta_ecu";
        //         main_dll(1, const_cast<const char **>(argv));
        //     });
        // t.detach();
        
        // init();
    
    std::cout << " " << dlclose(vecutasks) << std::endl;

    
}
