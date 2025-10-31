#include "unistd.h"
#include "fcntl.h"
#include "iostream"

int do_magic()
{
    const int fd = open("new_pts", O_RDONLY);
    if (fd < 0)
    {
        perror("Something went wrong while opening the file ;(");
        return 1;
    }

    dup2(fd, STDIN_FILENO);
    close(fd);
    return 0;
}
