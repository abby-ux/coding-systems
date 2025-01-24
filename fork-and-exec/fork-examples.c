#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{

    // make two process which run same
    // program after this instruction
    pid_t p = fork();
    if(p<0){
      perror("fork fail");
      exit(1);
    }
    printf("Hello world!, process_id(pid) = %d \n",getpid());
    return 0;
}


// #include <stdio.h>
// #include <sys/types.h>
// #include <unistd.h>
// int main()
// {
//     fork();
//     fork();
//     fork();
//     printf("hello\n");
//     return 0;
// }



// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <unistd.h>
// void forkexample()
// {
//     pid_t p;
//     p = fork();
//     if(p<0)
//     {
//       perror("fork fail");
//       exit(1);
//     }
//     // child process because return value zero
//     else if ( p == 0)
//         printf("Hello from Child!\n");

//     // parent process because return value non-zero.
//     else
//         printf("Hello from Parent!\n");
// }
// int main()
// {
//     forkexample();
//     return 0;
// }






// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <unistd.h>

// void forkexample()
// {
//     int x = 1;
//     pid_t p = fork();
//       if(p<0){
//       perror("fork fail");
//       exit(1);
//     }
//     else if (p == 0)
//         printf("Child has x = %d\n", ++x);
//     else 
//         printf("Parent has x = %d\n", --x);
// }
// int main()
// {
//     forkexample();
//     return 0;
// }





// #include <stdio.h>
// #include <unistd.h>
// int main()
// {
//     fork();
//     fork() && fork() || fork();
//     fork();

//     printf("forked\n");
//     return 0;
// }
