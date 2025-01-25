// C program to illustrate use of fork() &
// exec() system call for process creation

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> 
#include <stdlib.h>
#include <errno.h> 
#include <sys/wait.h>
#include <errno.h>






int main() {
    char dir[] = "my_directory"; // The directory to remove
    char *args[] = {"rmdir", dir, NULL}; // Command and arguments

    // Execute rmdir
    if (execvp(args[0], args4) == -1) {
        perror("execvp failed");
        return 1;
    }

    // This line won't be reached if execvp succeeds
    return 0;
}
// If execvp(args4[0], args4) is called:

// The current process is replaced by the rmdir command.
// The rmdir command is executed with dir as its argument.
// If successful, the specified directory is removed.
// If it fails, the program terminates with an error, and errno provides details about the failure.










int main(){
pid_t pid;
int ret = 1;
int status;
pid = fork();

if (pid == -1){

	// pid == -1 means error occurred
	printf("can't fork, error occurred\n");
	exit(EXIT_FAILURE);
}
else if (pid == 0){

	// pid == 0 means child process created
	// getpid() returns process id of calling process
	// Here It will return process id of child process
	printf("child process, pid = %u\n",getpid());
	// Here It will return Parent of child Process means Parent process it self
	printf("parent of child process, pid = %u\n",getppid()); 

	// the argv list first argument should point to 
	// filename associated with file being executed
	// the array pointer must be terminated by NULL 
	// pointer
	char * argv_list[] = {"ls","-lart","/home",NULL};

	// the execv() only return if error occurred.
	// The return value is -1
	execv("ls",argv_list);
	exit(0);
}
else{
	// a positive number is returned for the pid of
	// parent process
	// getppid() returns process id of parent of 
	// calling process
// Here It will return parent of parent process's ID
	printf("Parent Of parent process, pid = %u\n",getppid());
	printf("parent process, pid = %u\n",getpid()); 

		// the parent process calls waitpid() on the child
		// waitpid() system call suspends execution of 
		// calling process until a child specified by pid
		// argument has changed state
		// see wait() man page for all the flags or options
		// used here 
		if (waitpid(pid, &status, 0) > 0) {
			
			if (WIFEXITED(status) && !WEXITSTATUS(status)) 
			printf("program execution successful\n");
			
			else if (WIFEXITED(status) && WEXITSTATUS(status)) {
				if (WEXITSTATUS(status) == 127) {

					// execv failed
					printf("execv failed\n");
				}
				else
					printf("program terminated normally,"
					" but returned a non-zero status\n");			 
			}
			else
			printf("program didn't terminate normally\n");		 
		} 
		else {
		// waitpid() failed
		printf("waitpid() failed\n");
		}
	exit(0);
}
return 0;
}
