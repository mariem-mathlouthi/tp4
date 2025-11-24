#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void *thread1(void *arg)
{
    (void)arg; // Ignore le paramètre non utilisé

    printf("Thread 1: Tente d'obtenir lock1\n");
    pthread_mutex_lock(&lock1);
    printf("Thread 1: A obtenu lock1\n");

    sleep(1); // Simule un travail

    printf("Thread 1: Tente d'obtenir lock2\n");
    pthread_mutex_lock(&lock2);
    printf("Thread 1: A obtenu lock2\n");

    pthread_mutex_unlock(&lock2);
    printf("Thread 1: Relâche lock2\n");

    pthread_mutex_unlock(&lock1);
    printf("Thread 1: Relâche lock1\n");

    return NULL;
}

void *thread2(void *arg)
{
    (void)arg; // Ignore le paramètre non utilisé

    printf("Thread 2: Tente d'obtenir lock1\n"); // Même ordre que thread1
    pthread_mutex_lock(&lock1);
    printf("Thread 2: A obtenu lock1\n");

    sleep(1); // Simule un travail

    printf("Thread 2: Tente d'obtenir lock2\n");
    pthread_mutex_lock(&lock2);
    printf("Thread 2: A obtenu lock2\n");

    pthread_mutex_unlock(&lock2);
    printf("Thread 2: Relâche lock2\n");

    pthread_mutex_unlock(&lock1);
    printf("Thread 2: Relâche lock1\n");

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Tous les threads sont terminés.\n");
    return 0;
}
