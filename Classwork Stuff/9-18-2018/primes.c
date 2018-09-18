// gcc -g -o primes Primes.c -lpthread -lm
// ./out n num_threads

#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_N 100000000
#define MAX_THREADS 25

void crossout(int k), *worker(void *arg);
int n, prime[MAX_N + 1], nextBase;

pthread_mutex_t nextbaselock = PTHREAD_MUTEX_INITIALIZER;
pthread_t id[MAX_THREADS];

int main(int argc, char *argv[]) {
    if (argc != 3) { printf("You need to specify what primes to find and the amount of threads!\nExample: ./out 10000 4\n"); exit(1); }
    
    int nPrimes = 1, nThreads = atoi(argv[2]);
    void *work;
    n = atoi(argv[1]);
    nextBase = 3;

    for (int i = 3; i <= n; ++i) prime[i] = i % 2 != 0;
    for (int i = 0; i < nThreads; ++i) { if (pthread_create(&id[i], NULL, worker, "Thread " + i) != 0) { perror("pthread_create() error"); exit(1); } }
    for (int i = 0; i < nThreads; ++i) { if (pthread_join(id[i], &work) != 0) { perror("pthread_join() error"); exit(3); } else printf("%d values of base done\n", (int)work); }
    for (int i = 3; i <= n; prime[i++] ? nPrimes++ : 0);

    printf("The number of primes found was: %d\n", nPrimes);

    return 0;
}

void crossout(int k) { for (int i = 3; i * k <= n; i += 2) prime[i * k] = 0; }

void *worker(void *arg) {
    int limit = sqrt(n), base, *work = 0;

    while (1) {
        pthread_mutex_lock(&nextbaselock);
        base = nextBase;
        nextBase += 2;
        pthread_mutex_unlock(&nextbaselock);
        if (base <= limit && prime[base]) {
            crossout(base);
            work++;
        } else {
            pthread_exit(work);
        } 
    }
}