#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define n  6
pthread_t tid[n];
void* do_thread(void* data);

int main(){
    int result; 
    long i;
    void* thread_result;
    for (i = 1; i < n; i++) {
        result = pthread_create(&(tid[i]), NULL, do_thread, (void*)i); 
        if (result != 0) {
            perror("Thread created error");
            exit(EXIT_FAILURE);
        }
        sleep(1);
    }
    printf("Waiting for threads to finish....\n");
    for (i = n - 1; i > 0; i--) { 
        result = pthread_join(tid[i], &thread_result); 
        if (result != 0) {
            perror("Thread exited error");
        } else {
            printf("Pickup a thread\n");
        }
    }
    printf("All threads completed \n");
    return 0;
}

void* do_thread(void* data) {
    long number = (long)data; 
    printf("Thread function is running. Data argument was %ld\n", number); 
    sleep(3);
    printf("Finish - bye from %ld\n", number); 
    pthread_exit(NULL);
}

