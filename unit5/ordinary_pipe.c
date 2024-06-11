#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pd[2], n = 0, i = 0;
char line[256];

int main() {
    pipe(pd);
    printf("pd=[%d, %d]\n", pd[0], pd[1]);
    if (fork()) {
        printf("parent %d close pd[0]\n", getpid());
        close(pd[0]);
        while (i++ < 5) {
            printf("parent %d is writing to pipe\n", getpid());
            n = write(pd[1], "I AM YOUR PAPA", 16);
            printf("parent %d wrote %d bytes to pipe\n", getpid(), n);
        }
        printf("parent %d waits for child and exits\n", getpid());
    } else {
        printf("child %d close pd[1]\n", getpid());
        close(pd[1]);
        while (1) {  
            printf("child %d is reading from pipe\n", getpid());
            if ((n = read(pd[0], line, 128))){ 
                line[n] = 0;
                printf("child read %d bytes from pipe: %s\n", n, line);
            } else {  
                printf("child %d gets no data and exits\n", getpid());
                exit(0);
            }
        }
    }
}

