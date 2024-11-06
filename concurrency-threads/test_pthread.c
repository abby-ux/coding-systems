// test_pthread.c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  // for sleep()

void* hello(void* arg) {
    printf("Hello from thread %ld\n", (long)pthread_self());
    return NULL;
}

int main() {
    pthread_t thread;
    
    // Create thread
    if (pthread_create(&thread, NULL, hello, NULL) != 0) {
        perror("pthread_create failed");
        return 1;
    }
    
    // Wait for thread to finish
    if (pthread_join(thread, NULL) != 0) {
        perror("pthread_join failed");
        return 1;
    }
    
    printf("Main thread done!\n");
    return 0;
}