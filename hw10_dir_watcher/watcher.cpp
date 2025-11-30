#include <iostream>
#include <unistd.h>
#include <sys/inotify.h>

int main(const int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./watcher <path>";
        return 1;
    }

    const int fd = inotify_init();
    if (fd < 0) {
        std::cout << "Error";
        return 1;
    }

    if (const int wd = inotify_add_watch(fd, argv[1], IN_ALL_EVENTS); wd < 0) {
        std::cout << "Error watching " << argv[1];
        return 1;
    }
    
    std::cout << "Watching: " << argv[1] << std::endl;
    
    char buffer[4096];
    
    while (true) {
        const int length = read(fd, buffer, sizeof(buffer));
        if (length < 0) {
            break;
        }
        
        int i = 0;
        while (i < length) {
            const inotify_event* event = (struct inotify_event*)&buffer[i];
            
            std::cout << "ALERT! Activity detected!" << std::endl;
            
            if (event->len > 0) {
                std::cout << "File: " << event->name << std::endl;
            }
            
            if (event->mask & IN_CREATE) {
                std::cout << "File created" << std::endl;
            }
            if (event->mask & IN_DELETE) {
                std::cout << "File deleted" << std::endl;
            }
            if (event->mask & IN_MODIFY) {
                std::cout << "File modified" << std::endl;
            }
            if (event->mask & IN_OPEN) {
                std::cout << "File opened" << std::endl;
            }
            if (event->mask & IN_ACCESS) {
                std::cout << "File accessed" << std::endl;
            }
            
            std::cout << std::endl;
            
            i += sizeof(inotify_event) + event->len;
        }
    }
    
    close(fd);
    return 0;
}