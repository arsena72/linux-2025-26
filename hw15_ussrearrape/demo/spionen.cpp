#include <iostream>
#include <csignal>
#include <unistd.h>

static volatile sig_atomic_t last_commander = 0;

void on_sigusr1(int, siginfo_t* info, void*) {
    last_commander = info->si_pid;
    kill(last_commander, SIGUSR2);
}

int main() {
    struct sigaction sa{};
    sa.sa_sigaction = on_sigusr1;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGUSR1, &sa, nullptr);

    std::cout << "Target process live. PID: " << getpid() << std::flush;

    while (true) {
        pause();
    }

    return 0;
}
