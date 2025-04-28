#include <iostream>
#include <csignal>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

// Simulated interrupt manager type
struct TInterruptManager {
    int id;
};

// Static __thread TLS variable (like your IcuForThisThread)
static __thread TInterruptManager* IcuForThisThread = nullptr;

// Simple signal spec struct to mimic your SignalConfiguration
struct signal_spec {
    unsigned int magic;
};

static signal_spec SignalConfiguration[32];  // Simplified signal config array

// Signal handler that accesses TLS variable
static void SignalCatcher(int signal, siginfo_t* signal_info, void* pUContext) {
    signal_spec* int_info = &SignalConfiguration[signal];
    pthread_t this_thread = pthread_self();

    if (int_info->magic != 0xdeadbeef) {
        std::cerr << "******* SignalCatcher has bad magic " << std::hex << int_info->magic << std::endl;
        abort();
    }

    std::cout << "[vecutasks] SignalCatcher: signal " << signal
              << ", thread " << this_thread
              << ", IcuForThisThread id = "
              << (IcuForThisThread ? IcuForThisThread->id : -1)
              << std::endl;
}

// Function to install the signal handler for SIGUSR1
static void install_signal_handler() {
    struct sigaction sa;
    sa.sa_sigaction = SignalCatcher;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO | SA_RESTART;

    if (sigaction(SIGUSR1, &sa, nullptr) != 0) {
        perror("sigaction");
        std::exit(1);
    }

    // Initialize SignalConfiguration for SIGUSR1
    SignalConfiguration[SIGUSR1].magic = 0xdeadbeef;
}

// Exported function called from vecu.so or main program
extern "C" void vecutasks_func() {
    static bool initialized = false;
    if (!initialized) {
        install_signal_handler();
        initialized = true;
        std::cout << "[vecutasks] Signal handler installed\n";
    }

    // Initialize TLS variable for this thread
    if (!IcuForThisThread) {
        IcuForThisThread = new TInterruptManager();
        IcuForThisThread->id = (int)pthread_self();
        std::cout << "[vecutasks] Initialized IcuForThisThread with id " << IcuForThisThread->id << std::endl;
    } else {
        std::cout << "[vecutasks] IcuForThisThread already initialized with id " << IcuForThisThread->id << std::endl;
    }

    std::cout << "[vecutasks] vecutasks_func returning\n";
}
