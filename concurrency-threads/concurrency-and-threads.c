// NOTES ON CONCURRENCY, THREADS
/*
Multi Threaded Process
Imagine there are slices of pizza on the table, Everyone just decides the slice they want in their head and grabs it - this will not work if two people grad the same slice. Threads are like this with memory chunks, so we must make sure each thread knows exactly which chunk of memory that it needs to grab.
Image two stacks spred throughout the address space, each chuck of the stack has a free chunk between it. This is how a multi-threaded process could look. 
There is one stack per thread.

Why use threads?
-- Parallelism --
- Reason 1: make your program run faster.
Turn the single threaded program into one that uses multiple CPUs. 
Imagine that you are trying to run through a very large array, it would be a lot faster to split this up into multiple processes running through different chunks of the array all at once.
- Reason 2: avoid blocking program progress due to slow I/O
If you are running a program that performs multiple input/output processes, instead of waiting, your program want to do something else (use the CPU for computation)
One thread in your program can wait for I/O, the CPU can switch to other threads which are ready to run (something more useful for the time) 
-- Procces vs threads: --
- You could use multiple processes instead of threads, but threads use the same address space. This makes threads easier to share data (best for programs) while multiple processes would be best for logically separate tasks.

*/

// example: create a thread, that will print 'A' and 'B' separately.
/*
- program will create 2 threads, each thread will use mythread() with different args (A, or B)
- when a thread is created it can run right away (running status), or be placed in a ready state - not running yet.
    - on a multiprocessor the threads could just run at the same time.
*/
#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h> 
#include <assert.h> 
#include <pthread.h>

void *mythread(void *arg) {
    printf("%s\n", (char*) arg);
    return NULL;
}

int main (int argv, char *argv[]) {
    pthread_t p1, p2;
    
}