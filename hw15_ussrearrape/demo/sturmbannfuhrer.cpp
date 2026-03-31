#include <iostream>
#include <vector>
#include <csignal>
#include <unistd.h>

static volatile sig_atomic_t signal_received = 0;

void on_sigusr2(int) {
    signal_received = 1;
}

int main(const int argc, char* argv[]) {
    std::signal(SIGUSR2, on_sigusr2);

    std::cout << "Tracker PID: " << getpid() << "\n";

    for (int i = 1; i < argc; ++i) {
        pid_t target = std::stoi(argv[i]);
        signal_received = 0;

        if (kill(target, SIGUSR1) != 0) continue;

        usleep(100000);

        if (signal_received) {
            std::cout << "Target identified: " << target << " - Terminating...";
            kill(target, SIGILL);
            return 0;
        }
    }

    std::cout << "No target identified in the provided list.";
    return 1;
}
