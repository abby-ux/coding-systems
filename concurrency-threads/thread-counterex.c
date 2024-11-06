#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stddef.h>
#ifdef _WIN32
#include <windows.h>
#endif

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