#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-v] command [args...]\n", argv[0]);
        return 1;
    }

    int verbose = 0;
    int arg_start = 1;

    // Check for verbose flag
    if (strcmp(argv[1], "-v") == 0) {
        verbose = 1;
        arg_start++;
    }

    if (arg_start >= argc) {
        fprintf(stderr, "Error: Missing command to execute.\n");
        return 1;
    }

    // Open the output file

    // flags:
    //     Access Modes (choose one):
    // O_RDONLY: Open the file for read-only.
    // O_WRONLY: Open the file for write-only.
    // O_RDWR: Open the file for read and write.
    //     File Creation/Behavior Flags (combine with access modes using bitwise OR |):
    // O_CREAT: Create the file if it doesn’t exist (requires mode).
    // O_EXCL: If O_CREAT is also specified, ensures the call fails if the file already exists.
    // O_TRUNC: If the file exists, truncate it to zero length.
    // O_APPEND: All writes append data to the end of the file.
                // 0644 => rw-r--r--
    int fd = open("record.out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // Create a pipe if verbose mode is enabled
    // pipefd[0] => read end of the pipe
    // pipefd[1] => write end of the pipe
    int pipefd[2];
    if (verbose && pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // Create a child process, so now, both the parent and the child processes 
    // have copies of the pipe file descriptors (pipefd[0] and pipefd[1]).

    // timing:
    // If the child reads from an empty pipe, it blocks (waits) until the parent writes data.
    // If the parent writes to a full pipe, it blocks until the child reads some data.
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process is going to read data from the read end of the pipe fd[0]
        if (verbose) {
            close(pipefd[0]); // Close read end of the pipe - because that is the end the parent process will use
            dup2(pipefd[1], 1); // Redirect stdout to write end of the pipe
            close(pipefd[1]);
        } else {
            // stdout - fd 1
            // fd - record.out
            dup2(fd, 1); // Redirect stdout to record.out
        }

        close(fd); // Close the file descriptor
        // execute the command which we got from the command line and 
        // in this case we are replacing the child process we created with fork
        // and &argv[arg_start] can be treated as the starting point of the array of arugemnts we want to run
        // 
        execvp(argv[arg_start], &argv[arg_start]);
        perror("execvp");
        exit(1);
    } else {
        // Parent process is going to write data to the write end of the pipe, fs[1]
        close(fd);  // Close the file descriptor

        if (verbose) {
            close(pipefd[1]); // Close write end of the pipe

            int fd_out = open("record.out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out < 0) {
                perror("open");
                return 1;
            }

            // Read from the pipe and write to record.out with prefix
            FILE *pipe_read = fdopen(pipefd[0], "r");
            FILE *file_out = fdopen(fd_out, "w");
            char buffer[1024];

            while (fgets(buffer, sizeof(buffer), pipe_read)) {
                fprintf(file_out, "record.out> %s", buffer);
            }

            fclose(pipe_read);
            fclose(file_out);
            close(pipefd[0]);
        }

        // Wait for the child process to finish
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
    }

    return 0;
}
