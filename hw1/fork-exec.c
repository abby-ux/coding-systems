#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// You must fill in wherever it says 'HOMEWORK'.

void help();
int read_command(char *program);

// In C, a string is of type 'char []' or equivalently, 'char *'
int main(int argc, char *argv[]) {
  help();

  while (1) { // This is a "read-exec-print" loop.
    printf("%% "); // print prompt
    fflush(stdout); // Don't wait for 'newline'.  Flush stdout to screen now.

    int cmd;
    while (1) {
      cmd = read_command(argv[0]);
      if (cmd == '\n') { continue; } // Ignore newlines
      if (cmd == '#') {
        printf("HOMEWORK: This is a comment char.  Read through newline.\n");
        // Use a loop to consume characters until a newline or EOF
        while ((cmd = getchar()) != '\n' && cmd != EOF) {
            //  empty body because we dont do anything
        }
        continue;
      }
      break;
    }

    // The syntax "1" is an int and "'1'" is a char.
    switch (cmd) {
      case 'h':
        help();
        break; // Don't forget 'break'.  Otherwise control passes to next case.
      case 'x':
      case 'q':
        printf("Exiting\n");
        exit(0); // The argument 0 of exit says return code is 0:  success.

      case '1':
        printf("HOMEWORK: Execute 'ls' to list files.\n");

        pid_t p = fork();
        if (p < 0) {
            perror("fork failed");
            exit(1);
        } else if (p == 0) {
            // Child process
            char *args[] = {"ls", NULL};
            execvp(args[0], args);
            // If execvp fails
            perror("execvp failed");
            exit(1);
        } else {
            // Parent process
            int status;
            if (wait(&status) < 0) {
                perror("wait failed");
            } else {
                if (WIFEXITED(status)) {
                    printf("Child exited with status %d\n", WEXITSTATUS(status));
                } else if (WIFSIGNALED(status)) {
                    printf("Child was terminated by signal %d\n", WTERMSIG(status));
                } else {
                    printf("Child terminated abnormally\n");
                }
            }
            printf("Child has terminated\n");
        }
        break;

      case '2':
        printf("HOMEWORK: Execute 'ls -l' to list files.\n");

        pid_t p2 = fork();
        if (p2 < 0) {
            perror("fork failed");
            exit(1);
        } else if (p2 == 0) {
            // Child process
            char *args[] = {"ls", "-l", NULL};
            execvp(args[0], args);
            // If execvp fails
            perror("execvp failed");
            exit(1);
        } else {
            // Parent process
            if (wait(NULL) < 0) {
                perror("wait failed");
            }
        }
        break;
      case '3':
        // You'll need to continue to read 'dir' and stop at newline.
        printf("HOMEWORK:  See 'man 2 chdir'; implement 'cd'.\n");
        char dir[256]; // max size our directory could be
        char buf[1]; // 1 char buffer to read char by char
        int i = 0;
        while (read(0, buf, 1) > 0 && buf[0] != '\n') {
            dir[i] = buf[0];
            i++;
        }
        dir[i] = '\0';
        chdir(dir);
        printf("Directory changed");
        break;
      case '4':
        // You'll need to continue to read 'env var' and stop at newline.
        printf("HOMEWORK:  See 'man 3 getenv'; print env var (e.g., PWD).\n");
        break;
      case '5':
        // You'll need to to read 'env var' and string; stop at newline.
        printf("HOMEWORK:  See 'man 3 setenv'.\n");
        break;
      case '6':
        // Continue the input of command 6 by then reading the filenames
        //   for 'src' 'dest'.  Then use fork-exec with 'cp' command.
        printf("HOMEWORK:  Execute 'cp src dest'.\n");
        break;
      case '7':
        // You'll need to continue to read 'dir' and stop at newline.
        printf("HOMEWORK:  Execute 'mkdir dir'.\n");
        break;
      case '8':
        // You'll need to continue to read 'file' and stop at newline.
        printf("HOMEWORK:  Execute 'rm file'.\n");
        break;
      case '9':
        // You'll need to continue to read 'dir' and stop at newline.
        printf("HOMEWORK:  Execute 'rmdir dir'.\n");
        break;

      default:
        printf("Unrecognized command: %c\n", (char)cmd);
        printf("HOMEWORK: Read through newline.\n");
        break;
    }
  }

  return 0;  // When the process exits, this is its return code. 0 is success.
}

void help() {
  printf("HOMEWORK:  Print help statement showing ALL cases.\n");
  printf("EXAMPLE:\n 1: ...\n 2: ...\n h: ...\n x: ...\n q: ...\n #: ...\n");
}

int read_command(char *program) {
  char buf[1];
  while (1) {
    int rc;
    rc = read(0, buf, 1);  // fd is 0 (stdin); read just 1 character into buf.
    if (rc == 1) { // If 1 char was read
      break;
    } else if (rc == -1) { // If error
      if (rc == EAGAIN || rc == EINTR) {
        continue;  // The O/S kernel wasn't ready.  Ask it again.
      } else {
        fprintf(stderr, "%s: Error in reading command\n", program);
        exit(1);  // Error:  Set return code to error number 1
      }
    } else if (rc == 0) {
      printf("%s: End-of-input\n", program);
      exit(0);
    }
  }

  int cmd = buf[0];  // Convert 'char' to an 'int'.
  return cmd;
}