#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int global_var;
pthread_mutex_t a_mutex;

void *do_thread1(void *data);
void *do_thread2(void *data);

int main() {
    int res;
    int i;
    pthread_t p_thread1;
    pthread_t p_thread2;

    res = pthread_mutex_init(&a_mutex, NULL);
    if (res != 0) {
        perror("Mutex create error");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&p_thread1, NULL, do_thread1, NULL);
    if (res != 0) {
        perror("Thread create error");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&p_thread2, NULL, do_thread2, NULL);
    if (res != 0) {
        perror("Thread create error");
        exit(EXIT_FAILURE);
    }
    for (i = 1; i < 20; i++) {
        printf("Main thread waiting %d second \n", i);
        sleep(1);
    }
    printf("Finally the global_var is %d\n", global_var);
    return 0;
}

void *do_thread1(void *data) {
    int i;
    for (i = 1; i <= 5; i++) {
        pthread_mutex_lock(&a_mutex);
        global_var++;
        pthread_mutex_unlock(&a_mutex);
        sleep(1);
        printf("Thread 1 count: %d with global value %d \n", i, global_var);
    }
    printf("Thread 1 completed ! \n");
}

void *do_thread2(void *data) {
    int i;
    for (i = 1; i <= 5; i++) {
        pthread_mutex_lock(&a_mutex);
        global_var += 2;
        pthread_mutex_unlock(&a_mutex);
        sleep(2);
        printf("Thread 2 count: %d with global value %d \n", i, global_var);
    }
    printf("Thread 2 completed ! \n");
}

