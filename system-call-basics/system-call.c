//Address of the block is passed as parameters

#include <stdio.h>
#include <fcntl.h>

int main() {
    const char *pathname = "example.txt";
    int flags = O_RDONLY;
    mode_t mode = 0644;

    int params[3];
          // Block of data(parameters) in array
    params[0] = (int)pathname;
    params[1] = flags;
    params[2] = mode;

    int fd = syscall(SYS_open, params);
          // system call

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // File operations here...

    close(fd);
    return 0;
}