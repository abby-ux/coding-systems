/* pthread.h - Simplified version */
#ifndef _PTHREAD_H
#define _PTHREAD_H

#include <time.h>
#include <sched.h>
#include <bits/pthreadtypes.h>
#include <bits/thread-shared-types.h>

/* Thread attributes */
#define PTHREAD_CREATE_JOINABLE    0
#define PTHREAD_CREATE_DETACHED    1
#define PTHREAD_CANCELED          ((void *) -1)
#define PTHREAD_CANCEL_ENABLE      0
#define PTHREAD_CANCEL_DISABLE     1
#define PTHREAD_CANCEL_DEFERRED    0
#define PTHREAD_CANCEL_ASYNCHRONOUS 1

/* Mutex attributes */
#define PTHREAD_MUTEX_NORMAL       0
#define PTHREAD_MUTEX_RECURSIVE    1
#define PTHREAD_MUTEX_ERRORCHECK   2
#define PTHREAD_MUTEX_DEFAULT      PTHREAD_MUTEX_NORMAL

/* Basic thread structures */
typedef unsigned long int pthread_t;

typedef struct {
    int detachstate;      /* Detached or joinable state */
    int schedpolicy;      /* Scheduling policy */
    struct sched_param schedparam; /* Scheduling parameters */
    int inheritsched;     /* Scheduling inheritance */
    int scope;            /* Scheduling scope */
    size_t guardsize;     /* Guard size */
    int stackaddr_set;    /* Stack address set */
    void *stackaddr;      /* Stack address */
    size_t stacksize;     /* Stack size */
} pthread_attr_t;

typedef struct {
    int type;             /* Mutex type */
    int protocol;         /* Mutex protocol */
    int prioceiling;      /* Mutex priority ceiling */
    int process_shared;   /* Process-shared flag */
} pthread_mutexattr_t;

typedef struct {
    int lock;            /* Lock value */
    unsigned int count;  /* Number of recursive locks */
    pthread_t owner;     /* Current owner thread */
    /* ... other implementation-specific fields ... */
} pthread_mutex_t;

typedef struct {
    int process_shared;  /* Process-shared flag */
    /* ... other implementation-specific fields ... */
} pthread_condattr_t;

typedef struct {
    pthread_mutex_t *mutex;  /* Associated mutex */
    /* ... other implementation-specific fields ... */
} pthread_cond_t;

/* Thread functions */
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                  void *(*start_routine) (void *), void *arg);
int pthread_join(pthread_t thread, void **retval);
int pthread_detach(pthread_t thread);
void pthread_exit(void *retval);
pthread_t pthread_self(void);
int pthread_equal(pthread_t t1, pthread_t t2);

/* Thread attribute functions */
int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);
int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize);
int pthread_attr_getstacksize(const pthread_attr_t *attr, size_t *stacksize);

/* Mutex functions */
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);

/* Condition variable functions */
int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
int pthread_cond_destroy(pthread_cond_t *cond);
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
                          const struct timespec *abstime);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);

#endif /* _PTHREAD_H */