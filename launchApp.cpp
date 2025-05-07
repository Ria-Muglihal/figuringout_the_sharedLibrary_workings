#include <iostream>
#include <unistd.h>     // fork, exec
#include <sys/wait.h>   // waitpid
#include <signal.h>     // kill
#include <cstdlib>      // exit
#include <chrono>
#include <thread>

void launchAndManageProcess(const char* appPath, char* const argv[]) {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Failed to fork." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        execv(appPath, argv);
        std::cerr << "Failed to exec." << std::endl;
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        std::cout << "Launched process with PID: " << pid << std::endl;

        // Wait 5 seconds to simulate waiting or running time
        std::this_thread::sleep_for(std::chrono::seconds(5));

        // Check if process is still running
        int status;
        pid_t result = waitpid(pid, &status, WNOHANG);
        if (result == 0) {
            std::cout << "Process still running. Killing PID: " << pid << std::endl;
            kill(pid, SIGKILL);
            waitpid(pid, &status, 0);  // Clean up zombie process
        } else {
            std::cout << "Process already exited." << std::endl;
        }
    }
}

int main() {
    const char* appPath = "./silcontroller"; // Replace with your application
    char* args[] = { const_cast<char*>(appPath), nullptr };

    std::cout << "First launch..." << std::endl;
    launchAndManageProcess(appPath, args);

    std::cout << "\nLaunching again..." << std::endl;
    launchAndManageProcess(appPath, args);

    return 0;
}
