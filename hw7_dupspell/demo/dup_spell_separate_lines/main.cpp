#include <unistd.h>
#include <fcntl.h>
#include <iostream>

int main()
{
    const auto filename = "exclusive_file.log";

    // write-only, create if the file doesn't exist, erase if smth is written there, read/write perms
    const int fd1 = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd1 < 0) {
        perror("Something went wrong while opening the file ;(");
        return 1;
    }

    const int fd2 = dup(fd1);
    if (fd2 < 0) {
        perror("Something went wrong while *dupping* ;(");
        close(fd1);
        return 1;
    }

    write(fd1, "First line.\n", 12);
    write(fd2, "Second line.\n", 13);

    close(fd1);
    close(fd2);
    return 0;
}