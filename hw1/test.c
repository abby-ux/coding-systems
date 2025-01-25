#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

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
        char buf[1];
        while (read(0, buf, 1) > 0 && buf[0] != '\n') {
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

      case '1': {
        int rc = fork();
        if (rc < 0) { // fork failed
                fprintf(stderr, "fork failed\n");
                exit(1);
        } else if (rc == 0) { // child process
                char *myargs[2];
                myargs[0] = strdup("ls");
                myargs[1] = NULL;
                execvp(myargs[0], myargs);
        } else { // parent process
                int rc_wait = wait(NULL);
        printf("fork successful.\n");
        }
                }
        break;
      case '2': {
        int rc = fork();
        if (rc < 0) { // fork failed
                fprintf(stderr, "fork failed\n");
                exit(1);
        } else if (rc == 0) { // child process
                char *myargs[3];
                myargs[0] = strdup("ls");
                myargs[1] = strdup("-l");
                myargs[2] = NULL;
                execvp(myargs[0], myargs);
        } else { // parent process
                int rc_wait = wait(NULL);
                printf("fork successful.\n");
        }
                }
        break;
      case '3': {
        // You'll need to continue to read 'dir' and stop at newline.
        char dir[256];
        char buf[1];

        int i = 0;
        while (read(0, buf, 1) > 0 && buf[0] != '\n') {
                dir[i] = buf[0];
                i++;
        }
        dir[i] = '\0';
        chdir(dir);
        printf("directory successfully changed\n");
                }
        break;
      case '4': {
        // You'll need to continue to read 'env var' and stop at newline.
        char var[256];
        char buf[1];
        int i = 0;

        while (read(0, buf, 1) > 0 && buf[0] != '\n') {
                var[i] = buf[0];
                i++;
        }
        var[i] = '\0';
        char *value = getenv(var);
        printf("%s\n", value);
                }
        break;
      case '5': {
        // You'll need to to read 'env var' and string; stop at newline.
        char name[256];
        char value[256];
        char buf[1];
        int i = 0;

        while (read(0, buf, 1) && buf[0] != '\n') {
                name[i] = buf[0];
                i++;
        }
        name[i] = '\0';

        int j = 0;
        while(read(0, buf, 1) > 0 && buf[0] != '\n') {
                value[j] = buf[0];
                j++;
        }
        value[j] = '\0';
        setenv(name, value, 1);
        printf("setenv successful\n");
                }
        break;
      case '6': {
        // Continue to read 'src' and 'dest' files and stop at newline for each.
        char src[256];
        char dest[256];
        char buf[1];
        int i = 0;

        while (read(0, buf, 1) > 0 && buf[0] != '\n') {
                src[i] = buf[0];
                i++;
        }
        src[i] = '\0';
        int j = 0;

        while (read(0, buf, 1) > 0 && buf[0] != '\n') {
                dest[j] = buf[0];
                j++;
        }

        dest[j] = '\0';

        // fork a new process
        int rc = fork();

        if (rc < 0) {
                fprintf(stderr, "fork failed \n");
                exit(1);
        } else if (rc == 0){ // child process
                char *args[] = {"cp", src, dest, NULL};
                execvp("cp", args);
        } else { //parent process
                wait(NULL);
                printf("file successfully copied\n");
        }
                }
        break;
      case '7': {
        // You'll need to continue to read 'dir' and stop at newline.
        char dir[256];
        char buf[1];
        int i = 0;

        while (read(0, buf, 1) > 0 && buf[0] != '\n') {
                dir[i] = buf[0];
                i++;
        }
        dir[i] = '\0';

        // fork a new process
        int rc = fork();

        if (rc < 0) {
                fprintf(stderr, "fork failed\n");
                exit(1);
        } else if (rc == 0) { // child process
                char *args[] = {"mkdir", dir, NULL};
                execvp("mkdir", args);
        } else { // parent process
                wait(NULL);
                printf("directory created successfully\n");
        }
                }
        break;
      case '8': {
        // You'll need to continue to read 'file' and stop at newline.
        char file[256];
        char buf[1];
        int i = 0;

        while (read(0, buf, 1) > 0 && buf[0] != '\n') {
                file[i] = buf[0];
                i++;
        }
        file[i] = '\0';

        // fork a new process
        int rc = fork();

        if (rc < 0) {
                fprintf(stderr, "fork failed\n");
                exit(1);
        } else if (rc == 0){ // child process
                char *args[] = {"rm", file, NULL};
                execvp("rm", args);
        } else { // parent process
                wait(NULL);
                printf("file successfully removed\n");
        }
                }
        break;
      case '9': {
        // You'll need to continue to read 'dir' and stop at newline.
        char dir[256];
        char buf[1];
        int i = 0;

        while(read(0, buf, 1) > 0 && buf[0] != '\n') {
                dir[i] = buf[0];
                i++;
        }
        dir[i] = '\0';

        // fork a new process
        int rc = fork();
        if (rc < 0) {
                fprintf(stderr, "fork failed\n");
                exit(1);
        }
        else if (rc == 0) { // child process
                char *args[] = {"rmdir", dir, NULL};
                execvp("rmdir", args);
        } else { // parent process
                wait(NULL);
                printf("directory successfully removed\n");
        }
                }
        break;

      default:
        printf("Unrecognized command: %c\n", (char)cmd);
       // clear the buffer
       char buf[1];
       while (read(0, buf, 1) > 0 && buf[0] != '\n') {
       }
        break;
    }
  }

  return 0;  // When the process exits, this is its return code. 0 is success.
}

void help() {
  printf("1: list files\n");
  printf("2: list files with additional information\n");
  printf("3: change current directory\n");
  printf("4: print environment variable\n");
  printf("5: set environment variable\n");
  printf("6: copy a file\n");
  printf("7: create new directory\n");
  printf("8: remove a file\n");
  printf("9: remove a directory\n");
  printf("h: display list of commands\n");
  printf("q: exit\n");
  printf("x: exit\n");
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
