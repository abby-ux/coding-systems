// NOTES ON CONCURRENCY, THREADS
//ignore until notes:
// Wrapper functions
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stddef.h>

// Wrapper functions for pthread operations
void Pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
                   void *(*start_routine)(void *), void *arg) {
    int rc = pthread_create(thread, attr, start_routine, arg);
    if (rc != 0) {
        printf("Error: pthread_create failed\n");
        exit(1);
    }
}

void Pthread_join(pthread_t thread, void **value_ptr) {
    int rc = pthread_join(thread, value_ptr);
    if (rc != 0) {
        printf("Error: pthread_join failed\n");
        exit(1);
    }
}
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
// uncomment if want to test:
// ____________________________________________________________________________________________________________________________
// ____________________________________________________________________________________________________________________________
// Choose which example to compile:
// #define BASIC_EXAMPLE
// #define COUNTER_EXAMPLE
// gcc -o threads concurrency-and-threads.c -pthread -DBASIC_EXAMPLE
#ifdef BASIC_EXAMPLE
// Basic threading example
void *mythread(void *arg) {
    printf("%s\n", (char*) arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2;
    printf("main: begin\n");
    
    Pthread_create(&p1, NULL, mythread, "A");
    Pthread_create(&p2, NULL, mythread, "B");
    
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    
    printf("main: end\n");
    return 0;
}
#endif
// ____________________________________________________________________________________________________________________________
// ____________________________________________________________________________________________________________________________

// orders to run threads:
/*
Thread 1 could be created an then ran, then thread 2 could be created than ran.
Thread 1 could be created, thread 2 could be created, then T1 ran, then T2 ran.
- these are just 2 examples, not the only 2 options.

A thread is kind of like a function call but: instead of executing the function and returning the caller, 
system creates a new thread and runs it independelty from the caller.
Threads are complicated - it is difficult to tell what will run when.
*/

// ---- SHARED DATA ----
/*
how threads interact when they access shared data.
ex: 2 threads want to update a global shared variable
*/
// ____________________________________________________________________________________________________________________________
// ____________________________________________________________________________________________________________________________
#ifdef COUNTER_EXAMPLE
// gcc -o threads concurrency-and-threads.c -pthread -DCOUNTER_EXAMPLE
// Shared counter example demonstrating race conditions
static volatile int counter = 0;

void *mythread(void *arg) {
    printf("%s: begin\n", (char *) arg);
    int i;
    for (i = 0; i < 1e7; i++) {
        counter = counter + 1;
    }
    printf("%s: done\n", (char *) arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2;
    printf("main: begin (counter = %d)\n", counter);
    
    Pthread_create(&p1, NULL, mythread, "A");
    Pthread_create(&p2, NULL, mythread, "B");
    
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    
    printf("main: done with both (counter = %d)\n", counter);
    return 0;
}
#endif
    // ____________________________________________________________________________________________________________________________
    // ____________________________________________________________________________________________________________________________

/*
The counter prints out a different number every time is it ran. Why??
--- uncontrolled scheduling ---
- race condition: the counter results depends on the timing of the codes execution
- this can happend when multiple threads execute the same code like in the case above when they both count 
How can we try to solve this?: Multual exclusion
- if one thread is running some code, let's prevent the other from doing so
*/
// conclusion
/*
critical section:
code that accesses a shared resource (gloabl variable/data structure)
race condition:
when multiple threads enter the critical section at the same time, both try to update the same shared resoucre.
This can lead to different results every time, and sometimes unwanted results.
indeterminate program:
program with one or more race conditions. Output vaires every time depending on when which threads ran when.
The output is therefor indeterminate which we expect from computer systems.
mutual exclusion:
programs should use this so the outcome can be predicted, and so only one thread runs a critical section in a program.

An OS was the first concurrent program.
*/