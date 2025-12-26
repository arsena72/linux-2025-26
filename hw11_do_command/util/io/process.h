#pragma once
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

inline int do_command(const char* command) {
    if (command == nullptr) return 1;

    switch (const pid_t pid = fork())
    {
    case -1:
        return -1;
    case 0:
        execl("/bin/sh", "sh", "-c", command, static_cast<char*>(nullptr));

        _exit(127);
    default:
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            return -1;
        }

        return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    }
}