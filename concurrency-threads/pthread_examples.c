/*
Fork:
clone one process itno 2, give concurrency, isolation (seperate memory).
Threads:
Concurrency WITHOUT the isolation. - keeps everything in the same process.
Have difference call stacks, but in the same memroy space.

There are different APIs available for creating threads.
pthread: Standard API you can use.
*/
//example 1: create a pthread with pthread_create, join a pthread with pthread_join
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

//pthreads take and return a void pointer
// so we have to change this function by:
    // adding void*, void* arg, return NULL
void* myturn(void* arg) {
    for (int i = 0; i < 10; i++) {
        sleep(1);
        printf("My turn!%d\n", i);
    }
    return NULL;
}

void yourturn() {
    for (int i = 0; i < 5; i++) {
        sleep(1);
        printf("Your turn!%d\n", i);
    }
}

int main() {
    pthread_t newthread;
    pthread_create(&newthread, NULL, myturn, NULL);
    // without pthread, myturn will run forever, so we would never get to yourturn.
    // myturn();
    yourturn();
    // if yourturn finishes, main will complete, myturn might not finish running.
    // for example having the for loop 5 for yourturn and 10 times for myturn, 
    // it will always stop at 5 when yourturn is done.
        // fix this by using thread_join
        // waits until a specific thread finishes running and then continues
    pthread_join(newthread, NULL);
    return 0;
    
}

// example 2: create threads in a loop