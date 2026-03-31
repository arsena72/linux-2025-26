#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t target_pid = fork();
    if (target_pid == 0) {
        execl("./spionen", "spionen", nullptr);
        return 1;
    }

    usleep(100000);

    std::vector<int> pids;
    pids.push_back(target_pid);
    pids.push_back(99990);
    pids.push_back(99991);
    pids.push_back(99992);
    pids.push_back(99993);

    std::ranges::shuffle(pids, std::mt19937(std::random_device{}()));

    std::ofstream f("/tmp/pids.txt");
    for (int p : pids) f << p << " ";
    f.close();

    std::cout << "Target PID: " << target_pid << " logged to /tmp/pids.txt";

    std::vector<std::string> arg_strings = {"./tracker"};
    for (int p : pids) arg_strings.push_back(std::to_string(p));

    std::vector<char*> argv;
    for (auto& s : arg_strings) argv.push_back(s.data());
    argv.push_back(nullptr);

    pid_t tracker_pid = fork();
    if (tracker_pid == 0) {
        execv(argv[0], argv.data());
        return 1;
    }

    waitpid(tracker_pid, nullptr, 0);
    waitpid(target_pid, nullptr, 0);

    std::cout << "Tasks complete.";
    return 0;
}
