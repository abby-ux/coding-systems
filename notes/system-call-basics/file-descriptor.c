#include <fcntl.h>    // For open()
#include <unistd.h>   // For read() and close()
#include <stdio.h>    // For printf()

int main() {
    int fd = open("example.txt", O_RDONLY);  // Open the file for reading

    if (fd < 0) {
        // If open() fails, it returns -1
        perror("Failed to open file");
        return 1;
    }

    char buffer[100];  // Buffer to store the data we read
    int bytesRead = read(fd, buffer, sizeof(buffer) - 1);  // Read from the file

    if (bytesRead < 0) {
        perror("Failed to read file");
        close(fd);  // Don’t forget to close the file
        return 1;
    }

    buffer[bytesRead] = '\0';  // Null-terminate the string
    printf("File contents: %s\n", buffer);

    close(fd);  // Close the file when done
    return 0;
}
